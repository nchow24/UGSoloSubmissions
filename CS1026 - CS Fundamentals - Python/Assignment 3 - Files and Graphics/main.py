# nchow24, 250725575 (Nicole Anne Chow)
#analysis of happiness levels via tweets

#getting keywords file
keywordsFile = str(input("Enter the name of your file containing the keywords: ")) + ".txt"
try:
    keywords = open(keywordsFile, "r")
except IOError:
    print("File does not exist")

#creating list of keywords and corresponding happiness scores
keywordsList = []
happinessList = []
for line in keywords:
    line = line.split(",")
    for string in line:
        string = string.strip("\n")
        if string.isdigit():
            string = int(string)
            happinessList.append(string)
        else:
            string = str(string)
            keywordsList.append(string)

keywords.close()

#geting tweets file
tweetsFile = str(input("Enter the name of the file containing the tweets:")) + ".txt"
try:
    tweets = open(tweetsFile, "r", encoding="utf-8")
except IOError:
    print("File does not exist")

#creating lists of all latitudes, longitudes, and tweets
allLatitude = []
allLongitude = []
allTweets = []

for line in tweets:
    line = line.strip("[")
    allLatitude.append(line.split(",", 1)[0])
    allLatitude = [float(i) for i in allLatitude]
    line = line.strip(line.split(",", 1)[0])
    line = line.strip(", ")
    allLongitude.append(line.split("] ", 1)[0])
    allLongitude = [float(i) for i in allLongitude]
    line = line.strip(line.split("]", 1)[0])
    line = line[24:]
    allTweets.append(line.lower())

tweets.close()

#calculatng individual happiness scores and creating a list
allScore = []
t = 0
while t < len(allTweets):
    happinessScore = 0
    wordCount = 0
    i = 0
    while i < len(keywordsList):
        if keywordsList[i] in allTweets[t]:
            happinessScore = happinessScore + happinessList[i]
            wordCount = wordCount + 1
        i = i + 1
    if wordCount == 0:
        finalScore = 0
    else:
        finalScore = happinessScore/wordCount
    allScore.append(finalScore)
    t = t +1

#extracting tweets with keyword(s)
j = 0
keywordsPositions = []
while j < len(allScore):
    if allScore[j] != 0:
        keywordsPositions.append(j)
    j = j +1

extractedLatitude = []
extractedLongitude = []
extractedTweets = []
extractedScore = []
for position in keywordsPositions:
    extractedLatitude.append(allLatitude[position])
    extractedLongitude.append(allLongitude[position])
    extractedTweets.append(allTweets[position])
    extractedScore.append(allScore[position])

#compiling indiviudal scores within timezones
easternScores = []
centralScores = []
mountainScores = []
pacificScores = []

k = 0
while k < len(extractedLatitude):
    if 24.6608452 <= extractedLatitude[k] <= 49.1889787:
        if 67.444574 < abs(extractedLongitude[k]) < 87.518395:
            easternScores.append(extractedScore[k])
        if 87.518395 < abs(extractedLongitude[k]) < 101.998892:
            centralScores.append(extractedScore[k])
        if 101.998892 < abs(extractedLongitude[k]) < 115.236428:
            mountainScores.append(extractedScore[k])
        if 115.236428 < abs(extractedLongitude[k]) < 124.242264:
            pacificScores.append(extractedScore[k])
    k = k + 1

#calcluating averages among each timezone
easternTotal = 0
centralTotal = 0
mountainTotal = 0
pacificTotal = 0

for score in easternScores:
    easternTotal = easternTotal + score
for score in centralScores:
    centralTotal = centralTotal + score
for score in mountainScores:
    mountainTotal = mountainTotal + score
for score in pacificScores:
    pacificTotal = pacificTotal + score

easternAverage = easternTotal / len(easternScores)
centralAverage = centralTotal / len(centralScores)
mountainAverage = mountainTotal / len(mountainScores)
pacificAverage = pacificTotal / len(pacificScores)

#Printing final results
print("Eastern Timezone:")
print("Number of Tweets:", len(easternScores))
print("Average Happiness Score:", easternAverage, "\n")

print("Central Timezone:")
print("Number of Tweets:", len(centralScores))
print("Average Happiness Score:", centralAverage, "\n")

print("Mountain Timezone:")
print("Number of Tweets:", len(mountainScores))
print("Average Happiness Score:", mountainAverage, "\n")

print("Pacific Timezone:")
print("Number of Tweets:", len(pacificScores))
print("Average Happiness Score:", pacificAverage, "\n")

from happy_histogram import drawSimpleHistogram
eval = easternAverage
cval = centralAverage
mval = mountainAverage
pval = pacificAverage
print(drawSimpleHistogram(eval, cval, mval, pval))