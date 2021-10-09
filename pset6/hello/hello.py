from cs50 import get_string


# Define main function
def main():
    # Get name variable from user
    name = get_string("What is your name? ")
    # Print customized hello message
    print(f"Hello, {name}")


# Call the main variable
if __name__ == "__main__":
    main()