import csv
from sys import argv, exit
import cs50

# Connecting the db file to our python code
db = cs50.SQL("sqlite:///students.db")

# Prompting the user for enough command line arguments
if len(argv) != 2:
    print("misssing command line arguments")
    exit(1)

# Opening the csv file for reading
with open(argv[1], "r") as csv_file:
    reader = csv.DictReader(csv_file)

    # Looping in the csv file rows and inserting the data to the db file
    for row in reader:
        row["name"] = row["name"].split()
        if len(row["name"]) == 3:
            db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?)",
                       row["name"][0], row["name"][1], row["name"][2], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first,last,house,birth) VALUES (?,?,?,?)",
                       row["name"][0], row["name"][1], row["house"], row["birth"])
