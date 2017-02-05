class Node(object):
    def __init__(self, value=None, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

class Tree(object):
    def __init__(self):
        self.root = Node()

    def add_node(self, value):
        #import pdb; pdb.set_trace()
        node = Node(value=value)
        if self.root.value is None:
            self.root = node
        else:
            myQueue = list()
            treeNode = self.root
            myQueue.append(treeNode)
            while myQueue:
                treeNode = myQueue.pop(0)
                if treeNode.left is None:
                    treeNode.left = node
                    return
                elif treeNode.right is None:
                    treeNode.right = node
                    return
                else:
                    myQueue.append(treeNode.left)
                    myQueue.append(treeNode.right)

# Traverse with recursion
def preTraverse(root):
    if root is None:
        return
    print root.value
    preTraverse(root.left)
    preTraverse(root.right)

def midTraverse(root):
    if root is None:
        return
    midTraverse(root.left)
    print root.value
    midTraverse(root.right)

def afterTraverse(root):
    if root is None:
        return
    afterTraverse(root.left)
    afterTraverse(root.right)
    print root.value

# Traverse with stack
def preStack(root):
    if root is None:
        return

    myStack = list()
    node = root
    while node or myStack:
        while node:
            print node.value
            myStack.append(node)
            node = node.left
        node = myStack.pop() 
        node = node.right

def midStack(root):
    if root is None:
        return

    myStack = list()
    node = root
    while node or myStack:
        while node:
            myStack.append(node)
            node = node.left
        node = myStack.pop() 
        print node.value
        node = node.right

def afterStack(root):
    if root is None:
        return

    myStack = list()
    myStack2 = list()
    node = root
    myStack.append(node)
    while myStack:
        node = myStack.pop()
        if node.left is not None:
            myStack.append(node.left)
        if node.right is not None:
            myStack.append(node.right)
        myStack2.append(node)
    while myStack2:
        print myStack2.pop().value

if __name__ == '__main__':
    myTree = Tree()
    for i in range(0, 5):
        print "add value to tree %s" % i
        myTree.add_node(i)

    #import pdb; pdb.set_trace()
    print "preTraverse process: "
    preTraverse(myTree.root)
    print "pre with stack"
    preStack(myTree.root)

    print "midTraverse process:"
    midTraverse(myTree.root)
    print "mid with stack"
    midStack(myTree.root)

    print "afterTraverse process:"
    afterTraverse(myTree.root)
    print "after with stack"
    afterStack(myTree.root)
