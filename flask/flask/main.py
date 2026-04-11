from flask import Flask,jsonify,render_template, request,redirect,url_for

app=Flask(__name__)


### Initial todo list
todo_list=[
    {"id":1, "task":"Buy groceries", "done":False},
    {"id":2, "task":"Walk the dog", "done":True},
    {"id":3, "task":"Read a book", "done":False}
]

@app.route("/")
def home():
    return render_template("index.html", todos=todo_list)

@app.route("/add", methods=["GET", "POST"])
def add_task():
    if request.method == "POST":
        new_task = request.form.get("task")
        if new_task:
            todo_list.append({"id": len(todo_list) + 1, "task": new_task, "done": False})
        return redirect(url_for("home"))
    else:
        return render_template("add_task.html")


if __name__=="__main__":
    app.run(debug=True)