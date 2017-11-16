#!/bin/python
#Print the Binary Tree replace the depth with the number of the rows
# For example
#       5
#     /  \
#    3   6
#   / \
#  4   5
# Print the Tree:
# 5
# 3 6
# 4 5

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
        else: # Not empty Tree
            newNode = Node(value=value)
            myQueue = list()

            myQueue.append(self.root)
            while myQueue:
                curNode = myQueue.pop(0)
                if curNode.left is None:
                    curNode.left = newNode
                    return
                elif curNode.right is None:
                    curNode.right = newNode
                    return
                else:
                    myQueue.append(curNode.left)
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

if __name__ == "__main__":
    numberOfLeaves = 10
    aTree = BinaryTree()
    # Construct the BinaryTree
    for i in range(numberOfLeaves):
        print i
        aTree.add_node(i) 

    print "Begin to display values: "
    traverseBinaryTree(aTree.root)

    print "Begin to format"
    formatBinaryTree(aTree.root)
    global result
    i = 1
    while True:
        if i not in result.keys():
            break
        print result[i]
        i = i + 1
