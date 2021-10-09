import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
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

    # Get the username and the budget
    user_items = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
    username = user_items[0]["username"]
    balance = user_items[0]["cash"]

    # Incorporate updated data from lookup function
    portfolios = db.execute("SELECT * FROM accounts WHERE shares>0 AND user_id IN (SELECT id FROM users WHERE id =?) ORDER BY shares DESC", session["user_id"])
    for portfolio in portfolios:
        stock_quote_tmp = lookup(portfolio["symbol"])
        portfolio["name"] = stock_quote_tmp["name"]
        portfolio["price"] = (stock_quote_tmp["price"])
        portfolio["value"] = (portfolio["price"]*portfolio["shares"])

    # Calculate the grand total
    grand_total = round(balance, 2)
    for portfolio in portfolios:
        grand_total += portfolio["value"]

    # Render the page
    return render_template("index.html", portfolios=portfolios, username=username, balance=balance, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User buy request through POST
    if request.method == "POST":


        # Save user input into variable
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check if the user input a valid stock symbol
        stock_quote = lookup(symbol)
        if stock_quote == None:
            return apology("Insert a valid stock symbol")

        # Check if the user share input is valid
        elif not request.form.get("shares"):
            return apology("Insert how many share to buy", 400)

        # Turn shares into an int
        try:
            shares = int(shares)
        except ValueError:
            return apology("Insert a positive number", 400)

        if shares <= 0:
            return apology("Insert a positive number", 400)


        # Calculate the price of the transaction
        price = stock_quote["price"] * shares

        # Lookup for the user's budget
        tmp = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        budget = tmp[0]["cash"]

        # Check if the user cash balace is enough to support the transaction
        if price > budget:
            return apology("You don't have enough money for that, sorry")

        # Update the user account (money and shares) and keep track of the transaction
        # Create a new portfolio for the user stock share or update the one existing
        if  len(db.execute("SELECT * FROM accounts WHERE symbol=? AND user_id IN(SELECT id FROM users WHERE id=?)", symbol, session["user_id"])) == 1:
            db.execute("UPDATE accounts SET shares = shares + ? WHERE symbol=? AND user_id IN(SELECT id FROM users WHERE id=?)", shares, symbol, session["user_id"])
        else:
            db.execute("INSERT INTO accounts(user_id, symbol, shares) VALUES(?, ?, ?)", session["user_id"], symbol, shares)

        # Remove price from user balace
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", price, session["user_id"])

        # Record the transaction
        db.execute("INSERT INTO operations(user_id, symbol, value, shares) VALUES(?, ?, ?, ?)", session["user_id"], symbol, round(price, 2), shares)

        return redirect("/")


    # User reached route by GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Incorporate updated data from lookup function
    operations = db.execute("SELECT * FROM operations WHERE user_id IN (SELECT id FROM users WHERE id =?) ORDER BY timestamp DESC", session["user_id"])

    # Render the page
    return render_template("history.html", operations=operations)



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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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

    if request.method == "POST":

        # Save user input into a variable
        symbol = request.form.get("symbol")

        # Check if the user input a valid stock symbol
        stock_quote = lookup(symbol)
        if stock_quote == None:
            return apology("Insert a valid stock symbol")

        return render_template("quoted.html", stock_quote=stock_quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Store username into a variable
        username = request.form.get("username")

        # Ensure username is not arleady used
        tmp = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(tmp) == 1:
            return apology("the username arleady exist", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password match confirmation password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("confirmation password don't match", 400)

        # Hash the password
        psw_hash = generate_password_hash(request.form.get("password"))

        # Create a new user into the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, psw_hash)

        # Automatically login the new user
        user_id = db.execute("SELECT id FROM users WHERE username=?", username)
        session["user_id"] = user_id[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("registration.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""


    # User buy request through POST
    if request.method == "POST":


        # Save user input into variable
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check if the user input a valid stock symbol
        stock_quote = lookup(symbol)
        if stock_quote == None:
            return apology("Insert a valid stock symbol")

        # Check if the user share input is valid
        elif not request.form.get("shares"):
            return apology("Insert how many share to sell", 400)

        try:
            shares = int(shares)
        except ValueError:
            return apology("Insert a positive number", 400)

        if shares <= 0:
            return apology("Insert a positive number", 400)

        # Calculate the price of the transaction
        price = stock_quote["price"] * shares

        # Lookup for the user's budget
        tmp = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        budget = tmp[0]["cash"]

        # Check if the user shares balace is enough to support the transaction
        tmp = db.execute("SELECT shares FROM accounts WHERE symbol = ? AND user_id IN (SELECT id FROM users WHERE id=?)", symbol, session["user_id"])
        own_shares = tmp[0]["shares"]

        if own_shares < shares:
           return apology("You don't have enough shares for that, sorry")

        # Update the user account (money and shares) and keep track of the transaction
        db.execute("UPDATE accounts SET shares = shares - ? WHERE symbol=? AND user_id IN(SELECT id FROM users WHERE id=?)", shares, symbol, session["user_id"])

        # Remove price from user balace
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", price, session["user_id"])

        # Record the transaction
        db.execute("INSERT INTO operations(user_id, symbol, shares, value) VALUES(?, ?, ?, ?)", session["user_id"], symbol, 0 - shares, 0 - price)

        return redirect("/")


    # User reached route by GET
    else:

        # Data for the select form
        symbols = db.execute("SELECT symbol FROM accounts WHERE shares>0 AND user_id IN(SELECT id FROM users WHERE id=?) ORDER BY symbol", session["user_id"])
        return render_template("sell.html", symbols=symbols)

@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add cash to budget"""

    # User buy request through POST
    if request.method == "POST":

        # Check if the user share input is valid
        if not request.form.get("deposit"):
            return apology("Insert how many cash you want to add", 403)

        # Turn deposit into an int and check if positive
        deposit = int(request.form.get("deposit"))

        if type(deposit) != int or deposit <= 0:
            return apology("Deposit can't be negative!")

        # Add money to user budget
        db.execute("UPDATE users SET cash = cash + ? WHERE id=?", deposit, session["user_id"])

        return redirect("/")

    # User reached route by GET
    else:
        return render_template("money.html")



    def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
