# 3340 Assignment 3 Q7
# Nicole Chow  (nchow24 250725575)
# Mar 13, 2018

import sys

# get and parse files
f1 = open(sys.argv[1],"r")
f2 = open(sys.argv[2],"r")
string1 = []
string2 = []
for line in f1:
    line = line.replace("\n", " ")
    string1.extend(line)
for line in f2:
    line = line.replace("\n", " ")
    string2.extend(line)

#create matrix
matrix = [[0 for x in range(len(string2)+1)] for y in range(len(string1)+1)]
for i in range(len(string1)+1):
    for j in range(len(string2)+1):

        # j edits needed from string2 if string1 == NULL
        if i == 0: matrix[i][j] = j

        # i edits needed from string1 if string2 == NULL
        elif j == 0: matrix[i][j] = i

        # take diagonal if characters match
        elif string1[i - 1] == string2[j - 1]: matrix[i][j] = matrix[i - 1][j - 1]

        #get value from min of top, left and diagonal cells
        else: matrix[i][j] = 1 + min(matrix[i][j - 1], matrix[i - 1][j], matrix[i - 1][j - 1])

#3 rows of the alignment
align1 = []
align2 = []
align3 = []

# get alignment
i = len(string1)
j = len(string2)
while (i != 0 or j != 0):

    # get values of top, left and diagonal cell
    # if cells don't exist, set a value to 1 + edit distance so it won't be chosen as the minimum
    if i == 0:
        top = matrix[len(string1)][len(string2)] + 1
        diag = matrix[len(string1)][len(string2)] + 1
    else: top = matrix[i - 1][j]

    if j == 0:
        left = matrix[len(string1)][len(string2)] + 1
        diag = matrix[len(string1)][len(string2)] + 1
    else: left = matrix[i][j - 1]

    if (i!= 0 and j != 0): diag = matrix[i-1][j-1]
    minimum = min(top, diag, left)

    # diagonal cell: replace or match character (add both)
    if (diag == minimum or string1[i-1] == string2[j-1] ):
        align1 = [string1[i-1]] + align1
        align3 = [string2[j-1]] + align3
        if (string1[i - 1] == string2[j - 1]): align2 = ["|"] + align2
        else: align2 = [" "] + align2
        i = i-1
        j = j-1

    # top cell: add gap to string2 and character from string 1
    elif top == minimum:
        align1 = [string1[i-1]] + align1
        align2 = [" "] + align2
        align3 = ["-"] + align3
        i = i-1

    # left cell: add gap to string 1 and character from string2
    else:
        align1 = ["-"] + align1
        align2 = [" "] + align2
        align3 = [string2[j-1]] + align3
        j = j-1

# print output
print("\noptimal alignment:\n")

# parse lines if length > 60
if (len(align1)>60):
    counter = len(align1)//60
    for i in range (0, counter):
        for j in range (i*60, (i+1)*60): print(align1[j], end=" ")
        print("")
        for j in range (i*60, (i+1)*60): print(align2[j], end=" ")
        print("")
        for j in range (i*60, (i+1)*60): print(align3[j], end=" ")
        print("\n")
    for j in range (counter*60, len(align1)): print(align1[j], end=" ")
    print("")
    for j in range (counter*60, len(align1)): print(align2[j], end=" ")
    print("")
    for j in range (counter*60, len(align1)): print(align3[j], end=" ")
    print("\n")
else:
    for i in align1: print(i, end=" ")
    print("")
    for i in align2: print(i, end=" ")
    print("")
    for i in align3: print(i, end=" ")
    print("\n")

print("edit distance = " + str(matrix[len(string1)][len(string2)]))
