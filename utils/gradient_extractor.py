import re
import sys


def main(data):
    vals = re.findall(r"rgba\((\d+),(\d+),(\d+),\d+\) (\d+)%", data)
    print("DEFINE_GRADIENT_PALETTE (__NAME__) {")
    for val in vals:
        print(
            "    %d, %s, %s, %s," % (round(int(val[3]) * 2.55), val[0], val[1], val[2])
        )

    print("};")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py '<data_string>'")
    else:
        main(sys.argv[1])
