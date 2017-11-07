#/bin/python

import re


def string2Word(data):
    words = re.split('[\W0-9_]+', data)
    words.remove('')
    print "words = {}".format(words)

    # init the hash map
    wordMap = dict()
    for word in words:
        if word not in wordMap.keys():
            wordMap[word] = 1
        else:
            wordMap[word] = wordMap[word] + 1

    print "wordMap = {}".format(wordMap)
        
        
    

if __name__ == "__main__":
    print "Begint to Calc"
    filename = "./text.file"
    with open(filename, 'r') as fin:
        data = fin.read()
        print "data = {}".format(data) 

    string2Word(data)
