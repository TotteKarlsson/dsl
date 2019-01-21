import dsl

def progressEvent(data1, data2):
    print("In the progress Event..")

def main():
    pm = dsl.PythonPluginManager()
    plugin = pm.createBarePlugin("doPythonWork")

    val1 = 34
    val2 = 22


    dsl.pluginEvent(val1, val2)
    plugin.assignOnProgressEvent(dsl.pluginEvent, None, None)

    plugin.onProgress()

if __name__ == '__main__':
    main()
