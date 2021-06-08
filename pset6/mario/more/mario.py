from cs50 import get_int
while(True):
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break
for row in range(1, height+1):
    print(" " * (height - row), end="")
    print("#" * row, end="")
    print("  ", end="")
    print("#" * row, end="")
    print()