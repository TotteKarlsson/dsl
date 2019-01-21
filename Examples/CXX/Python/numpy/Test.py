import numpy as np

def f1(a):
    print("array_tutorial - f1")
    print(a)
    a[0,1] = 34.34
    firstRow = a[0,:]
    return firstRow

def f2():
    b = np.array([[1.34,2.122,3.456],[1,2,3],[1,2,3]],dtype=np.float64)
    print("array_turorial - f2")
    print(b)
    return b


a = np.array([[1.34,2.122,3.456],[1,2,3],[1,2,3]], dtype=np.float64)
print (f1(a))
f2()