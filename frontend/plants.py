
from flask import Flask
from flask import render_template
from flask import request
from flask import url_for
from flask import redirect
from flask import g
from datetime import datetime
from datetime import date as dt
from datetime import timedelta
from model import load_model
import pandas as pd
import plotly
import plotly.express as px
import json

view_counter = 0

def date_less_than(date, compare_to):
    return datetime.strptime(compare_to, '%Y-%b-%d') < date

app = Flask(__name__)

@app.before_first_request
def startup():
    print('startup app')
    global current_date
    current_date = dt.today()

@app.route('/')
def hello_plants():
    return render_template('index.html')

@app.route('/date')
def date():
    global view_counter 
    view_counter+=1
    return f'This page was last updated at {datetime.now()} and has been viewed {view_counter} times.'

@app.route('/climate', methods=['GET', 'POST'])
def measurements():

    global current_date

    db = load_model()

    if request.method == 'POST':
        if request.form.get('previous') == 'prev':
            current_date -= timedelta(days=1)
        if request.form.get('next') == 'next':
            current_date += timedelta(days=1)

    df = pd.DataFrame(db)
    selected = df[df['date'] == current_date.strftime('%Y-%m-%d')]
    fig = px.line(selected, x='time', y='temperature')
    graph = json.dumps(fig, cls=plotly.utils.PlotlyJSONEncoder)
    enable_next = current_date < dt.today()
    return render_template('measurements.html', graph=graph, render_graph=True, selected_date=current_date.strftime('%d.%m.%Y'), less_than_today=enable_next)

@app.route('/add_note', methods=['GET', 'POST'])
def add_note():
    if request.method == "POST":
        print(request.form['title'])
        print(request.form['description'])
        return redirect(url_for('hello_plants'))
    else:
        return render_template('add_note.html')
