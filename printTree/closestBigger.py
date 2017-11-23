#!/bin/python
#Find the closest Bigger value in the tree. 

import random


class Node(object):
    def __init__(self, value=None, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right


class BinaryTree(object):
    def __init__(self):
        self.root = Node()

    def add_node(self, value):
        # Empty Tree
        if self.root.value == None:
            self.root.value = value
        else:
            newNode = Node(value=value)
            myQueue  = [self.root] 
            while myQueue:
                curNode = myQueue.pop(0)
                if curNode.value >= value and curNode.left is None:
                    curNode.left = newNode
                    return
                elif curNode.value >= value:
                    myQueue.append(curNode.left)
                elif curNode.value < value and curNode.right is None:
                    curNode.right = newNode
                    return
                elif curNode.value < value:
                    myQueue.append(curNode.right)


def traverseBinaryTree(root):
    if root is None:
        return

    traverseBinaryTree(root.left)
    print root.value
    traverseBinaryTree(root.right)


location = 0
result = dict()
def formatBinaryTree(root):
    global location
    location = location + 1
    if root is None:
        location = location - 1
        return

    if location not in result.keys():
        result[location] = [root.value]
    else:
        result[location].append(root.value)

    formatBinaryTree(root.left)
    formatBinaryTree(root.right)
    location = location - 1

def findclosestBigger(root, value):
    if root.value is None:
        return None


if __name__ == "__main__":
    numberOfLeaves = 10
    aTree = BinaryTree()
    # Construct the BinaryTree
    input_list =  random.sample(range(0, numberOfLeaves), numberOfLeaves)
    for i in input_list:
        print i
        aTree.add_node(i) 

    print "Begin to display values: "
    traverseBinaryTree(aTree.root)

    print "Begin to format in level"
    formatBinaryTree(aTree.root)
    global result
    i = 1
    while True:
        if i not in result.keys():
            break
        print result[i]
        i = i + 1
