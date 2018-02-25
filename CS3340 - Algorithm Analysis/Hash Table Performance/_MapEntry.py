# class pair is a class of a key and value to be inserted in the hash tables
#
# Nicole Chow    (nchow24, 250725575)
# Feb 8, 2018

class Pair:

    def __init__(self, key, value):
        self.key = key
        self.value = value

    #returns the key
    def getKey(self):
        return self.key

    #returns the value
    def getValue(self):
        return self.value

    #set the key
    def setKey(self, newKey):
        self.key = newKey

    #sets the value
    def setValue(self, newValue):
        self.value = newValue
