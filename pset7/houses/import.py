from cs50 import SQL
import csv
import sys

db = SQL("sqlite:///students.db")


def main():

    # Check command-line arguments for valid syntax
    if len(sys.argv) != 2:
        print('Error: Incorrect usage at command line. Format is import.py database.csv')
        sys.exit(1)

    # Open CSV file given by command-line argument
    with open(sys.argv[1], 'r', newline='') as csvfile:

        # Initialise variables for fields
        first = 'None'
        middle = 'None'
        last = 'None'
        house = 'None'
        birth = 1990

        # For each row, parse name using csv.reader
        reader = csv.reader(csvfile)
        next(reader)

        for row in reader:

            # Split name into separate variables
            name = row[0].split(" ")
            first = name[0]
            if len(name) == 2:
                middle = 'None'
            else:
                middle = name[1]
            last = name[-1]

            # Read remaining variables
            house = row[1]
            birth = row[2]

            # Insert each student into the students table of students.db
            if len(name) == 2:
                db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)", first, last, house, birth)
            else:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)


main()