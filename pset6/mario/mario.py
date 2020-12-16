from cs50 import get_int

height = get_int("Height: ")

if height < 1 or height > 8:
    while True:
        print("Height must be a positive integer between 1 and 8. Try again.")
        height = get_int("Height: ")
        if height > 1 and height <= 8:
            break

for i in range(1, height + 1):

    for indent in range(height - i):
        print(" ", end="")
        
    for j in range(i):
        print("#", end="")
        
    print("  ", end="")
    
    for k in range(i):
        print("#", end="")
        
    print("\n", end="")