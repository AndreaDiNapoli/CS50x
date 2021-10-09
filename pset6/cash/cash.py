from cs50 import get_float

# Define the main function


def main():
    # Ask the user for how much change is to do
    change = get_change() * 100

    # Set the money value and the coins counter variable
    quarter = 25
    dime = 10
    nickel = 5
    penny = 1
    coins = 0

    # Count coins needed recursively starting from bigger to smaller ones
    while (change >= quarter):
        change -= quarter
        coins += 1

    while (change >= dime):
        change -= dime
        coins += 1

    while (change >= nickel):
        change -= nickel
        coins += 1

    while (change >= penny):
        change -= penny
        coins += 1

    # Print the number of coins needed
    print(f"{coins}")


# Define the main function
def get_change():
    while True:
        c = get_float("Change owed: ")
        if c >= 0:
            return c


if __name__ == "__main__":
    main()