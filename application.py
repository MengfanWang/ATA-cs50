from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    sub_total = 0
    stocks = []
    results = db.execute("SELECT symbol, sum(share) as share FROM `transaction` WHERE user_id = :id GROUP BY symbol", id=session["user_id"])

    for result in results:
        symbol = result['symbol']
        shares = result['share']
        price = lookup(result['symbol'])['price']
        total = round(result['share']*price,2)
        stocks.append((symbol, shares, price, total))
        sub_total = sub_total + total
        
    cash_balance = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]['cash']
    
    grant_total = cash_balance + sub_total
    
    return render_template("index.html", stocks=stocks, cash_balance=cash_balance, grant_total=grant_total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        # valid user inputs
        symbol = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))
        if not symbol :
            return apology("must provide valid symbol")
        if not shares or shares <= 0:  
            return apology("must provide valid shares")
            
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"]) 
        cash = int(cash[0]['cash'])
        
        if cash >= (symbol['price'] * shares):
            db.execute("INSERT INTO `transaction` (user_id, symbol, price, share) VALUES(:user_id, :symbol, :price, :share)", 
            user_id=session["user_id"], symbol=symbol['symbol'], price=symbol['price'], share=shares )
            update = db.execute("UPDATE users SET cash=cash-:total_price WHERE id=:id", 
            total_price=symbol['price'] * shares, id=session["user_id"])
            
            return redirect(url_for("index"))
        else:
            return apology("not enough money to buy")
            
    else:
        return render_template("buy.html")    
        

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    results = db.execute("SELECT * FROM `transaction` WHERE user_id = :id", id=session["user_id"])
    return render_template("history.html", results=results)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        if not request.form.get("symbol"):
            return apology("must provide symbol")
    
        symbol = request.form.get("symbol")        
        quote = lookup(symbol)
        if not quote:
            return apology("quote not found")
        else:
            quote['price'] = usd(quote['price'])
            return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    if request.method == "POST":
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        if request.form.get("password") != request.form.get("repeat password"):
            return apology("password not match")
        
        hashvalue = pwd_context.encrypt(request.form.get("password"))   
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", 
        username=request.form.get("username"), hash=hashvalue)
        
        if not result:
            return apology("username has been registered")
        
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))    
        session["user_id"] = rows[0]["id"]
        
        # redirect user to home page
        return redirect(url_for("index"))

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        # valid user inputs
        symbol = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))
        
        if not symbol :
            return apology("must provide valid symbol")
        if not shares or shares <= 0:  
            return apology("must provide valid shares")
            
        result = db.execute("SELECT share FROM `transaction` WHERE user_id = :id and symbol = :symbol", id=session["user_id"], symbol=symbol['symbol']) 
        if not result or result[0]['share'] < shares:
            return apology("not eligible for sell")
        else:
            db.execute("INSERT INTO `transaction` (user_id, symbol, price, share) VALUES(:user_id, :symbol, :price, :share)", 
            user_id=session["user_id"], symbol=symbol['symbol'], price=symbol['price'], share=(-shares))
                
            update = db.execute("UPDATE users SET cash=cash+:total_price WHERE id=:id", 
            total_price=symbol['price'] * shares, id=session["user_id"])
            
            return redirect(url_for("index"))
            
    else:
        return render_template("sell.html")    

