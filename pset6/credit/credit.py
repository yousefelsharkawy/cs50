from cs50 import get_int
sums = []
sum_odd = 0

# Prompting the user for number
number = get_int("Number: ")

# Storing the number in a list
num = [int(x) for x in str(number)]

# Accessing the number's second-to-last digits
for i in range(len(num)-2, -1, -2):
    # Multiplying each digit by 2
    tmp = [int(y) for y in str(num[i] * 2)]
    # Storing the digits of the product result in a list
    sums[len(sums):] = tmp

# Accessing the other digits that wren't multiplied then sums them
for j in range(len(num)-1, -1, -2):
    sum_odd += num[j]

# Checking the total's last digit if 0 or not
if ((sum_odd + sum(sums)) % 10 != 0):
    print("INVALID")
# If the check is corect, determine the type of the card
else:
    ident = str(num[0]) + str(num[1])
    if len(num) == 15 and (ident == '34' or ident == '37'):
        print('AMEX')
    elif len(num) == 16 and (ident == '51' or ident == '52' or ident == '53' or ident == '54' or ident == '55'):
        print('MASTERCARD')
    elif (len(num) == 13 or len(num) == 16) and (ident[0] == '4'):
        print("VISA")
    else:
        print("INVALID")
