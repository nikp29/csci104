#ifndef BST_H
#define BST_H

#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template<typename Key, typename Value>
class Node {
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value& value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
 * Explicit constructor for a node.
 */
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
        : item_(key, value), parent_(parent), left_(NULL), right_(NULL) {}

/**
 * Destructor, which does not need to do anything since the pointers inside of a node
 * are only used as references to existing nodes. The nodes pointed to by parent/left/right
 * are freed within the deleteAll() helper method in the BinarySearchTree.
 */
template<typename Key, typename Value>
Node<Key, Value>::~Node() {}

/**
 * A const getter for the item.
 */
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const {
    return item_;
}

/**
 * A non-const getter for the item.
 */
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() {
    return item_;
}

/**
 * A const getter for the key.
 */
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const {
    return item_.first;
}

/**
 * A const getter for the value.
 */
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const {
    return item_.second;
}

/**
 * A non-const getter for the value.
 */
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue() {
    return item_.second;
}

/**
 * An implementation of the virtual function for retreiving the parent.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const {
    return parent_;
}

/**
 * An implementation of the virtual function for retreiving the left child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const {
    return left_;
}

/**
 * An implementation of the virtual function for retreiving the right child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const {
    return right_;
}

/**
 * A setter for setting the parent of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) {
    parent_ = parent;
}

/**
 * A setter for setting the left child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) {
    left_ = left;
}

/**
 * A setter for setting the right child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) {
    right_ = right;
}

/**
 * A setter for the value of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) {
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
 * A templated unbalanced binary search tree.
 */
template<typename Key, typename Value>
class BinarySearchTree {
public:
    BinarySearchTree();                                                    // TODO
    virtual ~BinarySearchTree();                                           // TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair);  // TODO
    virtual void remove(const Key& key);                                   // TODO
    void clear();                                                          // TODO
    bool isBalanced() const;                                               // TODO
    void print() const;
    bool empty() const;

public:
    /**
     * An internal iterator class for traversing the contents of the BST.
     */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key, Value>& operator*() const;
        std::pair<const Key, Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key, Value>* ptr);
        Node<Key, Value>* current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const;               // TODO
    Node<Key, Value>* getSmallestNode() const;                        // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current);  // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot(Node<Key, Value>* r) const;
    virtual void nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2);

    // Add helper functions here
    bool isBalancedTree(Node<Key, Value>* node) const;
    int height(Node<Key, Value>* node) const;

protected:
    Node<Key, Value>* root_;

    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
 * Explicit constructor that initializes an iterator with a given node pointer.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value>* ptr) {
    // TODO
    current_ = ptr;
}

/**
 * A default constructor that initializes the iterator to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL) {
    // TODO
}

/**
 * Provides access to the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const {
    return current_->getItem();
}

/**
 * Provides access to the address of the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const {
    return &(current_->getItem());
}

/**
 * Checks if 'this' iterator's internals have the same value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    // TODO
    // equal if they have the same pointers
    return (this->current_ == rhs.current_);
}

/**
 * Checks if 'this' iterator's internals have a different value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    // TODO
    // not equal if they dont have the same pointers
    return (current_ != rhs.current_);
}

/**
 * Advances the iterator's location using an in-order sequencing
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++() {
    // TODO
    if (current_ == NULL) {
        return *this;
    }
    // base case: has a right child node
    if (current_->getRight() != NULL) {
        current_ = current_->getRight();
        // go down to the right, and then go as left as possible
        while (current_->getLeft() != NULL) {
            current_ = current_->getLeft();
        }
        return *this;
    }
    Node<Key, Value>* parent = current_->getParent();
    // doesnt have a right child, go up to the left until
    // you are able to go up to the left and then return that

    while (parent != NULL && parent->getRight() == current_) {
        current_ = parent;
        parent = parent->getParent();
    }
    if (parent != NULL && parent->getLeft() == current_) {
        current_ = parent;
        return *this;
    }
    // if u end up at the root, then u have reached the max node in the tree
    if (parent == NULL) {
        current_ = NULL;
        return *this;
    }
    return *this;
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
 * Default constructor for a BinarySearchTree, which sets the root to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(NULL) {
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const {
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const {
    printRoot(root_);
    std::cout << "\n";
}

/**
 * Returns an iterator to the "smallest" item in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const {
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
 * Returns an iterator whose value means INVALID
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const {
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& k) const {
    Node<Key, Value>* curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * An insert method to insert into a Binary Search Tree.
 * The tree will not remain balanced when inserting.
 */
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair) {
    // TODO
    // if root is null then set root to a new node
    if (root_ == NULL) {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
    } else {
        Node<Key, Value>* curr = root_;
        Node<Key, Value>* pred;
        // go down through the tree until you find the node with the same key or find a null node
        while (curr != NULL) {
            pred = curr;
            if (keyValuePair.first == curr->getKey()) {
                break;
            } else if (keyValuePair.first < curr->getKey()) {
                curr = curr->getLeft();
            } else {
                curr = curr->getRight();
            }
        }
        // if you find an identical node, update the value
        if (pred == curr) {
            curr->setValue(keyValuePair.second);
        } else if (keyValuePair.first < pred->getKey()) {
            // if hit null, set the corrrect predecessor
            pred->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, pred));
        } else {
            pred->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, pred));
        }
    }
}

/**
 * A remove method to remove a specific key from a Binary Search Tree.
 * The tree may not remain balanced after removal.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key) {
    // TODO
    Node<Key, Value>* to_delete = internalFind(key);
    // if the node we're removing doesn't exist, then don't do anything
    if (to_delete != NULL) {
        if (to_delete->getLeft() == NULL && to_delete->getRight() == NULL) {
            // is a leaf
            if (to_delete == root_) {
                delete root_;
                root_ = NULL;
            } else {
                Node<Key, Value>* parent = to_delete->getParent();
                if (parent->getLeft() == to_delete) {
                    parent->setLeft(NULL);
                } else {
                    parent->setRight(NULL);
                }
                delete to_delete;
            }
        } else if ((to_delete->getLeft() != NULL && to_delete->getRight() != NULL)) {
            // has 2 child nodes
            // find predecessor and swap into correct position, then delete
            // predeccessior cant b null bc to_delete has left child
            Node<Key, Value>* pred = predecessor(to_delete);
            nodeSwap(pred, to_delete);
            // if to_delete now has children, move the children up
            // remove link to to_delete from its parent
            if (to_delete->getLeft() == NULL) {
                Node<Key, Value>* to_delete_p = to_delete->getParent();
                if (to_delete_p->getLeft() == to_delete) {
                    to_delete_p->setLeft(NULL);
                } else {
                    to_delete_p->setRight(NULL);
                }
                delete to_delete;
            } else {
                // if there is a left child
                Node<Key, Value>* to_delete_p = to_delete->getParent();
                Node<Key, Value>* child = to_delete->getLeft();
                if (to_delete_p->getLeft() == to_delete) {
                    to_delete_p->setLeft(child);
                } else {
                    to_delete_p->setRight(child);
                }
                child->setParent(to_delete_p);
                delete to_delete;
            }
        } else {
            // has 1 child node
            // find child, swap, and delete
            Node<Key, Value>* child = (to_delete->getLeft() == NULL) ? to_delete->getRight() : to_delete->getLeft();
            // if to_delete is root, we need to j set child parent to none set it to root and delete to_delete
            if (to_delete == root_) {
                child->setParent(NULL);
                root_ = child;
                delete to_delete;
            } else {
                // if to_delete is not root
                Node<Key, Value>* to_delete_p = to_delete->getParent();
                if (to_delete_p->getLeft() == to_delete) {
                    to_delete_p->setLeft(child);
                } else {
                    to_delete_p->setRight(child);
                }
                child->setParent(to_delete_p);
                delete to_delete;
            }
        }
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) {
    // TODO
    if (current == NULL) {  // should I be accounting for this base case
        return NULL;
    }
    // base case
    if (current->getLeft() != NULL) {
        current = current->getLeft();
        // go down to the left, and then go as right as possible
        while (current->getRight() != NULL) {
            current = current->getRight();
        }
        return current;
    }
    Node<Key, Value>* parent = current->getParent();
    // doesnt have a right child, go up to the left until
    // you are able to go up to the left and then return that

    while (parent != NULL && parent->getLeft() == current) {
        current = parent;
        parent = parent->getParent();
    }
    if (parent != NULL && parent->getRight() == current) {
        current = parent;
        return current;
    }
    // if u end up at the root, then u have reached the max node in the tree
    if (parent == NULL) {
        current = NULL;
        return current;
    }
    return current;
}

/**
 * A method to remove all contents of the tree and
 * reset the values in the tree for use again.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() {
    // TODO
    // while the root_ isn't null reset everything in the tree
    while (root_ != NULL) {
        remove(root_->getKey());
    }
}

/**
 * A helper function to find the smallest node in the tree.
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const {
    // TODO
    // solves for base case
    if (root_ == NULL) {
        return NULL;
    }
    // go down tree, to the left bottom, return smallest
    Node<Key, Value>* curr = root_;
    Node<Key, Value>* pred = NULL;
    while (curr != NULL) {
        pred = curr;
        curr = curr->getLeft();
    }
    return pred;
}

/**
 * Helper function to find a node with given key, k and
 * return a pointer to it or NULL if no item with that key
 * exists
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const {
    // TODO
    // if empty tree return null
    if (root_ == NULL) {
        return NULL;
    }
    // go down the tree till I find da spot
    Node<Key, Value>* curr = root_;
    while (curr != NULL && curr->getKey() != key) {
        if (curr->getKey() > key) {
            curr = curr->getLeft();
        } else {
            curr = curr->getRight();
        }
    }
    return curr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const {
    // TODO
    return isBalancedTree(root_);
}
template<typename Key, typename Value>

int BinarySearchTree<Key, Value>::height(Node<Key, Value>* node) const {
    if (node == NULL)
        return 0;
    return std::max(height(node->getLeft()), height(node->getRight())) + 1;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedTree(Node<Key, Value>* node) const {
    // TODO
    if (node == NULL)
        return 1;
    return (std::abs(height(node->getLeft()) - height((node->getRight()))) <= 1 && isBalancedTree(node->getLeft())
            && isBalancedTree(node->getRight()));
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2) {
    if ((n1 == n2) || (n1 == NULL) || (n2 == NULL)) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if (n1p != NULL && (n1 == n1p->getLeft()))
        n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if (n2p != NULL && (n2 == n2p->getLeft()))
        n2isLeft = true;

    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if ((n1r != NULL && n1r == n2)) {
        n2->setRight(n1);
        n1->setParent(n2);
    } else if (n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    } else if (n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    } else if (n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);
    }

    if (n1p != NULL && n1p != n2) {
        if (n1isLeft)
            n1p->setLeft(n2);
        else
            n1p->setRight(n2);
    }
    if (n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if (n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if (n2p != NULL && n2p != n1) {
        if (n2isLeft)
            n2p->setLeft(n1);
        else
            n2p->setRight(n1);
    }
    if (n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if (n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }

    if (this->root_ == n1) {
        this->root_ = n2;
    } else if (this->root_ == n2) {
        this->root_ = n1;
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
