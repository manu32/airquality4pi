
import json

def load_model():
    with open("db.json") as f:
        return json.load(f)