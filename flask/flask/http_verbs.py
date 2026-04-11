from flask import Flask, request,jsonify

app=Flask(__name__)


@app.route("/")
def home():
    return "Welcome to the Home Page!"

items=[
    {"id":1, "name":"Item 1", "price":100},
    {"id":2, "name":"Item 2", "price":200},
    {"id":3, "name":"Item 3", "price":300}
]
@app.route("/items",methods=["GET"])
def get_items():
    return jsonify(items)

@app.route("/items", methods=["POST"])
def create_item():
    if not request.json or not 'name' in request.json or not 'price' in request.json:
        return jsonify({"error": "Invalid input"})
    new_item = {
        "id": items[-1]['id'] + 1 if items else 1,
        "name": request.json['name'],
        "price": request.json['price']
    }
    items.append(new_item)
    return jsonify(new_item)

@app.route("/items/<int:item_id>", methods=["GET"])
def get_item(item_id):
    item = next((item for item in items if item["id"] == item_id), None)
    if item:
        return jsonify(item)
    return jsonify({"error": "Item not found"}), 404

@app.route("/items/<int:item_id>", methods=["PUT"])
def update_item(item_id):
    item = next((item for item in items if item["id"] == item_id), None)
    if not item:
        return jsonify({"error": "Item not found"}), 404
    if not request.json or not 'name' in request.json or not 'price' in request.json:
        return jsonify({"error": "Invalid input"}), 400
    item['name'] = request.json['name']
    item['price'] = request.json['price']
    return jsonify(item)

@app.route("/items/<int:item_id>", methods=["DELETE"])
def delete_item(item_id):
    global items
    items = [item for item in items if item["id"] != item_id]
    return jsonify({"result": "Item deleted"})

if __name__=="__main__":
    app.run(debug=True)