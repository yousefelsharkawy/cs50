# Importing necessary packages for the program
from sys import argv, exit
import csv
import re

# Checking if the user provided enough inputs
if len(argv) != 3:
    print("Error! missing command line argument/s")
    exit(1)

# Declaring and initializing some necessary variables and list
names = []
seq_result = []
counter = 0
Max = 0

# Opening the csv file for reading
with open(argv[1], "r") as file:
    csvfile = csv.reader(file)
    # Storing the first row in col_names and the rest of rows in names (which is a list of lists/rows)
    for row in csvfile:
        if row[0] == "name":
            col_names = row
        else:
            names.append(row)

# Reading from the text file to string variable seq (short for sequence)
with open(argv[2], "r") as seq_file:
    seq_file_reader = csv.reader(seq_file)
    for row in seq_file_reader:
        seq = row[0]


# Calculating the maximum number of occurences of each STR in the sequence of dna
for i in range(1, len(col_names)):
    q = re.findall(f'(?:{col_names[i]})+', seq)
    for match in q:
        if (len(match) / len(col_names[i])) > Max:
            Max = int(len(match) / len(col_names[i]))
    seq_result.append(Max)
    Max = 0

# Checing the results with our database
for List in names:
    tmp_list = List[1:]
    tmp_list = [int(x) for x in tmp_list]
    if tmp_list == seq_result:
        print(List[0])
        exit(0)
print("No match")