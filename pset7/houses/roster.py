from cs50 import SQL
import sys

db = SQL("sqlite:///students.db")


def main():
    # Check command-line arguments for valid syntax
    if len(sys.argv) != 2:
        print('Error: Incorrect usage at command line. Format is import.py house')
        sys.exit(1)

    # Query database for students in house, sorting alphabetically by last then first name
    house = sys.argv[1]

    roster = db.execute("SELECT first, middle, last, birth FROM students WHERE lower(house) = lower(?) ORDER BY last, first;", house)

    # Print out students' full names and birth year, checking for NULL middle name
    for row in roster:
        person = []
        for key in row.keys():
            if not row[key] == None:
                person.append(row[key])

        if len(person) == 3:
            print(f"{person[0]} {person[1]}, born {person[-1]}")
        else:
            print(f"{person[0]} {person[1]} {person[2]}, born {person[-1]}")


main()