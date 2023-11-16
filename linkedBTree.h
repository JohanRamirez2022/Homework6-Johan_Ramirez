#ifndef LINKED_BTREE
#define LINKED_BTREE

#include "tree.h"
#include "linkedtreenode.h"
#include <algorithm>

using namespace std;

template<class ItemType>
class LinkedBTree: public TreeInterface<ItemType>{
private:
LinkedTreeNode<ItemType>* rootPtr;

public:
LinkedBTree();
bool isEmpty() const;
int getHeight() const;
int getNumberOfNodes() const;
ItemType getRootData() const;
bool add(const ItemType& newData);
bool remove(const ItemType& data);
void clear();
ItemType getEntry(const ItemType& anEntry) const;
bool contains(const ItemType& anEntry) const;


protected:
int getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr) const;

int getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const;

LinkedTreeNode<ItemType>* balancedAdd(LinkedTreeNode<ItemType>*
subTreePtr, LinkedTreeNode<ItemType>* newNodePtr);

LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>*
subTreePtr, const ItemType target, bool& isSuccessful);

LinkedTreeNode<ItemType>*
MoveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr);

LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>*
subTreePtr, const ItemType& target, bool& isSuccessful) const;

void destroyTree(LinkedTreeNode<ItemType>* subTreePtr);
};

#include "linkedBTree.cpp"

#endif
