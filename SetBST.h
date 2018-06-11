/**
 * @file SetBST.h - BST implementation of Set ADT
 * @author Nassuel Valera Cuevas
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include "adt/Set.h"
#include <set>

/**
 * @class SetBST - BST implementation of the Set ADT
 *
 * An element is either in the set or not, solely as determined
 * by the equality operator (operator==). There is no
 * concept in this class of multiple equivalent elements.
 *
 * This implementation of the Set ADT also supports
 * a const_iterator and methods begin(), begin(start) and end(). Order of
 * iteration is in KeyType order (per its < operator). Additionally,
 * there is a begin(key) that starts the iteration at the given
 * key.
 *
 * Time-efficiency of methods is directly resulting from using the STL
 * set template class which uses a balanced BST:
 * has(key)         O(log n)
 * add(key,value)   O(log n)
 * remove(key)      O(log n)
 * begin()          O(log n)
 * begin(key)       O(log n)
 * end()            O(1)
 *
 * @tparam KeyType     type of elements (keys) of the set
 *                     must support equality operator and < operator
 */
template <typename KeyType>
class SetBST : public Set<KeyType> {
public:

	SetBST() : root(nullptr) {}
    ~SetBST() {
		Node::freeNodes(root);
	}
    SetBST(const SetBST<KeyType>& other) : SetBST<KeyType> {
		*this = other;
	}
    SetBST(SetBST<KeyType>&& temp) = default;
    SetBST<KeyType>& operator=(const SetBST<KeyType>& other) = default;
    SetBST<KeyType>& operator=(SetBST<KeyType>&& temp) = default;

    bool has(const KeyType& key) const {
        Node *temp = root;
		while (temp != nullptr) {
			if (key == temp->key)
				return true;
			if (key < temp->key)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return false;
    }

    void add(const KeyType& key) {
        Node *temp = root;
		if (temp == nullptr)
			root = new Node(key);
		else
			while (!(temp->key == key))
				if (key < temp->key) {
					if (temp->left == nullptr)
						temp->left = new Node(key);
					temp = temp->left;
				} else {
					if (temp->right == nullptr)
						temp->right = new Node(key);
					temp = temp->right;
				}
    }

    void remove(const KeyType& key) {
        Node *toRemove;		// the node to remove
		Node **pToRemove;	// the place that points to toRemove

		pToRemove = &this->root;
		while ( *pToRemove != nullptr && key != (*pToRemove)->key) {
			if (key < (*pToRemove)->key)
				pToRemove = &(*pToRemove)->left;
			else
				pToRemove = &(*pToRemove)->right;
		toRemove = *pToRemove;

		// it is already deleted?
		if (toRemove == nullptr)
			return;
		}
		
		// If toRemove is not a leaf go left and replace with max key
		if (!toRemove->isLeaf()) {
			KeyType replacement;
			if (toRemove->left != nullptr) {
				toRemove = toRemove->left;
				while (toRemove->right != nullptr)
					toRemove = toRemove->right;
			} else {
				// else go right and replace the min key
				toRemove = toRemove->right;
				while (toRemove->left != nullptr)
					toRemove = toRemove->left;
			}
			replacement = toRemove->key;
			
			remove(replacement);
			toRemove->key = replacement;
		} else {
			delete toRemove;
			*pToRemove = nullptr;
		}
    }

    /**
     * @class const_iterator - used for begin(), begin(start) 
	 * and end() C++11 expectations for const iterators. 
	 * Can be used in range-based for loops, for example.
     * Operations supported are *, !=, and ++(prefix).
     */
    class const_iterator {
    public:
        const_iterator(SetBST<KeyType>::Node it) : current(it) {}
		
        const KeyType& operator*() const {
            return current->key;
        }
        const const_iterator& operator++() {
            // Figure out algorithm for this
			if (current->right != nullptr)
				parent = current;
				current = current->right;
			
            return *this;
        }
        bool operator!=(const const_iterator& rhs) const {
            return current != rhs.current;
        }
    private:
        typename SetBST<KeyType>::Node *current, *parent;
        friend class SetBST<KeyType>;
    };

    /**
     * Beginning iterator starts iteration in KeyType order through the elements.
     * @return beginning iterator (leftmost tree)
     */
    const_iterator begin() const {
		Node *temp = root;
		while (temp->left != nullptr)
			temp = temp->left;
        return const_iterator(temp);
    }

    /**
     * Beginning iterator starts iteration in alphabetical order
     * @param start
     * @return location of the node with the "start" KeyType
     */
    const_iterator begin(const KeyType& start) const {
		Node *temp = root;
		while (temp->key != start) {
			if (temp->key < start)
				temp = temp->left;
			 else if (temp->key > start) 
				temp = temp->right;
		}
        return const_iterator(temp);
    }

    /**
     * Ending iterator used in standard fashion to see when an iterator has finished
     * traversing this set.
     *
     * @return ending iterator (nullptr)
     */
    const_iterator end() const {
        return const_iterator(nullptr);
    }

private:
	struct Node {
		KeyType key;
		Node *left, *right;
		
		Node()								:	key(), left(nullptr), right(nullptr) {}
		explicit Node(const KeyType& key)	:	key(key), left(nullptr), right(nullptr) {}
		
		// class ctors
		~Node() = default; 
		Node(const Node& other) = default;
	    Node(Node&& temp) = default;
		Node& operator=(const Node& other) = default;
		Node& operator=(Node&& temp) = default;
		
		/**
		 *	Recursively deletes each node.
		 *	It is static as a node pointer in passed in.
		 *	
		 *	@param 	node			node to delete
		 */
	static void freeNodes(BinaryNode* &node) {
		// If node equals nullptr, there is nothing to free
		if (node == nullptr)
			return;
		freeNodes(node->left);
		freeNodes(node->right);
		delete node;
		node = nullptr;
	}
		
		/**	
		 *	@return	bool			says if the node is a leaf (no children)
		 */
		bool isLeaf() const 	{ return (left == nullptr || right == nullptr);	}
		/**	
		 *	@return	bool			says if the node has a left child
		 */
		bool hasLeft() const 	{ return left != nullptr;							}
		 /**	
		 *	@return	bool			says if the node has a right child
		 */
		bool hasRight() const 	{ return right != nullptr; 						}
	};
	
	Node *root;
};