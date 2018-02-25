# class HashDouble is a class of a double hashing table containing _MapEntry.Pair()s
#
# Empty cells are denoted as a Pair with a key of 0
# REMOVED values are denoted as a Pair with a key of -1
#
# Nicole Chow    (nchow24, 250725575)
# Feb 8, 2018

import _MapEntry

class HashDouble:

    def __init__(self):
        self.size = 1000003
        self.table = [_MapEntry.Pair(0, None)] * self.size

    #inserts a pair and returns the number of probes needed for the insertion, otherwise return -2 if table is full
    def insert(self, pair):
        newKey = abs(hash(pair.getKey())) % self.size
        probe = 1

        #probe until empty slot is found
        while (probe <= self.size and self.table[newKey].getKey() != 0 and self.table[newKey].getKey() != -1):
                newKey = (newKey + (1 + (abs(hash(pair.getKey())) % (self.size - 2) ))) % self.size
                probe = probe + 1

        #insert unless table is full
        if probe <= self.size:
            self.table[newKey] = pair
            return probe
        else:
            return -2


    #returns number of probes needed if key is found in table, otherwise -2
    def find(self, key):
        newKey = abs(hash(key)) % self.size
        probe = 1

        #probe until we find key or reach an empty cell or exhaust the table
        while (probe <= self.size and self.table[newKey].getKey() != 0 and self.table[newKey].getKey() != key):
            newKey = (newKey + (1 + (abs(hash(key)) % (self.size - 2)))) % self.size
            probe = probe + 1

        # check if the key is found
        if (self.table[newKey].getKey() == key):
            return probe
        else:
            return -2


    #returns index of table that holds key if key is in table, otherwise -2
    def findIndex(self, key):
        newKey = abs(hash(key)) % self.size
        probe = 1

        #probe until we find key or reach an empty cell or exhaust the table
        while (probe <= self.size and self.table[newKey].getKey() != 0 and self.table[newKey].getKey() != key):
            newKey = (newKey + (1 + (abs(hash(key)) % (self.size - 2)))) % self.size
            probe = probe + 1

        # check if the key is found
        if (self.table[newKey].getKey() == key):
            return newKey
        else:
            return -2


    #removes a key (if it exists) by replacing it with a REMOVED value
    def remove(self, key):
        found = self.findIndex(key)
        if (found != -2):
            self.table[found].setKey(-1)
            return 1
        else:
            return 0