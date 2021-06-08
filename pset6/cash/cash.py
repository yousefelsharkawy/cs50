from cs50 import get_float
while(True):
    dollars = get_float("chnage owed: ")
    if dollars >= 0:
        break
cents = round(dollars * 100)
i = 0
if cents >= 25:
    i = i + int(cents / 25)
    cents = cents % 25

if cents >= 10:
    i = i + int(cents / 10)
    cents = cents % 10
if cents >= 5:
    i = i + int(cents / 5)
    cents = cents % 5
if cents >= 1:
    i = i + int(cents / 1)
    cents = cents % 1
print(i)