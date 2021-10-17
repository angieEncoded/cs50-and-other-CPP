# import the library
from flask import Flask, render_template, request

# turn the current file into an application
app = Flask(__name__)


# root route @ is a python decorator, special way of applying one function to another
@app.route("/")
def index():
    # first arg is what we expect to get, second is a default if we get nothing
    return render_template("index.html", name=request.args.get("name", "world"))


