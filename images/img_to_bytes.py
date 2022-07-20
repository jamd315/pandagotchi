import os
import sys

from PIL import Image
import numpy as np

for f in sys.argv[1:]:
    img = np.array(Image.open(f))  # Open, convert to array
    bool_arr: np.ndarray = img[:, :, 0] == 0  # Test if the 1st channel (0th index) of each pixel of the image is equal to 0
    bool_arr.flatten()  # Flatten array so that each row follows the previous one in a new 1D array
    int_arr = np.packbits(bool_arr)  # Condenses the array of booleans into ints, e.g. [F, F, F, F, F, T, F, T] becomes [5]
    product_bytes = int_arr.tobytes()  # The array of ints becomes bytes
    filename = os.path.splitext(f)[0] + ".bin"  # Make the output filename
    with open(filename, "wb") as f:  # Save
        f.write(product_bytes)
