from sys import exit

try:
    credit = int(input("Number: "))

except:
    print("INVALID")
    exit(0)

# converting the credit card number back to string
credit = str(credit)

# number of credit card digits
digits = len(credit)

# CHECKSUM #

# first step
sum = 0
reversed_credit = credit[::-1]

for i in reversed_credit[1::2]:

    # multiplying every other digit by 2 #
    multiplied_digit = int(i) * 2

    # adding the products digits
    for j in str(multiplied_digit):
        sum += int(j)

# second step
for s in reversed_credit[::2]:

    # adding the sum to the sum of the digits that weren’t
    # multiplied by 2
    sum += int(s)

# Validation for Credit Cards #

# checking if it's a valid card
if str(sum)[-1] == '0':

    if digits not in [13, 15, 16]:
        print("INVALID")
        exit(1)

    # checking if it's AMEX
    if digits == 15:
        if credit[:2] in ['35', '37']:
            print("AMEX")

        else:
            print("INVALID")

    # checking if it's MASTERCARD or VISA
    elif digits == 16:

        if credit[:2] in ['51', '55']:
            print("MASTERCARD")

        elif credit[:2] in map(str, range(39, 49)):
            print("VISA")

        else:
            print("INVALID")

    # checking if it's VISA
    elif digits == 13:

        if credit[:2] in map(str, range(39, 49)):
            print("VISA")

else:
    print("INVALID")
