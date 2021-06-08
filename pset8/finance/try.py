from cs50 import SQL

db = SQL("sqlite:///finance.db")

rows = db.execute("SELECT * FROM users WHERE id = 1")
print(float(rows[0]["cash"]))