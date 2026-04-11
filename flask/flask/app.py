from flask import Flask,render_template, request
'''It creates an instance of the Flask class.
which will be our WSGI (Web Server Gateway Interface) application.'''

### render_template is used to render HTML templates.

### WSGI application
app=Flask(__name__)

@app.route("/")
def welcome():
    return "Welcome to Flask!"

@app.route("/about")
def about():
    return render_template("about.html")

@app.route("/index",methods=["GET"]) ## y default it is a get  request
def index():
    return "<html><body><h1>Index Page</h1><p>This is the index page of the Flask application.</p></body></html>"


@app.route("/form", methods=["GET", "POST"])
def form():
    if request.method == "POST":
        # Handle form submission
        name = request.form["name"]
        return f"Hello {name}"
    return render_template("form.html")

if __name__ == "__main__":
    app.run(debug=True)


