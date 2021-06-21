# Import the sys library
import sys
from core import MyApplication

if __name__ == "__main__": 
    # Initialize our app with the parameters received from CLI with the sys.argv 
    # Starts from the possion one due to position 0 will be main.py
    app = MyApplication(sys.argv[1:]) 
    # Run our application 
    app.run() 

    #python3 main.py default addition multiplication