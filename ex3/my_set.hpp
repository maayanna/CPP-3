/**
 * @file my_set.hpp
 * @author  Maayann Affriat <maayann.affriat@mail.huji.ac.il>
 * @version 2.0
 * @date 20 sep 2018
 *
 * @brief
 *
 * @section LICENSE
 * This program is not a free software.
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes --------------------------

#ifndef EX3_MY_SET_HPP
#define EX3_MY_SET_HPP

#include "my_set.h"
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

/**
 * Node constructor
 * @tparam T
 * @param dt
 */
template<typename T>
Node<T>::Node(T dt)
    {
        _data = dt;
        _father = nullptr;
        _right = nullptr;
        _left = nullptr;
    }

/**
 * Return the data
 * @tparam T
 * @return
 */
template<typename T>
T Node<T>::getData()
    {
        return _data;
    }

/**
 * return the parent node
 * @tparam T
 * @return
 */
template<typename T>
shared_ptr<Node<T>> Node<T>::getFather()
    {
        return _father;
    }

/**
 * Return the right son
 * @tparam T
 * @return
 */
template<typename T>
shared_ptr<Node<T>> Node<T>::getRight()
    {
        return _right;
    }

/**
 * return th eleft son
 * @tparam T
 * @return
 */
template<typename T>
shared_ptr<Node<T>> Node<T>::getLeft()
    {
        return _left;
    }

/**
 * set the parent node
 * @tparam T
 * @param node
 */
template<typename T>
void Node<T>::setFather(shared_ptr<Node<T>> node)
    {
        _father = node;
    }

/**
 * set the left son
 * @tparam T
 * @param node
 */
template<typename T>
void Node<T>::setLeft(shared_ptr<Node<T>> node)
    {
        _left = node;
    }

/**
 * set the right son
 * @tparam T
 * @param node
 */
template<typename T>
void Node<T>::setRight(shared_ptr<Node<T>> node)
    {
        _right = node;
    }

/**
 * set thedat a
 * @tparam T
 * @param data
 */
template<typename T>
void Node<T>::setData(T data)
    {
        _data = data;
    }

/**
 * set constructor
 * @tparam T
 */
template<typename T>
my_set<T>::my_set()
    {
        _size = 0;
        _root = nullptr;
    }

/**
 * copy constructor
 * @tparam T
 * @param other
 */
template<typename T>
//Copy constructor
my_set<T>::my_set(const my_set &other)
    {
        _size = 0;
        _root = nullptr;
        iterator it;
        for (it = other.cbegin(); it != other.cend(); it++)
            {
                insert(*it);
            }
    }

/**
 * Moove constructor
 * @tparam T
 * @param other
 */
template<typename T>
my_set<T>::my_set(my_set &&other) noexcept //Move constructor
    {
        _size = 0;
        _root = nullptr;
        for (iterator it = other.cbegin(); it != other.cend(); ++it)
            {
                insert(*it);
            }
        other._root = nullptr;
        other._size = 0;
    }

/**
 * Operator copy =
 * @tparam T
 * @param other
 * @return
 */
template<typename T>
my_set<T> &my_set<T>::operator=(const my_set &other)
    {
        if (!other._root)
            {
                _root = nullptr;
                _size = 0;
                return *this;
            }
        if (&other == this)
            {
                return *this;
            }
        clear();
        _size = 0;
        _root = nullptr;
        for (iterator it = other.cbegin(); it != other.cend(); ++it)
            {
                insert(*it);
            }

        return *this;
    }

/**
 * Moove operator =
 * @tparam T
 * @param other
 * @return
 */
template<typename T>
my_set<T> &my_set<T>::operator=(my_set &&other) noexcept
    {
        if (&other == this)
            {
                return *this;
            }
        clear();
        _size = 0;
        _root = nullptr;
        for (iterator it = other.cbegin(); it != other.cend(); ++it)
            {
                insert(*it);
            }
        other._root = nullptr;
        other._size = 0;
        return *this;
    }

/**
 * destructor
 * @tparam T
 */
template<typename T>
my_set<T>::~my_set()
    {
        clear();
    }

/**
 * begin for iterator
 * @tparam T
 * @return
 */
template<typename T>
typename my_set<T>::const_iterator my_set<T>::cbegin() const
    {
        std::shared_ptr<Node<T>> node = doMin();
        return const_iterator(node, false);
    }


/**
 * end for const iterator
 * @tparam T
 * @return
 */
template<typename T>
typename my_set<T>::const_iterator my_set<T>::cend() const noexcept
    {
        return const_iterator(nullptr, false);
    }

/**
 * constructor of set with iterator
 * @tparam T
 * @tparam InputIterator
 * @param beg
 * @param end
 */
template<typename T>
template<class InputIterator>
my_set<T>::my_set(InputIterator beg, InputIterator end)
    {
        _size = 0;
        _root = nullptr;

        for (beg; beg != end; beg++)
            {
                insert(*beg);
            }
    }

/**
 * find max
 * @tparam T
 * @return
 */
template<typename T>
shared_ptr<Node<T>> my_set<T>::doMax() const
    {
        shared_ptr<Node<T>> current = _root;

        while (current->getRight() != nullptr)
            {
                current = current->getRight();
            }
        return current;
    }

/**
 * find min
 * @tparam T
 * @return
 */
template<typename T>
shared_ptr<Node<T>> my_set<T>::doMin() const
    {
        shared_ptr<Node<T>> current = _root;

        if (current != nullptr)
            {
                while (current->getLeft() != nullptr)
                    {
                        current = current->getLeft();
                    }
            }

        return current;
    }

/**
 * begin for reverse iterator
 * @tparam T
 * @return
 */
template<typename T>
typename my_set<T>::const_iterator my_set<T>::crbegin() const
    {
        shared_ptr<Node<T>> minNode = doMax();
        return iterator(minNode, true);
    }


/**
 * end for reverse const iterator
 * @tparam T
 * @return
 */
template<typename T>
typename my_set<T>::const_iterator my_set<T>::crend() const
    {
        return const_iterator(nullptr, true);
    }

/**
 * If empty
 * @tparam T
 * @return
 */
template<typename T>
bool my_set<T>::empty() const
    {
        return (_size == 0);
    }

/**
 * the size of the set
 * @tparam T
 * @return
 */
template<typename T>
size_t my_set<T>::size() const
    {
        return _size;
    }

/**
 * Swap two sets
 * @tparam T
 * @param one
 * @param two
 */
template<class T>
void swap(my_set<T> &one, my_set<T> &two)
    {
        my_set<T> temp = one;
        one = two;
        two = temp;
    }

/**
 * Swap two sets
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
typename my_set<T>::const_iterator my_set<T>::find(const value_type &value) const
    {
        shared_ptr<Node<T>> myNode = findIt(value);
        if (myNode == nullptr)
            {
                return const_iterator(nullptr, false);
            }
        return const_iterator(value, false);
    }

/**
 * find a node
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
typename my_set<T>::iterator my_set<T>::find(const value_type &value)
    {
        shared_ptr<Node<T>> myNode = findIt(value);
        shared_ptr<Node<T>> node;
        node = myNode;
        return my_set<T>::iterator(node, false);
    }

/**
 * help for the insert
 * @tparam T
 * @param myNode
 * @param value
 * @return
 */
template<typename T>
pair<shared_ptr<Node<T>>, bool> my_set<T>::helperInsert(shared_ptr<Node<T>> myNode, const value_type &value)
    {
        if (findIt(value) == nullptr)
            {
                shared_ptr<Node<T>> current = myNode;
                shared_ptr<Node<T>> parent = nullptr;

                while (current != nullptr)
                    {
                        if (value < current->getData())
                            {
                                parent = current;
                                current = current->getLeft();
                            }
                        else
                            {
                                parent = current;
                                current = current->getRight();
                            }
                    }
                shared_ptr<Node<T>> newNode = make_shared<Node<T>>(value);
                newNode->setFather(parent);
                _size++;

                if (_root == nullptr)
                    {
                        _root = newNode;
                    }

                if (parent != nullptr)
                    {
                        if (value > parent->getData())
                            {
                                parent->setRight(newNode);
                            }
                        else
                            {
                                parent->setLeft(newNode);
                            }
                    }
                return (pair<shared_ptr<Node<T>>, bool>(newNode, true));
            }
        return (pair<shared_ptr<Node<T>>, bool>(nullptr, false));
    }

/**
 * find helper
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
shared_ptr<Node<T>> my_set<T>::findIt(const value_type &value) const
    {
        shared_ptr<Node<T>> currentNode = _root;
        while (currentNode != nullptr)
            {
                if (value < currentNode->getData())
                    {
                        currentNode = currentNode->getLeft();
                    }
                else if (value > currentNode->getData())
                    {
                        currentNode = currentNode->getRight();
                    }
                else
                    {
                        return currentNode;
                    }
            }
        return nullptr;
    }

/**
 * insert function
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
pair<typename my_set<T>::const_iterator, bool> my_set<T>::insert(const value_type &value)
    {
        pair<shared_ptr<Node<T>>, bool> myPair = helperInsert(_root, value);
        return pair<const_iterator, bool>(const_iterator(myPair.first, false), myPair.second);
    }

/**
 * insert function
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
pair<typename my_set<T>::const_iterator, bool> my_set<T>::insert(const value_type &&value)
    {
        pair<shared_ptr<Node<T>>, bool> myPair = helperInsert(_root, value);
        return pair<const_iterator, bool>(const_iterator(myPair.first, false), myPair.second);
    }

/**
 * insert function
 * @tparam T
 * @param pos
 * @param value
 * @return
 */
template<typename T>
typename my_set<T>::iterator my_set<T>::insert(my_set<T>::const_iterator pos, const value_type &value)
    {
        shared_ptr<Node<T>> myNode = pos.nextNode;
        pair<shared_ptr<Node<T>>, bool> myPair = helperInsert(myNode, value);
        if (myPair.second)
            {
                return iterator(myPair.first, false);
            }
        return iterator();
    }

/**
 * insert function
 * @tparam T
 * @param pos
 * @param value
 * @return
 */
template<typename T>
typename my_set<T>::const_iterator my_set<T>::insert(my_set<T>::const_iterator pos, const value_type &&value)
    {
        shared_ptr<Node<T>> myNode = pos.nextNode;
        pair<shared_ptr<Node<T>>, bool> myPair = helperInsert(myNode, value);
        if (myPair.second)
            {
                return const_iterator(myPair.first, false);
            }
        return const_iterator();
    }

/**
 * insert function
 * @tparam T
 * @param beg
 * @param end
 */
template<typename T>
void my_set<T>::insert(my_set<T>::iterator beg, my_set<T>::iterator end)
    {
        for (beg; beg != end; ++beg)
            {
                helperInsert(_root, beg); //By value
            }

    }

/**
 * helper to erase
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
pair<shared_ptr<Node<T>>, bool> my_set<T>::helperErase(const value_type &value)
    {
        shared_ptr<Node<T>> toDelete = findIt(value);

        if (toDelete != nullptr)
            {
                shared_ptr<Node<T>> successor;

                //No sons
                if (toDelete->getRight() == nullptr && toDelete->getLeft() == nullptr)
                    {

                        if (toDelete == _root)
                            {
                                _root = nullptr;
                                successor = nullptr;
                            }
                        else if (toDelete->getData() < toDelete->getFather()->getData())
                            {
                                toDelete->getFather()->setLeft(NULL);
                                successor = toDelete->getFather();
                            }
                        else
                            {
                                toDelete->getFather()->setRight(nullptr);
                                successor = toDelete->getFather();
                            }
                    }

                    //Only one son
                else if (toDelete->getRight() == nullptr)
                    {
                        if (toDelete == _root)
                            {
                                _root = _root->getLeft();
                                _root->setFather(nullptr);
                            }
                        toDelete->setData(toDelete->getLeft()->getData());
                        successor = toDelete->getLeft();
                        toDelete->setLeft(nullptr);
                    }
                else if (toDelete->getLeft() == nullptr)
                    {
                        if (toDelete == _root)
                            {
                                _root = _root->getRight();
                                _root->setFather(nullptr);
                            }
                        toDelete->setData(toDelete->getRight()->getData());
                        successor = toDelete->getRight();
                        toDelete->setRight(successor->getRight());
                        toDelete->setLeft(successor->getLeft());
                    }

                    //Two sons
                else
                    {
                        successor = successorFind(toDelete);
                        toDelete->setData(successor->getData());

                        if (successor->getFather()->getData() > successor->getData())
                            {
                                successor->getFather()->setLeft(successor->getRight());
                            }
                        else
                            {
                                successor->getFather()->setRight(successor->getRight());
                            }
                        if (successor->getRight() != nullptr)
                            {
                                successor->getRight()->setFather(successor->getFather());
                            }
                        if (toDelete == _root)
                            {
                                _root = toDelete;
                                _root->setFather(nullptr);
                            }
                    }
                _size--;
                return pair<shared_ptr<Node<T>>, bool>(_root, true);
            }
        return pair<shared_ptr<Node<T>>, bool>(nullptr, false);
    }

/**
 * find the successor
 * @tparam T
 * @param myNode
 * @return
 */
template<typename T>
shared_ptr<Node<T>> my_set<T>::successorFind(shared_ptr<Node<T>> myNode)
    {
        shared_ptr<Node<T>> successor = myNode->getRight();
        while (successor->getLeft() != nullptr)
            {
                successor = successor->getLeft();
            }
        return successor;
    }

/**
 * erase function
 * @tparam T
 * @param position
 * @return
 */
template<typename T>
typename my_set<T>::iterator my_set<T>::erase(my_set<T>::const_iterator position)
    {
        pair<shared_ptr<Node<T>>, bool> myPair = helperErase(position.nextNode->getData());
        return iterator(myPair.first, false);
    }

/**
 * erase function
 * @tparam T
 * @param value
 * @return
 */
template<typename T>
int my_set<T>::erase(const value_type &value)
    {
        pair<shared_ptr<Node<T>>, bool> myPair = helperErase(value);

        if (myPair.second)
            {
                return 1; //Number of erased node
            }
        return 0;
    }

/**
 * erase function
 * @tparam T
 * @param one
 * @param last
 * @return
 */
template<typename T>
typename my_set<T>::iterator my_set<T>::erase(my_set<T>::iterator one, my_set<T>::iterator last)
    {
        shared_ptr<Node<T>> successor = nullptr;

        for (one; one != last; ++one)
            {
                pair<shared_ptr<Node<T>>, bool> myPair = helperErase(one);
                successor = myPair.first;
            }
        return iterator(successor, false);
    }

/**
 * clearr the set
 * @tparam T
 */
template<typename T>
void my_set<T>::clear() noexcept
    {
        shared_ptr<Node<T>> toDelete = _root;
        while (toDelete != nullptr)
            {
                erase(toDelete->getData());
                toDelete = _root;
            }
    }

/**
 * swap two sets
 * @tparam T
 * @param other
 */
template<class T>
void my_set<T>::swap(my_set<T> &other)
    {
        my_set temp = *this;
        *this = other;
        other = temp;

    }

/**
 * find the max
 * @tparam T
 * @param myNode
 * @return
 */
template<typename T>
shared_ptr<Node<T>> Iter<T>::findMax(shared_ptr<Node<T>> myNode)
    {
        shared_ptr<Node<T>> current = myNode;
        shared_ptr<Node<T>> toReturn = myNode;

        while (current != nullptr)
            {
                toReturn = current;
                current = current->getRight();
            }

        if (toReturn != nullptr)
            {
                return toReturn;
            }
        return nullptr;
    }

/**
 * Iter constructor
 * @tparam T
 */
template<typename T>
Iter<T>::Iter()
    {
        nextNode = nullptr;
        reversed = false;
    }

/**
 * Iter constructor
 * @tparam T
 * @param myNode
 * @param isReverse
 */
template<typename T>
Iter<T>::Iter(shared_ptr<Node<T>> myNode, bool isReverse) : nextNode(myNode), reversed(isReverse)
    {
    }

/**
 * find the futur next node
 * @tparam T
 */
template<typename T>
shared_ptr<Node<T>> Iter<T>::nextSuccessor(shared_ptr<Node<T>> myNode)
    {
        shared_ptr<Node<T>> current = myNode;
        if (current == nullptr)
            {
                return nullptr;
            }
        if (current->getRight()) //Right subtree
            {
                return findMin(myNode->getRight());
            }
        else //No right subtree
            {
                shared_ptr<Node<T>> successor = nullptr;
                shared_ptr<Node<T>> ancestor = myNode->getFather();

                if (ancestor == nullptr)
                    {
                        return nullptr;
                    }
                while (myNode->getFather())
                    {
                        if (myNode->getFather()->getData() > myNode->getData())
                            {
                                successor = myNode->getFather();
                                break;
                            }

                        myNode = myNode->getFather();
                    }
                return successor;
            }
    }

template<typename T>
shared_ptr<Node<T>> Iter<T>::nextPredecessor(shared_ptr<Node<T>> myNode)
    {
        shared_ptr<Node<T>> current = myNode;
        if (current == nullptr)
            {
                return nullptr;
            }
        if (current->getLeft())
            {
                return findMax(current->getLeft());
            }
        else
            {
                return nullptr;
            }
    }

/**
 * find index of a node
 * @tparam T
 * @param myNode
 * @return
 */
template<typename T>
int Iter<T>::findIndex(shared_ptr<Node<T>> myNode)
    {
        for (int i = 0; i < nodes->size(); i++)
            {
                if (myNode != nullptr)
                    {
                        break;
                    }
                if (myNode->getData() == nodes->at(i)->getData())
                    {
                        return i;
                    }
            }
        return -1;
    }

/**
 * Operator ++
 * @tparam T
 * @return
 */
template<typename T>
Iter<T> &Iter<T>::operator++()
    {

        if (nextNode != nullptr)
            {
                if (!reversed)
                    {
                        shared_ptr<Node<T>> mine = nextSuccessor(nextNode);
                        nextNode = mine;
                    }
                else
                    {
                        nextNode = nextPredecessor(nextNode);
                    }
            }

        return *this;
    }

/**
 * Operator --
 * @tparam T
 * @return
 */
template<typename T>
Iter<T> &Iter<T>::operator--()
    {
        if (nextNode != nullptr)
            {
                if (reversed)
                    {
                        shared_ptr<Node<T>> mine = nextSuccessor(nextNode);
                        nextNode = mine;
                    }
                else
                    {
                        nextNode = nextPredecessor(nextNode);
                    }
            }

        return *this;
    }

/**
 * Operator =
 * @tparam T
 * @param other
 * @return
 */
template<typename T>
Iter<T> &Iter<T>::operator=(const Iter other)
    {
        nextNode = other.nextNode;
        reversed = other.reversed;
        return *this;
    }

/**
 * Operator ==
 * @tparam T
 * @param iter
 * @return
 */
template<typename T>
bool Iter<T>::operator==(const Iter iter) const
    {
        return ((iter.nextNode == nextNode) && (iter.reversed == reversed));
    }

/**
 * Operator !=
 * @tparam T
 * @param iter
 * @return
 */
template<typename T>
bool Iter<T>::operator!=(const Iter<T> iter) const
    {
        return ((iter.nextNode != nextNode) || (iter.reversed != reversed));
    }

/**
 * find a node
 * @tparam T
 * @param myNode
 * @return
 */
template<typename T>
int Iter<T>::findNode(shared_ptr<Node<T>> myNode)
    {
        for (int i = 0; i < nodes->size(); ++i)
            {
                if (nodes->at(i)->getData() == myNode->getData())
                    {
                        return i;
                    }
            }
        return -1;
    }

/**
 * Operator *
 * @tparam T
 * @return
 */
template<typename T>
T Iter<T>::operator*() const
    {
        return nextNode->getData();
    }

/**
 * Operator ++
 * @tparam T
 * @return
 */
template<typename T>
const Iter<T> Iter<T>::operator++(int)
    {
        ++(*this);
        return *this;
    }

/**
 * Operator --
 * @tparam T
 * @return
 */
template<typename T>
const Iter<T> Iter<T>::operator--(int)
    {
        --(*this);
        return *this;
    }

/**
 * Operator ->
 * @tparam T
 * @return
 */
template<typename T>
shared_ptr<T> Iter<T>::operator->()
    {
        return &nextNode->getData();
    }

/**
 *
 * @tparam T
 * @param myNode
 * @return
 */
template<typename T>
shared_ptr<Node<T>> Iter<T>::findMin(shared_ptr<Node<T>> myNode)
    {
        shared_ptr<Node<T>> current = myNode;
        shared_ptr<Node<T>> toReturn = myNode;

        while (current != nullptr)
            {
                toReturn = current;
                current = current->getLeft();
            }

        if (toReturn != nullptr)
            {
                return toReturn;
            }
        return nullptr;
    }

#endif