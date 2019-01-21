import cv2
import os
import sys
import dsl
import time
import logging

# Plugin Name and Plugin Category
def createPluginMetaData(plugin):
    pmd = dsl.PluginMetaData("doPythonWork", "Basic")
    pmd.setAuthor("Totte Karlsson")
    pmd.setDescription("Create a Python Work.")
    pmd.setCopyright("Allen Institute for Brain Science, 2018")
    pmd.setHint("Do Python Work")
    pmd.setCategory("Misc Plugins")
    plugin.assignMetaData(pmd)
    return pmd

# Setup the plugins properties, used later on when execution occurs
def createPluginProperties(plugin):
    logFileName = dsl.stringProperty("Log.txt", "LogFile")
    t           = dsl.floatProperty(.01, "Sleep")
    plugin.addProperty(logFileName)
    plugin.addProperty(t)
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

        sleepTime = thePlugin.getPropertyValueFloat("Sleep")

        progressData = dsl.intProperty(0, "Progress")
        loop = 0
        x = 10
        while loop < 101:
            loop = loop + 1
            x = x + 45.34
            sqrt(x)

            if thePlugin.isBeingTerminated() == True:
                logging.debug('Forcing Plugin To Exit')
                break

            progressData.setValue(loop)
            # Call plugins callback
            if thePlugin.hasProgressEvent():
                thePlugin.workProgressEvent(thePlugin, progressData)

            time.sleep(sleepTime)

        logging.debug('Looped ' + str(loop) +' times')
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
