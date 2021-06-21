import importlib

class MyApplication:
    # We are going to receive a list of plugins as parameter
    def __init__(self, plugins:list=[]):
        # Checking if plugin were sent
        if plugins != []:
            # create a list of plugins
            self._plugins = [
                importlib.import_module(plugin,".").Plugin() for plugin in plugins
            ]
        else:
            # If no plugin were set we use our default
            self._plugins = [importlib.import_module('default',".").Plugin()]

        
    def run(self):
        print("Starting my application")
        print("-" * 10)
        print("This is my core system")

        # Modified for in order to call process method
        for plugin in self._plugins:
            plugin.process(5,3)

        print("-" * 10)
        print("Ending my application")
        print() 
