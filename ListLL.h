/**
 * @file ListLL.h -- Linked-List implementation of List ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
#pragma once
#include <iostream>
#include <stdexcept>
#include "adt/List.h"

/**
 * @class ListLL<T> - template class for linked-list implementation of List ADT.
 *
 * Public interface is the same as the ADT. Implementations are conformant
 * with efficiency guarantees in ADT comments. Additionally:
 * append:    O(1)
 * set, get:  O(n) (except for special case of set/get on first or last element)
 * remove():  O(n)
 * remove(i): O(n)
 * insert(i): O(n)
 */
template <typename T>
class ListLL : public List<T> {
public:
    ListLL();
    // "Big five":
    ~ListLL();
    ListLL(const ListLL<T>& other);
    ListLL& operator=(const ListLL<T>& other);
    ListLL(ListLL<T>&& temp) noexcept;
    ListLL& operator=(ListLL<T>&& temp) noexcept;

    // The following methods implement the List ADT:
    int size() const;
    void set(int i, const T& element);
    const T& get(int i) const;
    int append(const T& element);
    void insert(int i, const T& element);
    void remove();
    void remove(int i);
    void clear();
    std::ostream& print(std::ostream& out) const;
private:
    struct Node {
        T data;
        Node *next;
        Node(T d, Node *n) : data(d), next(n) {}
    };
    int length;  // number of elements currently being used in linked-list
    Node *head;  // first element
    Node *tail;  // last element
};

/*
 * Following are the templated implementations of the methods
 * (this is done in the header file because it is a template class).
 */

template <typename T>
ListLL<T>::ListLL() : length(0), head(nullptr), tail(nullptr) {
}

template <typename T>
ListLL<T>::~ListLL() {
    clear();
}

template <typename T>
ListLL<T>::ListLL(const ListLL<T>& other) : ListLL() {
    *this = other;  // just use the lvalue = operator
}

template <typename T>
ListLL<T>::ListLL(ListLL<T>&& temp) noexcept : ListLL() {
    *this = temp;  // just use the rvalue = operator
}

template <typename T>
ListLL<T>& ListLL<T>::operator=(const ListLL<T>& other) {
    // first check if we are doing something like x = x
    if (this != &other) {
        clear();
        for (Node *theirs = other.head; theirs != nullptr; theirs = theirs->next)
            append(theirs->data);
    }
    return *this;
}

template <typename T>
ListLL<T>& ListLL<T>::operator=(ListLL<T>&& temp) noexcept {
    std::swap(length, temp.length);
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
    return *this;
}

template <typename T>
int ListLL<T>::size() const {
    return length;
}

template <typename T>
void ListLL<T>::set(int i, const T& element) {
    if (i < 0 || i >= length)
        throw std::out_of_range("set past bounds");
    if (i == length-1) {
        // special case we can go right to end
        tail->data = element;
    } else {
        Node *p = head;
        for (int j = 0; j < i; j++)
            p = p->next;
        p->data = element;
    }
}

template <typename T>
const T& ListLL<T>::get(int i) const {
    if (i < 0 || i >= length)
        throw std::out_of_range("get past bounds");
    if (i == length-1) {
        // special case we can go right to end
        return tail->data;
    } else {
        Node *p = head;
        for (int j = 0; j < i; j++)
            p = p->next;
        return p->data;
    }
}

template <typename T>
int ListLL<T>::append(const T& element) {
    Node *p = new Node(element, nullptr);
    if (length > 0)
        tail->next = p;
    else
        head = p;
    tail = p;
    length++;
    return length-1;
}

template <typename T>
void ListLL<T>::insert(int i, const T& element) {
    if (i > length || i < 0)
        throw std::out_of_range("insert past bounds");
    if (i == length) {
        append(element);
        return;
    } else {
        // we know if we're here that length > 0, so no need to think about tail
        length++;
        if (i == 0) {
            head = new Node(element, head);
        } else {
            Node *p = head;
            for (int j = 1; j < i; j++)
                p = p->next;
            p->next = new Node(element, p->next);
        }
    }
}

template <typename T>
void ListLL<T>::remove() {
    // we would need a doubly-linked list to make the O(1)
    remove(length-1);
}

template <typename T>
void ListLL<T>::remove(int i) {
    if (i >= length || i < 0)
        throw std::out_of_range("remove past bounds");
    Node *deleteMe;
    if (i == 0) {
        deleteMe = head;
        head = head->next;
    } else {
        Node *p = head;
        for (int j = 1; j < i; j++)
            p = p->next;
        deleteMe = p->next;
        p->next = deleteMe->next;
    }
    delete deleteMe;
    length--;
}

template <typename T>
void ListLL<T>::clear() {
    while (length > 0)
        remove(0);
}

template <typename T>
std::ostream& ListLL<T>::print(std::ostream& out) const {
    std::string delim = "";
    for (Node *p = head; p != nullptr; p = p->next) {
        out << delim << p->data;
        delim = ", ";
    }
    return out;
}
