# Import libraries
import sys
import csv

# Define the main function


def main():

    # Check if the user input the correct name of arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Load CSV file containing names and DNA sequences
    # Load the file into a variable
    database_path = sys.argv[1]
    with open(database_path) as dna_database:
        # Create a reader
        reader = csv.reader(dna_database)
        # Create a variable who store all the STR in the database header
        STR_references = next(reader)[1:]

        # Load txt file, containing a DNA sequence
        sequence_file = sys.argv[2]
        with open(sequence_file) as dna_sequence:
            sequence = dna_sequence.read()
            # Counts the longest run consecutives repeats for each DNA sequences
            STR_counts = [max_consecutive_str(sequence, STR) for STR in STR_references]

        # Compare the sequences repeats number to the database and find if there's a mach
        match = check_match(reader, STR_counts)

        # Print the name of the match or the "No match" message
        if match == "nobody":
            print("No match")
        else:
            print(match)

# Define a function that calulcate the max number of time a STR is repetead into a string


def max_consecutive_str(string, STR):
    # Prepare and inizialize a counts variable to use as a reference with the input string
    counts = [0] * len(string)
    # Run a loop that look for every chunk of DNA in the input with a size of the STR you're searching
    for i in range(len(string) - len(STR), -1, -1):
        # Check if this single chunk is equal to the STR of reference
        if string[i: i + len(STR)] == STR:
            # Set the counter for that place of the string as 1 if it's the last chunk of DNA
            if i + len(STR) > len(string) - 1:
                counts[i] = 1
            # Set the counter for that place of the string as +1 of the previous chunk counter
            else:
                counts[i] = 1 + counts[i + len(STR)]
    # Return the maximum number of consecutive STR found in the input txt
    return max(counts)

# Define a function that compare a database with a list of STR counters to check if there's a match and return the name of it


def check_match(database, STR_counts):
    for line in database:
        person = line[0]
        c = [int(value) for value in line[1:]]
        if c == STR_counts:
            return(person)
    return("nobody")

# Call the main function


if __name__ == "__main__":
    main()