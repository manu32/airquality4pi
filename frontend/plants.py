
from flask import Flask
from flask import render_template
from flask import request
from flask import url_for
from flask import redirect
from datetime import datetime
from model import load_model
import pandas as pd
import plotly
import plotly.express as px
import json

view_counter = 0

app = Flask(__name__)

@app.route('/')
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

    df = pd.DataFrame(db)

    fig = px.line(df, x='timestamp', y='temperature')

    graph = json.dumps(fig, cls=plotly.utils.PlotlyJSONEncoder)

    return render_template('plants.html', graph=graph)

@app.route('/add_note', methods=['GET', 'POST'])
def add_note():
    if request.method == "POST":
        print(request.form['title'])
        print(request.form['description'])
        return redirect(url_for('hello_plants'))
    else:
        return render_template('add_note.html')
