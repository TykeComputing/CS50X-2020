from cs50 import get_int

# Get number as int from user
intNumber = get_int("Long Card Number ")

# Convert int to list
number = list(map(int, str(intNumber)))

# Get length of list
numberlen = len(number)

# Check numberlen is within range
if numberlen < 13 or numberlen > 16:
    print("INVALID")
    exit()

# Sum the numbers
intsum = 0

if numberlen == 13 or numberlen == 15:
    a = 1
    b = 0
else:
    a = 0
    b = 1

for i in range(a, numberlen, 2):

    numberi = number[i] * 2

    if numberi < 10:
        intsum = intsum + numberi
    elif numberi >= 10:
        intsum = intsum + 1 + (numberi - 10)
    else:
        print("ERROR")
        exit()

for i in range(b, numberlen, 2):
    intsum = intsum + number[i]

# Convert first two digits of number to an integer
startdigits = (number[0] * 10) + (number[1])

# Check final sum number, compare numberlen to expected length of card, return type
if intsum % 10 == 0:
    if startdigits == 34 or startdigits == 37:
        print("AMEX")
        exit()
    elif startdigits > 50 and startdigits < 56 and numberlen == 16:
        print("MASTERCARD")
        exit()
    elif startdigits > 39 and startdigits < 50 and (numberlen == 13 or numberlen == 16):
        print("VISA")
        exit()
    else:
        print("INVALID")
        exit()

else:
    print("INVALID")
    exit()