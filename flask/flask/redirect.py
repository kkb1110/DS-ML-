from flask import Flask,render_template, request,redirect,url_for

app=Flask(__name__)

@app.route("/")
def welcome():
    return "Welcome to Flask!"


@app.route("/result/<score>")
def result(score):
    res=''
    if score < '50':
        res='Fail'
    else:
        res='Pass'
    return render_template("result.html", marks=score, result=res)

@app.route("/form",methods=["GET", "POST"])
def form():
    if request.method == "POST":
        math = request.form.get("Math")
        science = request.form.get("Science")
        english = request.form.get("English")
        c = request.form.get("C")
        total_avg = (int(math) + int(science) + int(english) + int(c)) / 4
        return redirect(url_for("result", score=total_avg )) ###'''passing tha value of score for dynamic route'''
    return render_template("allsub.html")

if __name__ == "__main__":
    app.run(debug=True)


