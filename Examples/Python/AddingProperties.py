import dsl
import sys

def setupProperties():
        props = dsl.Properties("TempAndHumidity")
        p1    = dsl.intProperty(30, "Days")
        p2    = dsl.floatProperty(99.99, "Floats")
        p3    = dsl.stringProperty("This is a string value", "Strings")
        props.add(p1)
        props.add(p2)
        props.add(p3)
        return props

##The main function allow debugging of the plugin from within python
def main():
    try:
        props = setupProperties()
        print ("Number of properties: " + str(props.count()))

        for i in range(props.count()):
            prop = props.getProperty(i)
            print ("Property label: " + str(prop.getLabel()) + " Value = " + prop.getValueAsString())

    except: # catch exceptions
        e = sys.exc_info()[0]
        print ("There was a problem: " + str(e))

if __name__ == '__main__':
    main()

