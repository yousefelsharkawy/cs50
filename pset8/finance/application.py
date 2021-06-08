import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, name, sum(shares) shares FROM purchases group by buyer_id, symbol, name having buyer_id = :Id", Id =  session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :Id", Id = session["user_id"])
    prices = {}
    for row in rows:
        symbol = row["symbol"]
        prices[symbol] = lookup(symbol)["price"]
    total = cash[0]["cash"] + sum(prices.values())
    return render_template("index.html",rows=rows, prices=prices,cash=cash,total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        stock = lookup(request.form.get("symbol"))
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        elif not stock:
            return apology("stock does not exist")
        rows = db.execute("SELECT * FROM users WHERE id = :Id", Id = session["user_id"])
        cash = float(rows[0]["cash"])
        if (float(stock["price"]) * float(request.form.get("shares"))) > cash:
            return apology("cash is not enough")
        else:
            db.execute("UPDATE users SET cash = :Cash WHERE id = :Id", Cash=(cash - (float(stock["price"]) * float(request.form.get("shares")))), Id=session["user_id"])
            db.execute("INSERT INTO purchases (buyer_id, symbol, name, shares, price) VALUES (:buyer_id, :symbol, :name, :shares, :price)"
                       ,buyer_id = session["user_id"], symbol = stock["symbol"], name=stock["name"],shares = request.form.get("shares"), price=stock["price"])
            return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("stock doesn't exist")
        else:
            return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        rows = db.execute("SELECT username FROM users WHERE username = :username",username=request.form.get("username"))
        if not request.form.get("username"):
            return apology("Must provide username" , 403)
        elif len(rows) == 1:
            if request.form.get("username") == rows[0]["username"]:
                return apology("The Username Is taken")
        elif not request.form.get("password"):
            return apology("Must Provide Password")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords don't match")
    db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                username = request.form.get("username"), hash = generate_password_hash(request.form.get("password")))
    return redirect("login")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
