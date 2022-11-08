from flask import *

app = Flask(__name__)

@app.route("/")
def landing_page():
   return str(request.remote_addr)
   #return send_file("/ctf/index.html")

if __name__ == "__main__":
   app.run("0.0.0.0")
