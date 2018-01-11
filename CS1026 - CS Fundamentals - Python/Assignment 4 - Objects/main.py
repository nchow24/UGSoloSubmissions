# nchow24, 250725575 (Nicole Anne Chow)
#widget construction information

class Parts:
    def __init__(self,name, price, quantity):
        self._partName = name
        self._partPrice = price
        self._partQuantity = quantity

    def getName(self):
        return self._partName

    def getPrice(self):
         return self._partPrice

    def setQuantity(self,part):
        self._partQuantity = self._partQuantity - part

    def getQuantity(self):
        return self._partQuantity

#creating lists for parts
parts = open("parts.txt", "r")
names = []
prices = []
initialQuantity = []
for line in parts:
    line = line.rstrip()
    names.append(line.split(' ', 1)[0])
    line = line.strip((line.split(' ', 1)[0]))
    line = line.strip(" ")
    prices.append(line.split(' ', 1)[0])
    line = line.partition(' ')[-1]
    initialQuantity.append(line)

#creating objects of class Parts
partA = Parts(names[0], float(prices[0]), int(initialQuantity[0]))
partB = Parts(names[1], float(prices[1]), int(initialQuantity[1]))
partC = Parts(names[2], float(prices[2]), int(initialQuantity[2]))
partD = Parts(names[3], float(prices[3]), int(initialQuantity[3]))
partE = Parts(names[4], float(prices[4]), int(initialQuantity[4]))

class PartInventory:

    #inventory data structure
    partsName = [partA.getName(),partB.getName(),partC.getName(),partD.getName(), partE.getName()]
    partsInventory = [partA.getQuantity(),partB.getQuantity(),partC.getQuantity(),partD.getQuantity(), partE.getQuantity()]

    #printing inventory data structure
    def printInventory():
        i = 0
        while i < len(PartInventory.partsName):
            print(PartInventory.partsName[i], ":", PartInventory.partsInventory[i])
            i = i +1
        print("")

    #updating partsInventory data structure
    def updateInventory(part, partsName = partsName, partsInventory = partsInventory):
        for element in partsName:
            if element == part:
                position = partsName.index(element)
                name = "part"+part[-1]
                if name == "partA":
                    partsInventory[position] = partA.getQuantity()
                elif name == "partB":
                    partsInventory[position] = partB.getQuantity()
                elif name == "partC":
                    partsInventory[position] = partC.getQuantity()
                elif name == "partD":
                    partsInventory[position] = partD.getQuantity()
                else:
                    partsInventory[position] = partE.getQuantity()


    #removing part from database1
    def removePart(part, partsName = partsName, partsInventory = partsInventory):
        for element in partsName:
            if element == part:
                position = partsName.index(element)
                partsName.pop(position)
                partsInventory.pop(position)
        return partsInventory and partsName

def main():
    #initial inventory output
    print("Initial Parts Inventory")
    PartInventory.printInventory()

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

    #widget1
    print("WIDGET 1")
    if partA.getQuantity() >= w1["partA"] and partB.getQuantity() >= w1["partB"] and partC.getQuantity() >= w1["partC"]:
        print("Widget CAN be built.")
        for element in w1:
            print(w1[element], "of", element, "used")
        cost1 = w1["partA"]*partA.getPrice() + w1["partB"]*partB.getPrice() + w1["partC"]*partC.getPrice()
        print("Cost: $","%.2f" % cost1)
        partA.setQuantity(w1["partA"])
        PartInventory.updateInventory("partA")
        partB.setQuantity(w1["partB"])
        PartInventory.updateInventory("partB")
        partC.setQuantity(w1["partC"])
        PartInventory.updateInventory("partC")
    else:
        print("Widget CANNOT be built.")
        if partA.getQuantity() <w1["partA"]:
            print("There is an insufficient amount of partA")
        if partB.getQuantity() <w1["partB"]:
            print("There is an insufficient amount of partB")
        if partC.getQuantity() <w1["partC"]:
            print("There is an insufficient amount of partC")
    print("")

    #widget2
    print("WIDGET 2")
    if partD.getQuantity() >=w2["partD"] and partB.getQuantity() >= w2["partB"]:
        print("Widget CAN be built.")
        for element in w2:
            print(w2[element], "of", element, "used")
        cost2 = w2["partD"]*partD.getPrice() + w2["partB"]*partB.getPrice()
        print("Cost: $", "%.2f" % cost2)
        partD.setQuantity(w2["partD"])
        PartInventory.updateInventory("partD")
        partB.setQuantity(w2["partB"])
        PartInventory.updateInventory("partB")
    else:
        print("Widget CANNOT be built.")
        if partD.getQuantity() <w2["partD"]:
            print("There is an insufficient amount of partD")
        if partB.getQuantity() <w2["partB"]:
            print("There is an insufficient amount of partB")
    print("")

    #widget3
    print("WIDGET 3")
    if partA.getQuantity() >= w3["partA"] and partB.getQuantity() >= w3["partB"] and partC.getQuantity() >= w3["partC"] and partD.getQuantity() >=w3["partD"]:
        print("Widget CAN be built")
        for element in w3:
            print(w3[element], "of", element, "used")
        cost3 = w3["partA"]*partA.getPrice() + w3["partB"]*partB.getPrice() + w3["partC"]*partC.getPrice() + w3["partD"]*partD.getPrice()
        print("Cost: ", "%.2f" % cost3)
        partA.setQuantity(w3["partA"])
        PartInventory.updateInventory("partA")
        partB.setQuantity(w3["partB"])
        PartInventory.updateInventory("partB")
        partC.setQuantity(w3["partC"])
        PartInventory.updateInventory("partC")
        partD.setQuantity(w3["partD"])
        PartInventory.updateInventory("partD")
    else:
        print("Widget CANNOT be built")
        if partA.getQuantity() <w3["partA"]:
            print("There is an insufficient amount of partA")
        if partB.getQuantity() <w3["partB"]:
            print("There is an insufficient amount of partB")
        if partC.getQuantity() <w3["partC"]:
            print("There is an insufficient amount of partC")
        if partD.getQuantity() <w3["partD"]:
            print("There is an insufficient amount of partD")
    print("")

    #widget4
    print("WIDGET 4")
    if partA.getQuantity() >= w4["partA"] and partC.getQuantity() >= w4["partC"] and partD.getQuantity() >= w4["partD"]:
        print("Widget CAN be built.")
        for element in w4:
            print(w4[element], "of", element, "used")
        cost4 = w4["partA"]*partA.getPrice() + w4["partC"]*partC.getPrice() + w4["partD"]*partD.getPrice()
        print("Cost: $", "%.2f" % cost4)
        partA.setQuantity(w4["partA"])
        PartInventory.updateInventory("partA")
        partC.setQuantity(w4["partC"])
        PartInventory.updateInventory("partC")
        partD.setQuantity(w4["partD"])
        PartInventory.updateInventory("partD")
    else:
        print("Widget CANNOT be built.")
        if partA.getQuantity() <w4["partA"]:
            print("There is an insufficient amount of partA")
        if partC.getQuantity() <w4["partC"]:
            print("There is an insufficient amount of partC")
        if partD.getQuantity() <w4["partD"]:
            print("There is an insufficient amount of partD")
        print("")

    #widget5
    print("WIDGET 5")
    if partA.getQuantity() >= w5["partA"] and partD.getQuantity() >= w5["partD"]:
        print("Widget CAN be built.")
        for element in w5:
            print(w5[element], "of", element, "used")
        cost5 = w5["partA"]*partA.getPrice() + w5["partD"]*partD.getPrice()
        print("Cost: $", "%.2f" % cost5)
        partA.setQuantity(w5["partA"])
        PartInventory.updateInventory("partA")
        partD.setQuantity(w5["partD"])
        PartInventory.updateInventory("partD")
    else:
        print("Widget CANNOT be built.")
        if partA.getQuantity() <w5["partA"]:
            print("There is an insufficient amount of partA")
        if partD.getQuantity() <w5["partD"]:
            print("There is an insufficient amount of partD")
    print("")

    #removing parts with inventory of 0
    if partA.getQuantity() == 0:
        PartInventory.removePart("partA")
    if partB.getQuantity() == 0:
        PartInventory.removePart("partB")
    if partC.getQuantity() == 0:
        PartInventory.removePart("partC")
    if partD.getQuantity() == 0:
        PartInventory.removePart("partD")
    if partE.getQuantity() == 0:
        PartInventory.removePart("partE")

    #final inventory output
    print("Final Parts Inventory")
    PartInventory.printInventory()

main()
