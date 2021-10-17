import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():


    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # check that there was data in all fields
        if not request.form.get("person") or not request.form.get("moy") or not request.form.get("dom"):
            # dump it back to the page with an error message if something was missing
            birthdays = db.execute("SELECT * from birthdays")
            return render_template("index.html", error="Missing something from the form. Try again.", birthdays=birthdays)
        else:
            # Get the data from the form
            name = request.form.get("person")
            month = request.form.get("moy")
            day = request.form.get("dom")

            # put the data in the database
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?,?,?)", name, month, day)

            # send the user back where they came from
            return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * from birthdays")
        return render_template("index.html", birthdays=birthdays)


