#ifndef LINKED_BSEARCHTREE
#define LINKED_BSEARCHTREE

#include "linkedtreenode.h"
#include "linkedBTree.h"

template <class ItemType>
class LinkedBSTree: public LinkedBTree <ItemType>
{
    private:
    LinkedTreeNode<ItemType>* rootPtr;
    
    protected:
    LinkedTreeNode<ItemType>* placeNode(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr);
    
    LinkedTreeNode<ItemType>* removeNode(LinkedTreeNode<ItemType>* nodePtr);

    LinkedTreeNode<ItemType>* removeLeftmostNode(LinkedTreeNode<ItemType>* nodePtr, ItemType& inorderSuccessor);

    LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>* treePtr, const ItemType& target) const;

    void preorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const;

    void inorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const;

    void postorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const;

    public:
    LinkedBSTree();

    bool add(const ItemType& newData) override;
};


#include "linkedBSTree.cpp"
#endif