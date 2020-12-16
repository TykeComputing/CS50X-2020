from cs50 import get_string

# Get input from user
input = get_string("Please enter the sentence: ")

# Iterate over input, counting total of letters, sentences and words
n = len(input)
letters = 0
sentences = 0
words = 1

for i in range(0, n, 1):
    if ord(input[i]) == 46 or ord(input[i]) == 63 or ord(input[i]) == 33:
        sentences += 1
    elif ord(input[i]) == 32:
        words += 1
    elif input[i].isalpha():
        letters += 1

# Convert to L (average letters per 100 words)
L = (letters / words) * 100

# Convert to S (average sentences per 100 words)
S = (sentences / words) * 100

# Run Colemann-Lieu formula to determine grade
index = (0.0588 * L) - (0.296 * S) - 15.8

# Return suggested grade to user
if index < 1:
    print("Before Grade 1")
    exit()
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade { round(index) }")