from cs50 import get_int

height = 0

# prompts the user for a number from 1 through 8
while height <= 0 or height >= 9:
    height = get_int("Height: ")

for i in range(height):

    # prints spaces before the left side of the pyramid
    for s in range(height - i - 1):
        print(' ', end='')

    # prints the '#' of the left side of the pyramid
    for j in range(i + 1):
        print('#', end='')

    # prints the gap between the two sides of the pyramid
    print("  ", end='')

    # prints the '#' of the right side of the pyramid
    for j in range(i + 1):
        print('#', end='')

    print()