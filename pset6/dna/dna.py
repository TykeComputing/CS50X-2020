import csv
import sys


def main():
    # Check for 2 command-line arguments
    if len(sys.argv) != 3:
        print('Error: Incorrect usage at command line. Format is dna.py database.csv sequence.txt')
        sys.exit(1)

    # With CSV file open
    with open(sys.argv[1], 'r', newline='') as csvfile:

        # Use dictreader to important rows into a dict
        database = csv.DictReader(csvfile)

        # Initialise checkList of STRs
        checkList = list(database.fieldnames)
        checkList.remove('name')

        # Initialise list (strCounters) for highest recorded values of DNA strings, maintaining order as per specification
        strCounters = [0] * len(checkList)

        # With DNA sequence file open
        with open(sys.argv[2], 'r', newline='') as strfile:

            # Read sequence into memory as string
            sequence = strfile.read()

        # Iterate over checkList STRs found within sequence
        for n in range(len(checkList)):

            j = len(checkList[n])

            for i in range(len(sequence) - (j - 1)):
                if sequence[i:i+j] == checkList[n]:
                    tempCounter = 1

                    # Count consecutive repeats of this STR recursively
                    while True:
                        i += j
                        if sequence[i:i+j] == checkList[n]:
                            tempCounter += 1
                        else:
                            break

                    # If count is higher than same STR in list strCounters, swap this count into the list for that STR
                    if tempCounter > strCounters[n]:
                        strCounters[n] = tempCounter

        # If counter list is found in dict, print match
        for row in database:
            test = []
            for i in range(len(checkList)):
                test.append(int(row[checkList[i]]))
            if test == strCounters:
                print(row['name'])
                sys.exit(0)

        # If no match found, print result
        print('No match')

    # Exit program
    sys.exit(0)


main()