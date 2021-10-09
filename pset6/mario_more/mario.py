from cs50 import get_int


# Define the main function
def main():
    # Ask the user for the pyramid height
    height = get_height()

    # Build the pyramid
    for y in range(1, height + 1):
        print((height - y) * " ", end="")
        print(y * "#", end="")
        print("  ", end="")
        print(y * "#", end="")
        print()


# Define a function that ask for an int from 1 to 8
def get_height():
    while True:
        h = get_int("Height: ")
        if h > 0 and h <= 8:
            return h


if __name__ == "__main__":
    main()
