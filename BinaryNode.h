/**
 * @file BinaryNode.h - Implementation of Binary Tree ADT.
 * @author Nassuel Valera
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include <iostream>
#pragma once

/**
 * @class BinaryNode - Implementation of Binary Tree ADT as
 *					   as a struct making all of its members
 *					   public by default.
 * @tparam T data element type
 */
template <typename T>
struct BinaryNode {
	T data;
    BinaryNode *left;
    BinaryNode *right;
	
	// Class required methods
    BinaryNode() 												: data(), left(nullptr), right(nullptr)	{}
    explicit BinaryNode(const T& d)							: data(d), left(nullptr), right(nullptr)	{}
    BinaryNode(BinaryNode *l, BinaryNode *r)					: data(), left(l), right(r)					{}
    BinaryNode(BinaryNode *l, BinaryNode *r, const T& d)		: data(d), left(l), right(r)				{}
	
	// Class ctors
	~BinaryNode() = default; 
	BinaryNode(const BinaryNode& other) = default;
	BinaryNode(BinaryNode&& temp) = default;
	BinaryNode& operator=(const BinaryNode& other) = default;
	BinaryNode& operator=(BinaryNode&& temp) = default;
	
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
	 *	Recursively prints out the "root" node and the ones below it.
	 *	In a in-order traversal fashion.
	 *	
	 *	@param node				"root" node
	 *	@param out				stream to print to
	 *	@return 				modified output stream
	 * 	@pre        			out is writable
     * 	@post       			out has a textual representation of the data of the
	 *							the node as well as an assigned prefix, differentiating
	 *							if it is a right or left node. 0: right | 1: left (with <<)
	 */
    static void printR(std::ostream& out, std::string prefix, const BinaryNode* node) {
		// If node equals nullptr, there is nothing to print
		if (node == nullptr)
			return;
		printR(out, " " + prefix + "0", node->left);	// Print left side
			out << prefix << ": " << node->data << std::endl;
		printR(out, " " + prefix + "1", node->right);	// Print right side
	}
	
	/**
	 *	Overload function for ostream and a BinaryNode* which calls printR()
	 */
	friend std::ostream&operator<<(std::ostream& out, const BinaryNode *node) {
		printR(out , "", node);
		return out;
	}
};