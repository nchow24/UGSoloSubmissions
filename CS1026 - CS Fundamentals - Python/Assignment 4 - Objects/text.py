#creating dictionaries for each widget
widgetsList = []
widgets = open("widgets.txt", "r")
for line in widgets:
    line = line.rstrip()
    widgetsList.append(line)

for element in widgetsList:
    if "Widget" in element:
        position = widgetsList.index(element)
        widgetsList.pop(position)

for element in widgetsList:
    position1 = widgetsList.index(element)
    if element == "":
        widget1 = widgetsList[0:position1]
widgetsList.pop(position1)
for element in widgetsList:
    position2 = widgetsList.index(element)
    if element == "":
        widget2 = widgetsList[position1:position2]
widgetsList.pop(position2)
for element in widgetsList:
    position3 = widgetsList.index(element)
    if element == "":
        widget3 = widgetsList[position2:position3]
widgetsList.pop(position3)
for element in widgetsList:
    position4 = widgetsList.index(element)
    if element == "":
        widget4 = widgetsList[position3:position4]
widgetsList.pop(position4)
for element in widgetsList:
    position5 = widgetsList.index(element)
    if element == "":
        widget5 = widgetsList[position4:position5]

w1 = {}
w2 = {}
w3 = {}
w4 = {}
w5 = {}
for element in widget1:
    w1[element.partition(' ')[0]] = int(element.partition(' ')[-1])
for element in widget2:
    w2[element.partition(' ')[0]] = int(element.partition(' ')[-1])
for element in widget3:
    w3[element.partition(' ')[0]] = int(element.partition(' ')[-1])
for element in widget4:
    w4[element.partition(' ')[0]] = int(element.partition(' ')[-1])
for element in widget5:
    w5[element.partition(' ')[0]] = int(element.partition(' ')[-1])

print(w1)
print(w2)
print(w3)
print(w4)
print(w5)

