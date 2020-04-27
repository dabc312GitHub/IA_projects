from binarytree import Node
root = Node(3)
root.left = Node(6)
root.right = Node(8)

# Getting binary tree
print('Binary tree :', root)

root.pprint(index=True)
print('Binary tree :', root)

var = root.left
var.left = Node(22)
root.pprint(index=True)
del root[1]

print('Binary tree :', root)


# Getting list of nodes
print('List of nodes :', list(root), "\n")

# Getting inorder of nodes
print('Inorder of nodes :', root.inorder, "\n")

# Checking tree properties
print('Size of tree :', root.size)
print('Height of tree :', root.height, "\n")

# Get all properties at once
print('Properties of tree : \n', root.properties, "\n")
