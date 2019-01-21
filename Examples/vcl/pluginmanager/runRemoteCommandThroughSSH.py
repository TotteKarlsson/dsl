import cv2
import os
import sys
import dsl
import time
import logging

# Plugin Name and Plugin Category
def createPluginMetaData(plugin):
    pmd = dsl.PluginMetaData("runRemoteCommand", "Basic")
    pmd.setAuthor("Totte Karlsson")
    pmd.setDescription("Run Remote Command.")
    pmd.setCopyright("Allen Institute for Brain Science, 2018")
    pmd.setHint("Remote Commmander")
    pmd.setCategory("Misc Plugins")
    plugin.assignMetaData(pmd)
    return pmd

# Setup the plugins properties, used later on when execution occurs
def createPluginProperties(plugin):
    plugin.addStringProperty(   "Log.txt",                                          "LogFile")
    plugin.addStringProperty(   "atbigdawg",                                        "SSHHost")
    plugin.addStringProperty(   "totte",                                            "UserName")
    plugin.addStringProperty(   "lacket47",                                         "Password")
    plugin.addIntProperty(      80,                                                 "RenderPort")
    plugin.addStringProperty(   "renderapps.stack.apply_global_affine_to_stack",    "ScriptName")
    plugin.addStringProperty(   "docker exec renderapps_develop python -m",         "RemoteCommand")
    return True

## The execute function is called from C/C++ with a PythonPlugin object
## as argument. The python code below assume that the plugins properties and metadata has been setup from
## within c/c++, using the above functions
def execute(thePlugin):
    try:

        logFormat = 'PYTHON_%(levelname)s: %(message)s'
        logFileName = thePlugin.getPropertyValueString("LogFile")
        logging.basicConfig(filename=logFileName, level=logging.DEBUG, format=logFormat)
        logging.debug('Entering Plugin Execute Method')


        logging.debug('Exiting execute function in plugin: ' + thePlugin.getName())

    except:
        e = sys.exc_info()
        print ()
        logging.error("Plugin Exception: "  + str(e))
        return False

    return True

def sqrt(y, n=10000):
    x = y / 2
    while n > 0:
        n -= 1
        x = (x + y/x) / 2
    return x

#Main function is used for testing..
def main():
    try:
        pm = dsl.PythonPluginManager()
        plugin = pm.createBarePlugin("doPythonWork")

        print(type(plugin))
        createPluginMetaData(plugin)
        createPluginProperties(plugin)
        plugin.setPropertyValue("Sleep", 1.1)

        res = execute(plugin)

    except: # catch exceptions
        e = sys.exc_info()
        print ("There was a problem: " + str(e))

    finally:
        #Its important to call this, in order to clean up memory properly
        pm.unloadAll()


if __name__ == '__main__':
    main()
