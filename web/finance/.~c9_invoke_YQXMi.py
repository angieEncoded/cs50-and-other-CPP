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

    # Get the user's information
    userData = db.execute(
        "SELECT * FROM users WHERE id = ?", session["user_id"])

    # get the user's owned shares
    userShares = db.execute(
        "SELECT * FROM shares WHERE user_id = ?", session["user_id"])

    # assign the cash on hand
    cashOnHand = userData[0]["cash"]
    cashOnHand = float(cashOnHand)

    # check if the user has anything returned from the query and if not, just return the template
    if not userShares:
        return render_template("index.html", cashOnHand=cashOnHand, totalValue=cashOnHand, totalSharesValue=0)

    # if we do have shares in the query
    else:

        # create an array to hold the current prices, and share value
        dataForDisplay = []
        totalValue = cashOnHand
        totalSharesValue = 0

        # loop through the userShares and lookup the current prices for each share
        # calculate the total price and push it all into a new array
        for item in userShares:

            # Look up the individual stock
            print(item)
            result = lookup(item["stock_symbol"])

            # calculate the value of the user's shares
            shareValue = float(result["price"]) * \
                float(item["number_of_shares"])
            # print(shareValue)

            # add to the total portfolio value
            totalValue = totalValue + shareValue
            totalSharesValue = totalSharesValue + shareValue
            # create a new object with all the data I want in it
            currentData = {
                "symbol": item["stock_symbol"],
                "name": item["stock_name"],
                "currentPrice": result["price"],
                "shareTotalValue": shareValue,
                "sharesOwned": item["number_of_shares"]
            }

            # Push that result into the current prices array
            dataForDisplay.append(currentData)

        # print(dataForDisplay)

        # pass everything through to the template
        return render_template("index.html", cashOnHand=cashOnHand, totalValue=totalValue, totalSharesValue=totalSharesValue, dataForDisplay=dataForDisplay)
        # return apology("in progress")


# personal touch - password reset.
@app.route("/passwordreset", methods=["GET", "POST"])
@login_required
def passwordreset():

    if request.method == "GET":
        return render_template("password.html")

    if request.method == "POST":

        # Check all the fields have data
        if not request.form.get("currentpassword") or not request.form.get("password") or not request.form.get("confirm"):
            flash("Must complete all fields")
            return render_template("password.html")

        # check that the passwords match
        if not request.form.get("password") == request.form.get("confirm"):
            flash("Passwords do not match")
            return render_template("password.html")

        # get the user from the session
        userId = session["user_id"]

        # get the user's password  from the database
        results = db.execute("SELECT * FROM users WHERE id = ?", userId)

        # check that the typed in password matches
        typedPassword = request.form.get("currentpassword")
        currentPassword = results[0]["hash"]
        valid = check_password_hash(currentPassword, typedPassword)

        if not valid:
            flash("Current password is not correct. Please check your password.")
            return render_template("password.html")

        # hash the new password
        newTypedPassword = request.form.get("password")
        newPassword = generate_password_hash(newTypedPassword)

        # Insert the new password into the database
        db.execute("UPDATE users SET hash = ? ", newPassword)
        flash("Successfully changed your password")
        return render_template("password.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    # show the form
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":

        # check that the stock symbol isn't blank
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Must input stock symbol and number of shares.")

        # if we have input, validate the input
        shares = request.form.get("shares")

        # check if it's a float - great help from stack overflow on this one https://stackoverflow.com/questions/736043/checking-if-a-string-can-be-converted-to-float-in-python
        try:
            int(shares)
        except ValueError:
            return apology("Cannot purchase fractional shares or non-numeric shares. Please enter whole number shares")

        if int(shares) < 1:
            return apology("Cannot purchase negative shares.")

        # if it's not blank, look it up
        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        results = lookup(symbol)
        # print(results)

        # return an apology if there are no results
        if results == None:
            return apology("That stock doesn't exist.")

        # Select cash the user has from the database
        userId = session["user_id"]
        userCash = db.execute("SELECT cash FROM users where id = ?", userId)
        userCash = float(userCash[0]["cash"])
        shareCost = float(results["price"])
        stockName = results["name"]
        numberOfShares = request.form.get("shares")
        numberOfShares = float(numberOfShares)
        totalCost = shareCost * numberOfShares
        print(userCash)
        print(totalCost)

        # check that the user has enough cash on hand
        if userCash >= totalCost:

            # check whether the user already has some of those shares
            results = db.execute(
                "SELECT * FROM shares where stock_symbol = ?", symbol)
            if not results:
                # "purchase" the stock with a new entry in - enter the stock_name, number_of_shares, user_id, purchase_price
                db.execute("INSERT INTO shares (stock_name, stock_symbol, number_of_shares, user_id) VALUES(?,?,?,?)",
                           stockName, symbol, numberOfShares, userId)
            # if we did find something in there
            else:
                currentShares = results[0]["number_of_shares"]
                usersTotalShares = int(currentShares) + int(numberOfShares)
                db.execute(
                    "UPDATE shares SET number_of_shares = ? where user_id = ?", usersTotalShares, userId)

            # Do some cleanup - add an entry to the history
            db.execute("INSERT INTO history (stock_name, stock_symbol, number_of_shares, user_id, price, purchase_type) VALUES(?,?,?,?,?,?)",
                       stockName, symbol, numberOfShares, userId, shareCost, "BUY")

            # subtract the amount from the user's balance
            userCash = userCash - totalCost
            db.execute("UPDATE users SET cash = ? WHERE id = ?",
                       userCash, userId)

            # when the transaction is done, send user back to the index page
            return redirect("/")

        else:
            return apology("Not enough cash on hand")


@app.route("/history")
@login_required
def history():
    userId = session["user_id"]
    results = db.execute("SELECT * FROM history WHERE user_id = ?", userId)
    return render_template("history.html", dataForDisplay=results)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

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
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Please enter a symbol to check", 400)
        else:
            result = lookup(request.form.get("symbol"))
            if result == None:
                return apology("That stock doesn't exist", 400)
            else:
                return render_template("quote.html", result=result)


@app.route("/register", methods=["GET", "POST"])
def register():

    # Show register form
    if request.method == "GET":
        return render_template("register.html")

    else:
        # check that there is a username
        if not request.form.get("username"):
            return apology("Username required.")

        # Check that passwords match

        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Password must be entered twice")

        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords don't match", 400)

        # Check that the username isn't in the database
        username = request.form.get("username")
        results = db.execute(
            "SELECT * FROM users WHERE username = ?", username)
        if len(results) > 0:
            if username == results[0]["username"]:
                return apology("That username is taken", 400)

        # Finally if we passed all those checks, hash the password and save the user
        password = request.form.get("password")
        hashedPassword = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?,?)",
                   username, hashedPassword)
        flash("Successfully registered! Enjoy using the system")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash("Successfully registered! Enjoy the system!")
        # Redirect user to home page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    userId = session["user_id"]

    if request.method == "GET":

        # get the user's current stocks
        results = db.execute("SELECT * FROM shares where user_id = ?", userId)
        return render_template("sell.html", results=results)

    if request.method == "POST":

        # Check that we entered valid stock data
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Must enter both a symbol and a number of shares", 400)

        # if we have input, validate the input\
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # check if it's a float - great help from stack overflow on this one https://stackoverflow.com/questions/736043/checking-if-a-string-can-be-converted-to-float-in-python
        try:
            int(shares)
        except ValueError:
            return apology("Cannot sell fractional shares or non-numeric shares. Please enter whole number shares")

        if int(shares) < 1:
            return apology("Cannot sell negative shares.")

        # make sure that the user has enough shares and send them away if not
        currentShares = db.execute(
            "SELECT * FROM shares WHERE stock_symbol = ? AND user_id = ?", symbol, userId)
        if int(currentShares[0]["number_of_shares"]) < int(shares):
            return apology("You don't have that many shares to sell.", 400)

        # determine how many we will have left
        endingNumberOfShares = int(
            currentShares[0]["number_of_shares"]) - int(shares)

        # lookup the current stock price
        currentPrice = lookup(symbol)
        # print(currentPrice)
        stockName = currentPrice["name"]
        price = currentPrice["price"]
        # add a selling transaction to the history
        db.execute("INSERT INTO history (stock_name, stock_symbol, number_of_shares, user_id, price, purchase_type) VALUES(?,?,?,?,?,?)",
                   stockName, symbol, shares, userId, price, "SELL")

        # calculate how much the user will make on this sale
        totalSale = float(currentPrice["price"]) * float(shares)

        # Delete the amount of shares from the user's shares
        db.execute("UPDATE shares SET number_of_shares = ?",
                   endingNumberOfShares)

        # add the cash to the user's cash balance
        cashOnHand = db.execute("SELECT cash FROM users WHERE id = ?", userId)
        endingBalance = cashOnHand[0]["cash"] + totalSale
        # print(cashOnHand[0]["cash"])

        db.execute("UPDATE users SET cash = ?", endingBalance)

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
