#include "linkedBSTree.h"

template<class ItemType>
LinkedBSTree<ItemType> :: LinkedBSTree() : rootPtr(nullptr) {}




template<class ItemType>
bool LinkedBSTree<ItemType>::add(const ItemType& newData)
{
    LinkedTreeNode<ItemType>* newDataPtr = new LinkedTreeNode<ItemType>(newData);
    rootPtr = placeNode(rootPtr, newDataPtr);
    return true;
}

template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBSTree<ItemType> :: placeNode(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr)
{
    if (subTreePtr == nullptr)
    {
        return newNodePtr;
    }
    else if (newNodePtr->getItem() < subTreePtr->getItem())
    {
        subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
    }
    else
    {
        subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));
    }
    return subTreePtr;
}


template<class ItemType>
LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful)
{
    if (subTreePtr == nullptr)
    {
        isSuccessful = false;
        return nullptr;
    }
    if (target < subTreePtr->getItem())
    {
        subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target));
    }
    else if (target > subTreePtr->getItem())
    {
        subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target));
    }
    else
    {
        if (subTreePtr->isLeaf())
        {
            LinkedTreeNode<ItemType>* temp = subTreePtr;
            subTreePtr = nullptr;
            delete temp;
            isSuccessful = true;
            return subTreePtr;
        }
        else if (subTreePtr->getLeftChildPtr = nullptr)
        {
            LinkedTreeNode<ItemType>* temp = subTreePtr->getRightChildPtr();
            subTreePtr = nullptr;
            isSuccessful = true;
            return temp;
        }
        else if (subTreePtr->getRightChildPtr = nullptr)
        {
            LinkedTreeNode<ItemType>* temp = subTreePtr->getLeftChildPtr();
            subTreePtr = nullptr;
            isSuccessful = true;
            return temp;
        }
    }
}


