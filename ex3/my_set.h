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

#ifndef EX3_MY_SET_H
#define EX3_MY_SET_H



// ------------------------------ includes --------------------------

#include <iostream>
#include <vector>
#include <memory>


using namespace std;

template <typename T> class my_set;
template <typename T> class Node;
template <typename T> class Iter;

template <typename T>

/**
 * Inner class representing a Node
 */
class Node
{
public:
    /**
     * Constructor
     * @param dt - data of the Node
     */
    explicit Node(T dt);

    /**
     * Destructor
     */
    ~Node() = default;

    /**
     * Get the data of the node
     * @return _data
     */
    T getData();

    /**
     * Get the parent of the node
     * @return _parent
     */
    shared_ptr<Node<T>> getFather();

    /**
     * Get the right son
     * @return _right
     */
    shared_ptr<Node<T>> getRight();

    /**
     * Get the left son
     * @return _left
     */
    shared_ptr<Node<T>> getLeft();

    /**
     * Set the father
     * @param node - the new father
     */
    void setFather(shared_ptr<Node<T>> node);

    /**
     * Set the left son
     * @param node - the new left son
     */
    void setLeft(shared_ptr<Node<T>> node);

    /**
     * Set the right son
     * @param node - the new right son
     */
    void setRight(shared_ptr<Node<T>> node);

    /**
     * Set the data
     * @param data - the new data
     */
    void setData(T data);

private:
    /** data member */
    T _data;

    /** Father member */
    shared_ptr<Node<T>> _father;

    /** Right son member */
    shared_ptr<Node<T>> _right;

    /** Left son member */
    shared_ptr<Node<T>> _left;

};

template <typename T>
/**
* Inner class representing an iterator
*/
class Iter
{

public:

    friend class Node<T>;
    friend class my_set<T>;

    /**
     * Constructor by default
     */
    Iter();

    /**
     * Constructor receiving a node and a flag to know if its a reverse iterator
     * @param myNode - node
     * @param isReverse - true iff the iterator is reversed
     */
    explicit Iter(shared_ptr<Node<T>> myNode, bool isReverse);

    /**
     * Destructor
     */
    ~Iter() = default;

    /**
     *
     */
    shared_ptr<Node<T>> nextSuccessor(shared_ptr<Node<T>> ptr);
    
    shared_ptr<Node<T>> nextPredecessor(shared_ptr<Node<T>> ptr);

    /**
     * find the index of the node
     * @param myNode
     * @return
     */
    int findIndex(shared_ptr<Node<T>> myNode);

    /**
     * Operator =
     * @param other
     * @return
     */
    Iter& operator = (const Iter other);

    /**
     * Operator *
     * @return
     */
    T operator*() const;

    /**
     * Operator ->
     * @return
     */
    shared_ptr<T> operator->();

    /**
     * Operator ++
     * @return
     */
    Iter& operator ++ ();

    /**
     * Operator ++
     * @return
     */
    const Iter operator ++ (int);

    /**
     * Operator --
     * @return
     */
    Iter& operator -- ();

    /**
     * Operator --
     * @return
     */
    const Iter operator -- (int);

    /**
     * Operator ==
     * @param iter
     * @return
     */
    bool operator == (const Iter iter) const;

    /**
     * Operator !=
     * @param iter
     * @return
     */
    bool operator != (const Iter iter) const;

    /**
     * find a node
     * @param myNode
     * @return
     */
    int findNode(shared_ptr<Node<T>> myNode);

    /**
     * find the max node
     * @param myNode
     * @return
     */
    shared_ptr<Node<T>> findMax(shared_ptr<Node<T>> myNode);

    /**
     * find the min
     * @param myNode
     * @return
     */
    shared_ptr<Node<T>> findMin(shared_ptr<Node<T>> myNode);

    /**
     * the next node
     */
    shared_ptr<Node<T>> nextNode;

private:
    /**
     * nodes
     */
    vector<shared_ptr<Node<T>>> * nodes;

    /**
     * The deleted ones
     */
    vector<shared_ptr<Node<T>>> * deleted;

    /**
     * true iff the iterator is reversed
     */
    bool reversed;
};


template <typename T>
/**
 * Class my_set that represents a set
 * @tparam T - typename T
 */
class my_set
{
public:

    /**
     * friend class
     */
    friend class Iter<T>;

    /**
     * typedef
     */
    typedef Iter<T> iterator;
    typedef const Iter<T> const_iterator;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;

    /**
     * Default constructor
     */
    my_set();

    /**
     * Constructor with iterator
     * @tparam InputIterator
     * @param beg
     * @param end
     */
    template <class InputIterator> my_set(InputIterator beg, InputIterator end);

    /**
     * destructor
     */
    ~my_set();

    /**
     * Copy constructor
     * @param other
     */
    my_set(const my_set& other);

    /**
     * Moove constructor
     * @param other
     */
    my_set(my_set && other) noexcept;

    /**
     * Operator =
     * @param other
     * @return
     */
    my_set& operator =(const my_set & other);

    /**
     * Moove operator =
     * @param other
     * @return
     */
    my_set& operator =(my_set && other) noexcept;

    /**
     * begining of iterator
     * @return
     */
//    const_iterator cbegin();

    /**
     * begining of const iterator
     * @return
     */
    const_iterator cbegin() const;

    /**
     * end of iterator
     * @return
     */
//    iterator cend();

    /**
     * end of const iterator
     * @return
     */
    const_iterator cend() const noexcept;

    /**
     * begin of reverse iterator
     * @return
     */
//    const_iterator crbegin();

    /**
     * beg of reverse const iterator
     * @return
     */
    const_iterator crbegin() const;

    /**
     * end of reverse iterator
     * @return
     */
//    iterator crend();

    /**
     * end of reverse const iterator
     * @return
     */

    const_iterator crend() const;

    /**
     * insert function
     * @param value
     * @return
     */
    pair<my_set<T>::const_iterator, bool> insert(const value_type& value);

    /**
     * insert function
     * @param value
     * @return
     */
    pair<my_set<T>::const_iterator, bool> insert(const value_type&& value);

    /**
     * insert function
     * @param pos
     * @param value
     * @return
     */
    iterator insert(const_iterator pos, const value_type& value);

    /**
     * insert function
     * @param pos
     * @param value
     * @return
     */
    const_iterator insert(const_iterator pos, const value_type&& value);

    /**
     * insert function
     * @param beg
     * @param end
     */
    void insert(iterator beg, iterator end);

    /**
     * helper insert function
     * @param myNode
     * @param value
     * @return
     */
    pair<shared_ptr<Node<T>>, bool> helperInsert(shared_ptr<Node<T>> myNode, const value_type& value);

    /**
     * find function
     * @param value
     * @return
     */
    const_iterator find(const value_type& value) const;

    /**
     * find function
     * @param value
     * @return
     */
    iterator find(const value_type& value);

    /**
     * find helper function
     * @param value
     * @return
     */
    shared_ptr<Node<T>> findIt(const value_type& value) const;

    shared_ptr<Node<T>>& findToErase(shared_ptr<Node<T>>& currentNode, const value_type& value);

    /**
     * function that finds the successor of a node
     * @param myNode
     * @return
     */
    shared_ptr<Node<T>> successorFind(shared_ptr<Node<T>> myNode);

    /**
     * function that erases a node
     * @param position
     * @return
     */
    iterator erase(const_iterator position);

    /**
     * erase function
     * @param value
     * @return
     */
    int erase(const value_type& value);

    /**
     * erase function
     * @param one
     * @param last
     * @return
     */
    iterator erase(iterator one, iterator last);

    /**
     * function that helps erase
     * @param value
     * @return
     */
    pair<shared_ptr<Node<T>>, bool> helperErase(const value_type& value);


    /**
     * check if empty
     * @return
     */
    bool empty() const;

    /**
     * size of the tree
     * @return
     */
    size_t size() const;

    /**
     * no more nodes
     */
    void clear() noexcept;

    /**
     * swap two set
     * @tparam T1
     * @param one
     * @param two
     */
    template <typename T1> friend void swap(my_set<T>& one, my_set<T>& two);

    /**
     * swap two sets
     */
    void swap(my_set<T>&);

    /** root of the tree */
    shared_ptr<Node<T>> _root;

    /**
     * find the max
     * @return
     */
    shared_ptr<Node<T>> doMax() const;

    /**
     * find the min
     * @return
     */
    shared_ptr<Node<T>> doMin() const;

private:



    /** size of thetree */
    int _size;
};

#include "my_set.hpp"
#endif //EX3_MY_SET_H
