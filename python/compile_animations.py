import platformio

import copy

env = DefaultEnvironment()
try:
    import yaml
except ImportError:
    env.Execute(
        env.VerboseAction(
            '$PYTHONEXE -m pip install "pyyaml"',
            "Installing ESP-IDF's Python dependencies",
        )
    )
    import yaml

TAB_SIZE = 2

class AnimationElement:
    sizeof = 10  # Manually updated
    def __init__(self, sequence_name, element_name, data, defaults=dict()):
        self._sequence_name = sequence_name
        self._element_name = element_name
        self.data = data
        self.x = data.get("x", defaults.get("x", 0))
        self.y = data.get("y", defaults.get("y", 0))
        self.w = data.get("w", defaults.get("w", 0))
        self.h = data.get("h", defaults.get("h", 0))
        self.invert = data.get("invert", defaults.get("invert", False))
        self.transparent = data.get("transparent", defaults.get("transparent", False))
        self.cleardisplay = data.get("cleardisplay", defaults.get("cleardisplay", False))
        self.delay = data.get("delay", defaults.get("delay", 0))
        self.image = data.get("image", defaults.get("image", None))
        if self.image is None:
            raise ValueError("AnimationElement must have an image")
        
    @property
    def name(self):
        return f"_{self._sequence_name}_{self._element_name}_id{id(self)}"

    def __repr__(self):
        return f"AnimationElement(id={id(self)}, name={self.name}, x={self.x}, y={self.y}, w={self.w}, h={self.h}, invert={self.invert}, transparent={self.transparent}, cleardisplay={self.cleardisplay}, delay={self.delay}, image={self.image}"

    def render_meta(self):
        if not self.invert and not self.transparent and not self.cleardisplay:
            return "IMAGE_DEFAULT"
        flags = []
        if self.invert:
            flags.append("IMAGE_INVERT")
        if self.transparent:
            flags.append("IMAGE_TRANSPARENT")
        if self.cleardisplay:
            flags.append("IMAGE_CLEARDISPLAY")
        return " | ".join(flags)

    def get_cpp(self, next_name=None, tab_index=0):
        next_name = "nullptr" if next_name is None else "&" + next_name
        return f"""static const PROGMEM AnimationElement {self.name} = 
{" " * (TAB_SIZE * tab_index + 0)}{{
{" " * (TAB_SIZE * tab_index + 1)}.x = {self.x},
{" " * (TAB_SIZE * tab_index + 1)}.y = {self.y},
{" " * (TAB_SIZE * tab_index + 1)}.w = {self.w},
{" " * (TAB_SIZE * tab_index + 1)}.h = {self.h},
{" " * (TAB_SIZE * tab_index + 1)}.meta = {self.render_meta()},
{" " * (TAB_SIZE * tab_index + 1)}.delay = {self.delay},
{" " * (TAB_SIZE * tab_index + 1)}.image = {self.image},
{" " * (TAB_SIZE * tab_index + 1)}.next = {next_name}
{" " * (TAB_SIZE * tab_index + 0)}}};
"""


class AnimationSequence:
    sizeof = 3
    def __init__(self, name, raw_sequence, sequence_id=0):
        self.name = name
        self.data = raw_sequence
        self.id = sequence_id
        if "defaults" in raw_sequence:
            self.defaults = raw_sequence["defaults"]
            del raw_sequence["defaults"]
        else:
            self.defaults = dict()
        self.elements = self.loop_handler(raw_sequence)
        seen_ids = set()
        for element in self.elements:
            if id(element) in seen_ids:
                raise RuntimeError("ID duplicate detected")
            seen_ids.add(id(element))

    """Returns a list of AnimationElements.  Recursive"""
    def loop_handler(self, loop_data, existing_elements=[], loop_amt=1):
        new_elements = list()
        for element_name, raw_element in loop_data.items():
            if element_name == "loop":  # Ignore these once we recurse into a loop
                continue
            if "image" in raw_element:
                new_elements.append(AnimationElement(self.name, element_name, raw_element, self.defaults))
            elif "loop" in raw_element:
                new_elements = self.loop_handler(raw_element, new_elements, raw_element["loop"])
        copied_new_elements = []
        for _ in range(loop_amt):
            copied_new_elements.extend(copy.deepcopy(new_elements))
        return existing_elements + copied_new_elements
    
    def get_cpp(self, tab_index=0):
        return f"""const PROGMEM AnimationSequence {self.name} = 
{" " * (TAB_SIZE * tab_index + 0)}{{
{" " * (TAB_SIZE * tab_index + 1)}.id = {self.id},
{" " * (TAB_SIZE * tab_index + 1)}.head = &{self.elements[0].name}
{" " * (TAB_SIZE * tab_index + 0)}}};
"""

    def render_cpp(self):
        out_str = ""
        out_str += f"#pragma region {self.name}\n"
        prev_name = None
        for i in reversed(range(len(self.elements))):
            out_str += self.elements[i].get_cpp(prev_name) + "\n"
            prev_name = self.elements[i].name
        out_str += self.get_cpp()
        out_str += f"#pragma endregion {self.name}\n"
        return out_str

    def render_header(self):
        return f"extern const PROGMEM AnimationSequence {self.name};\n"


def main():
    with open("./yaml/animations.yaml") as f:
        yaml_data: dict = yaml.load(f, Loader=yaml.Loader)

    sequences = []
    flash_size = 0
    sequence_counter = 0
    for name, data in yaml_data.items():
        sequence = AnimationSequence(name, data, sequence_counter)
        sequences.append(sequence)
        flash_size += AnimationSequence.sizeof
        flash_size += len(sequence.elements) * AnimationElement.sizeof
        sequence_counter += 1
    
    with open("./src/sequences.cpp", "w") as f:
        f.write(f"// Autogenerated.  Takes {flash_size:,} bytes of flash.\n")
        f.write("// NOTE these are declared backwards for linked list purposes\n")
        f.write("\n")
        f.write('#include <avr/pgmspace.h>\n')
        f.write('#include "sequences.h"\n')
        f.write('#include "Animator.h"\n')
        f.write('#include "images.h"\n')
        f.write('#include "globals.h"  // Face size declarations\n')
        f.write("\n")
        for sequence in sequences:
            f.write(sequence.render_cpp())
            f.write("\n")
    
    with open("./include/sequences.h", "w") as f:
        f.write(f"// Autogenerated.  Takes {flash_size:,} bytes of flash.\n")
        f.write("\n")
        f.write("#ifndef _SEQUENCES_H\n")
        f.write("#define _SEQUENCES_H\n")
        f.write("\n")
        f.write('#include "Animator.h"\n')
        f.write("\n")
        for sequence in sequences:
            print(f"Defined animation sequence {sequence.name}")
            f.write(sequence.render_header())
        f.write("\n#endif")


main()
