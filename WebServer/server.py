from flask import Flask,render_template

app = Flask(__name__)

# Index page
@app.route('/')
def index():
    return render_template('index.html')
    
# Dashboard page
@app.route('/Dashboard')
def dashboard():
    return render_template('dashboard.html')

# Download page
@app.route('/Downloads')
def downloads():
    return render_template('downloads.html')

# About page
@app.route('/About')
def about():
    return render_template('about.html')


if __name__ == '__main__':
    app.run(host = '0.0.0.0', port=80, debug=True)


