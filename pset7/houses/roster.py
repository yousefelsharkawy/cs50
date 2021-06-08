from sys import argv, exit
import cs50

# Connecting the db file to our python program
db = cs50.SQL("sqlite:///students.db")

# Prompting the user for enough inputs
if len(argv) != 2:
    print("missing command line argument/s")
    exit(1)

# Quering the db file for data
list = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last,first", argv[1])

# Looping on each student and printing their data
for student in list:
    if student["middle"] == None:
        print(student["first"], student["last"] + ", born", student["birth"])
    else:
        print(student["first"], student["middle"], student["last"] + ", born", student["birth"])