
from flask import Flask
from flask import render_template
from datetime import datetime
from model import load_model


view_counter = 0

app = Flask(__name__)


@app.route('/index')
def hello_plants():
    return render_template('index.html')

@app.route('/date')
def date():
    global view_counter 
    view_counter+=1
    return f'This page was last updated at {datetime.now()} and has been viewed {view_counter} times.'

@app.route('/climate')
def measurements():
    db = load_model()
    return render_template('plants.html', db=db)
