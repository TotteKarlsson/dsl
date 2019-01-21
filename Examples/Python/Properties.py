import dsl

p1 = dsl.intProperty(34, "An intProperty")
p2 = dsl.stringProperty("My String")

print (p1.getValue())
print (p2.getValue())

props = dsl.Properties("Testing")

props.add(p1)
props.add(p2)

a = props.getProperty(0)

print (a.getLabel())
print (props.count())