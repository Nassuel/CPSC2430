/**
 * @file DictBST.h - AVL implementation of Dictionary ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include "adt/Dictionary.h"
#include <stdexcept>
#include <algorithm>

/**
 * @class DictBST - AVL implementation of Dictionary ADT
 *
 * A dictionary is a set whose elements has an associated payload.
 * An element is either in the dictionary or not, solely as determined
 * by the equality operator (operator==). There is no
 * concept in this class of multiple equivalent elements.
 *
 * This implementation of the Dictionary ADT also supports
 * a const_iterator and methods begin() and end(). Order of
 * iteration is in KeyType order (per its < operator). Additionally,
 * there is a begin(key) that starts the iteration at the given
 * key.
 *
 * Time-efficiency of methods is from using a balanced BST:
 * has(key)         O(log n)
 * get(key)         O(log n)
 * get(key) const   O(log n)
 * add(key,value)   O(log n)
 * remove(key)      O(log n)
 * begin()          O(1)
 * begin(key)       O(log n)
 * end()            O(1)
 *
 * @tparam KeyType     type of elements (keys) of the dictionary
 *                     must support equality operator and < operator
 * @tparam ValueType   type of associated data for each key in the dictionary
 *                     must support zero-argument construction
 */
template <typename KeyType, typename ValueType>
class DictBST : public Dictionary<KeyType, ValueType> {
    struct Node {
        KeyType key;
        ValueType value;
        Node *left, *right, *parent;
        int height;

        Node() : key(), value(), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
        Node(const KeyType& key, const ValueType& value, Node *parent) : key(key), value(value), left(nullptr),
                                                                         right(nullptr), parent(parent), height(0) {}

        /**
         * Checks if this is a leaf node.
         *
         * @return  true if a leaf (no left and no right)
         */
        bool isLeaf() const {
            return left == nullptr && right == nullptr;
        }

        /**
         * Manually, recursively, check that node is balanced (0 or 1 difference in subtree height).
         *
         * Also checks that heights are correct.
         * Meant as a debugging tool.
         * @return  true if subtree is balanced and heights are all correct
         */
        bool isBalanced() const {
            if (isLeaf() && height == 0)
                return true;
            if (left != nullptr && !left->isBalanced())
                return false;
            if (right != nullptr && !right->isBalanced())
                return false;
            if (height != std::max(getHeight(left), getHeight(right)) + 1)
                return false;
            return true;
        }

        /**
         * Find the minimum node.
         *
         * @return  left-most node in this subtree
         */
        Node *findMin() {
            if (left == nullptr)
                return this;
            else
                return left->findMin();
        }

        /**
         * Find the maximum node.
         *
         * @return  right-most node in this subtree
         */
        Node *findMax() {
            if (right == nullptr)
                return this;
            else
                return right->findMax();
        }

        /**
         * Find a node in this subtree whose key is equal to the given key.
         *
         * @param node  root of this subtree
         * @param key   search target
         * @return      node with node->key == key, nullptr if not found
         */
        static Node *find(Node *node, const KeyType& key) {
            if (node == nullptr || node->key == key)
                return node;
            if (key < node->key)
                return find(node->left, key);
            else
                return find(node->right, key);
        }

        /**
         * Delete the memory for this subtree.
         *
         * @param node   root of this subtree
         */
        static void freeNodes(Node *&node) {
            if (node == nullptr)
                return;
            freeNodes(node->left);
            freeNodes(node->right);
            delete node;
            node = nullptr;
        }

        /**
         * Internal method to insert into a subtree.
         *
         * If key already is in this subtree, replace its value with given one.
         * @param node    root of this subtree (where we want to insert (key,value))
         * @param parent  node's parent (for back pointer)
         * @param key     key to insert
         * @param value   value to associate with key
         */
        static void insert(Node *&node, Node* parent, const KeyType& key, const ValueType& value) {
            if (node == nullptr)
                node = new Node(key, value, parent);
            else if (key < node->key)
                insert(node->left, node, key, value);
            else if (node->key < key)
                insert(node->right, node, key, value);
            else
                node->value = value;
            balance(node);
        }

        /**
         * Internal method to remove from a subtree.
         *
         * If the key is not in the subtree, do nothing.
         * @param node  root of this subtree (where we want to erase key and its associated value)
         * @param key   key to erase
         */
        static void erase(Node *&node, const KeyType& key) {
            if (node == nullptr)
                return;  // not found; do nothing
            if (key < node->key) {
                erase(node->left, key);
            } else if (node->key < key) {
                erase(node->right, key);
            } else if (node->left != nullptr && node->right != nullptr) {
                // has both children, so get min of right subtree to replace this one
                Node *replacement = node->right->findMin();
                node->key = replacement->key; // copy it here
                node->value = replacement->value;
                erase(node->right, node->key);     // and remove it there
            } else {
                // at least one child is not there, so just throw this one away and link it to below
                Node *deleteMe = node;
                Node *parent = node->parent;
                node = (node->right == nullptr) ? node->left : node->right;
                if (node != nullptr)
                    node->parent = parent;
                delete deleteMe;
            }
            balance(node);
        }

        /**
         * Rebalance this subtree if necessary and set its height.
         *
         * @param node  to balance
         */
        static void balance(Node *&node) {
            if (node == nullptr)
                return;
            Node *parent = node->parent;
            int lh = getHeight(node->left);
            int rh = getHeight(node->right);
            if (lh-rh > 1) {
                lh = getHeight(node->left->left);
                rh = getHeight(node->left->right);
                if (lh >= rh)
                    rotateWithLeftChild(node);
                else
                    doubleWithLeftChild(node);
            } else if (rh-lh > 1) {
                lh = getHeight(node->right->left);
                rh = getHeight(node->right->right);
                if (rh >= lh)
                    rotateWithRightChild(node);
                else
                    doubleWithRightChild(node);
            }
            node->parent = parent; // new node may have been rotated in
            node->setHeight();
        }

        /**
         * Rebalancing case 1: rotate right
         *
         * @param k2  current root that will rotate out replaced by k1 to the left
         * @see "Weiss, Data Structures and Algorithm Analysis in C++, 4th ed., Figure 4.34"
         */
        static void rotateWithLeftChild(Node *&k2) {
            Node *k1 = k2->left;

            k2->left = k1->right;
            if (k2->left != nullptr)
                k2->left->parent = k2;

            k1->right = k2;
            if (k1->right != nullptr)
                k1->right->parent = k1;

            k2->setHeight();
            k1->setHeight();
            k2 = k1;
        }

        /**
         * Rebalancing case 4: rotate left
         *
         * @param k2  current root that will rotate out replaced by k1 to the right
         * @see "Weiss, Data Structures and Algorithm Analysis in C++, 4th ed., Figure 4.36"
         */
        static void rotateWithRightChild(Node *&k2) {
            Node *k1 = k2->right;

            k2->right = k1->left;
            if (k2->right != nullptr)
                k2->right->parent = k2;

            k1->left = k2;
            if (k1->left != nullptr)
                k1->left->parent = k1;

            k2->setHeight();
            k1->setHeight();
            k2 = k1;
        }

        /**
         * Rebalancing case 2: rotate left below, then right above
         * 1) First left child with its right child
         * 2) Then node k3 with new left child.
         *
         * @param k3  current root that will rotate out replaced by k2 (currently k3->left->right)
         * @see "Weiss, Data Structures and Algorithm Analysis in C++, 4th ed., Figure 4.45"
         */
        static void doubleWithLeftChild(Node *&k3) {
            rotateWithRightChild(k3->left);
            if (k3->left != nullptr)
                k3->left->parent = k3;
            rotateWithLeftChild(k3);
        }

        /**
         * Rebalancing case 3: rotate right below, then left above
         * 1) First right child with its left child
         * 2) Then node k3 with new right child.
         *
         * @param k3  current root that will rotate out replaced by k2 (currently k3->right->left)
         * @see "Weiss, Data Structures and Algorithm Analysis in C++, 4th ed., Figure 4.39"
         */
        static void doubleWithRightChild(Node *&k3) {
            rotateWithLeftChild(k3->right);
            if (k3->right != nullptr)
                k3->right->parent = k3;
            rotateWithRightChild(k3);
        }

        /**
         * Helper method to get height of a subtree (including nullptr)
         *
         * @param node   root of this subtree
         * @return       height (-1 for node==nullptr)
         */
        static int getHeight(Node *node) {
            return node == nullptr ? -1 : node->height;
        }

        /**
         * Set this node to its correct height
         */
        void setHeight() {
            height = std::max(getHeight(left), getHeight(right)) + 1;
        }

        /**
         * Copy this tree.
         *
         * Retains the same structure but with all new nodes and copies of the keys
         * and with the correct parent pointers for the new tree.
         * @return a copy of this tree (parent set to nullptr)
         */
        Node *copy() const {
            Node *nodecopy = new Node(key, value, nullptr);
            if (left != nullptr) {
                nodecopy->left = left->copy();
                nodecopy->left->parent = nodecopy;
            }
            if (right != nullptr) {
                nodecopy->right = right->copy();
                nodecopy->right->parent = nodecopy;
            }
            return nodecopy;
        }
    };
    Node *root;
public:
    typedef DictBST<KeyType,ValueType> DictType;
    DictBST() : root(nullptr) {}
    ~DictBST() {
        Node::freeNodes(root);
    }
    DictBST(const DictType& other) : DictType() {
        *this = other;
    }
    DictBST(DictType&& temp) : DictType() {
        *this = temp;
    }
    DictType& operator=(const DictType& other) {
        if (this != &other) {
            Node::freeNodes(root);
            root = other.root->copy();
        }
        return *this;
    }
    DictType& operator=(DictType&& temp) {
        std::swap(root, temp.root);
        return *this;
    }

    bool has(const KeyType& key) const {
        return Node::find(root, key) != nullptr;
    }

    ValueType& get(const KeyType& key) {
        Node *p = Node::find(root, key);
        if (p == nullptr) {
            // key not here, so add it with an empty ValueType
            add(key, ValueType());
            p = Node::find(root, key);
        }
        return p->value;
    }

    const ValueType& get(const KeyType& key) const {
        Node *p = Node::find(root, key);
        if (p == nullptr)
            throw std::invalid_argument("key not present in dictionary");
        return p->value;
    }

    void add(const KeyType& key, const ValueType& value) {
        Node::insert(root, nullptr, key, value);
    }

    void remove(const KeyType& key) {
        Node::erase(root, key);
    }

    /**
     * Debugging tool to verify that tree is balanced and valid.
     *
     * @return  if all balanced and happy
     */
    bool isBalanced() const {
        if (root == nullptr)
            return true;
        return root->isBalanced();
    }

    /**
     * @class const_iterator - used for begin() and end()
     * C++11 expectations for const iterators. Can be used
     * in range-based for loops, for example.
     * Operations supported are *, !=, and ++(prefix).
     */
    class const_iterator {
    public:
        const_iterator(DictBST<KeyType,ValueType>::Node *current) : current(current) {}

        const KeyType& operator*() const {
            if (current == nullptr)
                throw std::invalid_argument("dereference of end()");
            return current->key;
        }

        const const_iterator& operator++() {
            if (current == nullptr)
                return *this; // no further increment past end()
            if (current->right != nullptr) {
                current = current->right->findMin();
            } else {
                while (current->parent != nullptr && current->parent->right == current)
                    current = current->parent;
                current = current->parent;
            }
            return *this;
        }

        bool operator!=(const const_iterator& rhs) const {
            return current != rhs.current;
        }

    private:
        DictBST<KeyType,ValueType>::Node *current;
        friend class DictBST<KeyType,ValueType>;
    };

    /**
     * Beginning iterator starts iteration in KeyType order through the elements.
     *
     * @return  beginning iterator
     */
    const_iterator begin() const {
        return const_iterator(root == nullptr ? nullptr : root->findMin());
    }

    /**
     * Beginning iterator starts iteration in KeyType order with a given start location.
     *
     * @param start  key where to start iteration
     * @return       iterator referencing start, or end() if not found
     */
    const_iterator begin(const KeyType& start) const {
        return const_iterator(Node::find(root, start));
    }

    /**
     * Ending iterator used in standard fashion to see when an iterator has finished
     * traversing this set.
     *
     * @return ending iterator
     */
    const_iterator end() const {
        return const_iterator(nullptr);
    }
};
