import os
import re

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
    """Show portfolio of stocks"""

    current_cash = db.execute("SELECT cash FROM users WHERE id = ?", session.get("user_id"))[0]['cash']

    rows = db.execute("SELECT stock_symbol, stock_name, shares FROM portfolio WHERE user_id = ?", session.get("user_id"))

    total_cash = current_cash

    # Find the current prices for stocks and find the total cash
    for row in rows:
        stock_price = lookup(row['stock_symbol'])['price']
        total_price = row['shares'] * stock_price
        row.update({'price': stock_price, 'total': total_price})
        total_cash += total_price

    return render_template("index.html", rows=rows, current_cash=current_cash, total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Lookup stock symbol
        stock = lookup(symbol)

        if not shares.isdigit():
            return apology("You cannot purchase partial shares.")

        # Ensure it is a valid stock
        if stock == None:
            return apology("Invalid stock symbol")

        row = db.execute("SELECT cash FROM users WHERE id = ?", session.get("user_id"))
        current_cash = row[0]['cash']
        purchase = float(shares) * float(stock['price'])

        if purchase > current_cash:
            return apology("you do not have enough cash to purchase")

        else:
            current_cash -= purchase

            # Update the total cash that the user has
            db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, session.get("user_id"))

            # Add the purchase that was made
            db.execute("INSERT INTO transactions (user_id, stock_symbol, stock_name, price, shares) VALUES(?, ?, ?, ?, ?)",
                       session.get("user_id"), symbol, stock['name'], stock['price'], shares)

            # If the stock does not exist in the portfolio add it
            rows = db.execute("SELECT stock_symbol, shares FROM portfolio WHERE user_id = ? AND stock_symbol = ?",
                              session.get("user_id"), symbol)

            if len(rows) != 1:
                db.execute("INSERT INTO portfolio (user_id, stock_symbol, stock_name, shares) VALUES (?, ?, ?, ?)",
                           session.get("user_id"), symbol, stock['name'], shares)

            # Else if it does exist, add the shares that were recently bought
            else:
                db.execute("UPDATE portfolio SET shares=shares+(?) WHERE stock_symbol = ?", shares, symbol)

            flash("Bought!")
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT stock_symbol, shares, price, timestamp FROM transactions WHERE user_id = ?", session.get("user_id"))

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id, but maintain flashed message if present
    if session.get("_flashes"):
        flashes = session.get("_flashes")
        session.clear()
        session["_flashes"] = flashes
    else:
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

        symbol = request.form.get("symbol")

        # Lookup stock symbol
        stock = lookup(symbol)

        # Ensure it is a valid stock
        if stock != None:
            return render_template("quoted.html", stock=stock)
        else:
            return apology("Invalid stock symbol")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)
            
        # Ensure password is confirmed
        elif not confirmation:
            return apology("must confirm password", 400)

        # Ensure password confirmation matches
        if password != confirmation:
            return apology("The password confirmation does not match", 400)

        # Make sure password is strong
        if len(password) < 8:
            return apology("Password is short (Make it at least 8 characters)", 400)
        elif re.search('[0-9]', password) is None:
            return apology("Password must contain at least one number", 400)
        elif re.search('[A-Z]', password) is None:
            return apology("Password must contain at least one capital letter", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username is not already taken
        if len(rows) != 1:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        else:
            return apology("username already taken", 400)
            
        # Login user automatically after registeration
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session['user_id'] = rows[0]['id']

        # Redirect user to home page
        flash("Registered!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if symbol == None:
            return apology("Missing symbol", 400)

        if symbol == None:
            return apology("Missing shares", 400)

        # Lookup stock symbol
        stock = lookup(symbol)

        # Query the database for the selected stock
        row = db.execute("SELECT stock_symbol, shares FROM portfolio WHERE user_id = ? AND stock_symbol = ?",
                         session.get("user_id"), symbol)

        # Shares that the user have from the selected stock
        owned_shares = row[0]['shares']

        # Checking if the user have that number of shares
        if int(shares) > owned_shares:
            return apology("Too many shares", 400)

        shares_selled_price = shares * stock['price']

        # Add transaction
        db.execute("INSERT INTO transactions (user_id, stock_symbol, stock_name, shares, price) VALUES (?, ?, ?, ?, ?)",
                   session.get("user_id"), symbol, stock['name'], -shares, stock['price'])

        # Update the user's cash
        db.execute("UPDATE users SET cash=cash+(?) WHERE id = ?", shares_selled_price, session.get("user_id"))

        # Update the number of shares in portfolio
        db.execute("UPDATE portfolio SET shares=shares-(?) WHERE user_id = ? AND stock_symbol = ?",
                   shares, session.get("user_id"), symbol)

        flash("Sold!")
        return redirect("/")

    else:
        rows = db.execute("SELECT stock_symbol FROM portfolio WHERE user_id = ?", session.get("user_id"))

        return render_template("sell.html", rows=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
