#include "linkedBTree.h"
#include <string>


template<class ItemType>
LinkedBTree<ItemType> :: LinkedBTree() : rootPtr(nullptr) {}

template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const
{
    if (subTreePtr == nullptr)
    {
        return 0;
    }
    int leftCount = getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
    int rightCount = getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
    int total = 1 + leftCount + rightCount;
    return total;
}

template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodes() const
{
   return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType LinkedBTree<ItemType>::getRootData() const
{
    return rootPtr->getItem();
}


template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>:: MoveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr) {
    if (subTreePtr == nullptr) {
        return nullptr;
    }

    if (subTreePtr->getLeftChildPtr() == nullptr) {
        LinkedTreeNode<ItemType>* temp = subTreePtr;
        subTreePtr = subTreePtr->getRightChildPtr();
        delete temp;
        return subTreePtr;
    }

    if (subTreePtr->getRightChildPtr() == nullptr) {
        LinkedTreeNode<ItemType>* temp = subTreePtr;
        subTreePtr = subTreePtr->getLeftChildPtr();
        delete temp;
        return subTreePtr;
    }

    LinkedTreeNode<ItemType>* temp = subTreePtr->getLeftChildPtr();
    subTreePtr->setLeftChildPtr(MoveValuesUpTree(subTreePtr->getRightChildPtr()));
    subTreePtr->setRightChildPtr(nullptr);
    delete subTreePtr;
    return temp;
}

template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>:: removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful)
{
    if (subTreePtr == nullptr)
    {   
        isSuccessful = false;
        return subTreePtr;
    }
    else
    {
        if (subTreePtr->getItem() == target)
        {
            if (subTreePtr->isLeaf())
            {
                LinkedTreeNode<ItemType>* temp = subTreePtr;
                subTreePtr = nullptr;
                delete temp;
                isSuccessful = true;
                return nullptr;
                
            }
            else if (subTreePtr->getRightChildPtr() == nullptr) 
                {
                    LinkedTreeNode<ItemType>* temp = subTreePtr->getLeftChildPtr();
                    subTreePtr = nullptr;
                    delete temp;
                    isSuccessful = true;
                    return subTreePtr;
                }
            else if (subTreePtr->getLeftChildPtr() == nullptr)
                {
                    LinkedTreeNode<ItemType>* temp = subTreePtr->getRightChildPtr();
                    subTreePtr = nullptr;
                    delete temp;
                    isSuccessful = true;
                    return subTreePtr;
                }
            else
            {   
                LinkedTreeNode<ItemType>* temp = subTreePtr;
                if ((getHeightHelper(subTreePtr->getLeftChildPtr())) > (getHeightHelper(subTreePtr->getRightChildPtr())))
                {
                   subTreePtr = MoveValuesUpTree(subTreePtr->getLeftChildPtr());
                   subTreePtr = nullptr;
                   isSuccessful = true;
                   delete temp;
                   return subTreePtr;
                }
                else
                {
                   subTreePtr = MoveValuesUpTree(subTreePtr->getRightChildPtr());
                   subTreePtr = nullptr;
                   delete temp;
                   isSuccessful = true;
                   return subTreePtr;
                }
            }
        }
    }
    return subTreePtr;
}


template<class ItemType>
bool LinkedBTree<ItemType>::remove(const ItemType& data)
{
    bool isSuccessful;
    LinkedTreeNode<ItemType>* temp = removeValue(rootPtr, data, isSuccessful);
    if (isSuccessful)
    {
        return true;
    }
    return false;
}

template<class ItemType>
void LinkedBTree<ItemType>::destroyTree(LinkedTreeNode<ItemType>* subTreePtr)
{
    if (subTreePtr != nullptr)
    {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        subTreePtr = nullptr;
        delete subTreePtr;
    }
}

template<class ItemType>
void LinkedBTree<ItemType>::clear()
{
    destroyTree(rootPtr);
    rootPtr = nullptr;
}

template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::findNode(LinkedTreeNode<ItemType>*subTreePtr, const ItemType& target, bool& isSuccessful) const
{
    if (subTreePtr == nullptr)
    {
        isSuccessful = false;
        return nullptr;
    }
    if (subTreePtr->getItem() == target)
    {   
        isSuccessful = true;
        return subTreePtr;
    }
    LinkedTreeNode<ItemType>* tempLeft = findNode(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        if (isSuccessful)
        {
            return tempLeft;
        }
    return findNode(subTreePtr->getRightChildPtr(), target, isSuccessful);
}

template<class ItemType>
ItemType LinkedBTree<ItemType>:: getEntry(const ItemType& anEntry) const
{
    bool isSuccessful;

    LinkedTreeNode<ItemType>* result = findNode(rootPtr, anEntry, isSuccessful);
    if (result == nullptr)
    {
        throw std::string("Cannot locate entry");
    }
    else
    {
        return result->getItem();
    }
}

template<class ItemType>
bool LinkedBTree<ItemType>:: contains(const ItemType& anEntry) const
{
    bool isSuccessful;
    LinkedTreeNode<ItemType>* temp = findNode(rootPtr, anEntry, isSuccessful);
    if (isSuccessful)
    {
        return true;
    }
    return false;
}

template<class ItemType>
int LinkedBTree<ItemType>::getHeight() const
{
    return getHeightHelper(rootPtr);
}

template<class ItemType>
int LinkedBTree<ItemType>::getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr) const
{
    if (subTreePtr == nullptr)
    {
    return 0;
    }
    else
    {
        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
    }
}

template<class ItemType>
bool LinkedBTree<ItemType>::isEmpty() const
{
    if (rootPtr == nullptr)
    {
        return true;
    }
    return false;
}

template<class ItemType>
bool LinkedBTree<ItemType>::add(const ItemType& newData)
{   
    LinkedTreeNode<ItemType>* newDataPtr = new LinkedTreeNode<ItemType>(newData);
    rootPtr = balancedAdd(rootPtr, newDataPtr);
    return true;
}

template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>:: balancedAdd(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr)
{
    if(subTreePtr == nullptr)
    {
        return newNodePtr;
    }
    else
    {
        if (getHeightHelper(subTreePtr->getLeftChildPtr()) < (getHeightHelper(subTreePtr->getRightChildPtr())))
        {
            subTreePtr->setLeftChildPtr(balancedAdd(subTreePtr->getLeftChildPtr(),newNodePtr));
        }
        else
        {
            subTreePtr->setRightChildPtr(balancedAdd(subTreePtr->getRightChildPtr(),newNodePtr));
        }
    }
    return subTreePtr;
}