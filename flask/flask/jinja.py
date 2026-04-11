### Jinja2 is a templating engine for Python. It is used to generate HTML, XML, or other markup formats
### that are returned to the user via an HTTP response.

'''
{{ variable }}: This syntax is used to output the value of a variable.
{% for item in list %}...{% endfor %}: This is a control structure for looping over a list.
{% if condition %}...{% endif %}: This is a control structure for conditional statements.
{# This is a comment #}: This syntax is used to add comments in the template that will not be rendered in the output.
'''

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

### Variable rules in routes
@app.route("/success/<int:var>")
def success(var):
    return "You entered variable " + str(var)

x=[10,20,30,40,50,60,70,80,90]

@app.route("/result/<score>")
def result(score):
    res=''
    if score < '50':
        res='Fail'
    else:
        res='Pass'
    return render_template("result.html", marks=score, result=res, x=x)

@app.route("/ifpassed/<marks>")
def ifpassed(marks):
    return render_template("ifpassed.html", marks=int(marks))

if __name__ == "__main__":
    app.run(debug=True)


