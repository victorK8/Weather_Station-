from flask import Flask, render_template, url_for

app = Flask(__name__)

# Index page
@app.route('/')
def index():
    return render_template('index.html')

# Dashboard page
@app.route('/Dashboard')
def dashboard():
    return 'Dashboard (Not yet)'

# Download page
@app.route('/Downloads')
def downloads():
    return 'Downloads (Not yet)'

# About page
@app.route('/about.html')
def about():
    return render_template('about.html')


if __name__ == '__main__':
    app.run(host = '0.0.0.0', port=80, debug=True)


