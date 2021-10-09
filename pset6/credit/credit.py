import cs50

# Define the main function
def main():

    # Ask the user for a credit card number
    card = get_creditcard()
    #Calculate the cardnumber lenght and copy it as an INT into a new variable
    lenght = len(card)
    copy = int(card)

    for i in range(lenght):
        a = card[lenght] * 2
        b =






# Define a function that ask for a credit card number to verify
def get_creditcard():
    while True:
        c = cs50.get_string("Number: ")
        if len(c) != 13 or len(c) != 14 or len(c) != 15:
            print("INVALID")
            sys.exit()
        else:
            return c


if __name__ == "__main__":
    main()