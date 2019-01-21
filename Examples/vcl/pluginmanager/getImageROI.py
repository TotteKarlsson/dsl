import cv2
import os
import sys
import dsl
import time
import logging


# Plugin Name and Plugin Category
def createPluginMetaData(plugin):
    pmd = dsl.PluginMetaData("getImageROI", "Basic")
    pmd.setAuthor("Totte Karlsson")
    pmd.setDescription("Create a cropped image.")
    pmd.setCopyright("Allen Institute for Brain Science, 2018")
    pmd.setHint("Crop Image")
    pmd.setCategory("Misc Plugins")
    plugin.assignMetaData(pmd)
    return pmd

# Setup the plugins properties, used later on when execution occurs
def createPluginProperties(plugin):
    plugin.addProperty(dsl.stringProperty("P:\\Temp\\Image1.jpg",   "SourceImageFileName"))
    plugin.addProperty(dsl.stringProperty("Log.txt",                "LogFile"))
    plugin.addProperty(dsl.intProperty(0,                           "X"))
    plugin.addProperty(dsl.intProperty(0,                           "Y"))
    plugin.addProperty(dsl.intProperty(100,                         "Height"))
    plugin.addProperty(dsl.intProperty(100,                         "Width"))
    plugin.addProperty(dsl.stringProperty("NoName",                 "CroppedImageFileName"))
    return True

def cropImage(imageF, x, y, h, w):
    if not os.path.isfile(imageF):
        raise FileNotFoundError

    logging.debug('Cropping Image: ' + imageF)
    #Check if file exists
    img = cv2.imread(imageF, cv2.IMREAD_COLOR)
    cropped_img = img[y:y+h, x:x+w]
    imagePath = os.path.dirname(os.path.abspath(imageF))
    imageFNameNoExtension = os.path.splitext(os.path.basename(imageF))[0]
    outFName = os.path.join(imagePath, imageFNameNoExtension + "-cropped.jpg")
    cv2.imwrite(outFName, cropped_img)
    logging.debug('Wrote ImageFile: ' + outFName)
    return outFName

## The execute function is called from C/C++ with a PythonPlugin object
## as argument. The python code below assume that the plugins properties and metadata has been setup from
## within c/c++, using the above functions
def execute(thePlugin):
    try:
        logFileName = thePlugin.getPropertyValueString("LogFile")
        logging.basicConfig(filename=logFileName, level=logging.DEBUG)

        if(thePlugin.isBeingTerminated() == True):
            logging.debug('Forcing exit from Plugin execute method: Plugin \'' + thePlugin.getName() + "\': " + str(i))

        else:
            logging.debug('Executing the Python Plugin \'' + thePlugin.getName())
            inFName = thePlugin.getPropertyValueString("SourceImageFileName")
            x       = thePlugin.getPropertyValueInt("X")
            y       = thePlugin.getPropertyValueInt("Y")
            height  = thePlugin.getPropertyValueInt("Height")
            width   = thePlugin.getPropertyValueInt("Width")
            outFName = cropImage(inFName, x, y, height, width)
            thePlugin.setPropertyValue("CroppedImageFileName", outFName)

    except FileNotFoundError as e:
        e = sys.exc_info()
        print ("Failed cropping image. Failure Message: " + str(e))
        return False

    logging.debug('Exiting execute function in plugin: ' + thePlugin.getName())
    return True

#Main function is used for testing..
def main():
    try:
        pm = dsl.PythonPluginManager()
        plugin = pm.createBarePlugin("getImageROI")
        createPluginMetaData(plugin)
        createPluginProperties(plugin)

        srcFName = "p:/temp/Image1.jpg"
        plugin.setPropertyValue("SourceImageFileName", srcFName)

        p = plugin.getProperty("SourceImageFileName")
        print( p.getValueAsString())
        x, y, h, w = 500, 300, 400, 200
        plugin.setPropertyValue("X", x)
        plugin.setPropertyValue("Y", y)
        plugin.setPropertyValue("Height", h)
        plugin.setPropertyValue("Width", h)

        for i in range(1):
            res = execute(plugin)

    except: # catch exceptions
        e = sys.exc_info()[0]
        print ("There was a problem: " + str(e))

    finally:
        #Its important to call this, in order to clean up memory properly
        pm.unloadAll()


if __name__ == '__main__':
    main()
