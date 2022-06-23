from cs50 import get_float

# the get_float makes sure that the input is a number not a string on its own

# change owed
co = get_float("Change owed: ") 

# converting from float to integer (from dollars to cents)
cents = co * 100

# number of coins
noc = 0 

# a loop for counting the number of cents
while cents != 0:
    if cents >= 25:
        cents -= 25
        noc += 1

    elif cents >= 10:
        cents -= 10
        noc += 1

    elif cents >= 5:
        cents -= 5
        noc += 1

    elif cents >= 1:
        cents -= 1
        noc += 1

print(noc)