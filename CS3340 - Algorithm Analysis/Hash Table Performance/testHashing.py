# testHashing.py is a main file that tests the performance of class HashLinear and class HashDouble
#
# Nicole Chow    (nchow24, 250725575)
# Feb 8, 2018

import random
import _MapEntry
import HashTable_LinearProbing
import HashTable_DoubleHashing

load = [0.25, .5, 2/3.0, .75, .8, .9, .95]
size = 1000003

data = [0] * size
for i in range (0, len(data)):
    data[i] = random.randint(1, 1000000000)

linearTable = HashTable_LinearProbing.HashLinear()
doubleTable = HashTable_DoubleHashing.HashDouble()

currentLoad = 0

print("Average probes:\n")

for x in range (0, len(load)):
    #fill to next load
    print("load factor = " + str(load[x]))
    for y in range (int(round(currentLoad * size)), int(round(load[x] * size))):
        linearTable.insert(_MapEntry.Pair(data[y], None))
        doubleTable.insert(_MapEntry.Pair(data[y], None))
    currentLoad = load[x]


    #sucessful search
    print("  sucessful search:")
    sumProbesLinear = 0
    sumProbesDouble = 0
    for a in range(0, int(round(0.01 * size))):
        key = data[random.randint(0, int(round(currentLoad*size)))]
        sumProbesLinear = sumProbesLinear + linearTable.find(key)
        sumProbesDouble = sumProbesDouble + doubleTable.find(key)


    print("linear probing:      " + "%.2f" % (sumProbesLinear / int(round(0.01 * size))))
    print("double hashing:      " + "%.2f" % (sumProbesDouble / int(round(0.01 * size))))

    #unsucessful search
    print("  unsucessful search:")
    sumProbesLinear = 0
    sumProbesDouble = 0
    for b in range(int(round(currentLoad*size)), int(round((currentLoad + 0.01)*size))):
        key = data[b]
        sumProbesLinear = sumProbesLinear + linearTable.insert(_MapEntry.Pair(key, None))
        sumProbesDouble = sumProbesDouble + doubleTable.insert(_MapEntry.Pair(key, None))
    currentLoad = currentLoad + 0.01

    print("linear probing:      " + "%.2f" % (sumProbesLinear / int(round(0.01 * size))))
    print("double hashing:      " + "%.2f" % (sumProbesDouble / int(round(0.01 * size))) + "\n")
