#ifndef RBBST_H
#define RBBST_H

#include "bst.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError {};

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
        : Node<Key, Value>(key, value, parent), height_(1) {}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode() {}

/**
 * A getter for the height of a AVLNode.
 */
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const {
    return height_;
}

/**
 * A setter for the height of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height) {
    height_ = height;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
    virtual void insert(const std::pair<const Key, Value>& new_item);  // TODO
    virtual void remove(const Key& key);                               // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here
    virtual void balance(AVLNode<Key, Value>* g);
    virtual void rightRotate(AVLNode<Key, Value>* n);
    virtual void leftRotate(AVLNode<Key, Value>* n);
    virtual void insertFix(AVLNode<Key, Value>* n);
    virtual void removeFix(AVLNode<Key, Value>* n);
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item) {
    // TODO
    AVLNode<Key, Value>* pred;
    if (BinarySearchTree<Key, Value>::root_ == NULL) {
        BinarySearchTree<Key, Value>::root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        return;
    } else {
        AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);
        // go down through the tree until you find the node with the same key or find a null node
        while (curr != NULL) {
            pred = curr;
            if (new_item.first == curr->getKey()) {
                break;
            } else if (new_item.first < curr->getKey()) {
                curr = curr->getLeft();
            } else {
                curr = curr->getRight();
            }
        }
        // if you find an identical node, update the value
        if (pred == curr) {
            curr->setValue(new_item.second);
            // in this case we dont need to balance, so break
            return;
        } else if (new_item.first < pred->getKey()) {
            // if hit null, set the corrrect predecessor
            pred->setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, pred));
        } else {
            pred->setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, pred));
        }
    }
    if (pred->getHeight() == 2) {
        return;
    }
    insertFix(pred);
}

template<class Key, class Value>
void AVLTree<Key, Value>::balance(AVLNode<Key, Value>* g) {

    // get parent node (the largest child of g)
    AVLNode<Key, Value>* p;
    int l_h = (g->getLeft() == NULL) ? 0 : g->getLeft()->getHeight();
    int r_h = (g->getRight() == NULL) ? 0 : g->getRight()->getHeight();
    p = (l_h > r_h) ? g->getLeft() : g->getRight();
    bool p_left = (l_h > r_h);  // is p left child of g // something wrong over here cuz its going left right
    // calculate the child heights of p
    l_h = (p->getLeft() == NULL) ? 0 : p->getLeft()->getHeight();
    r_h = (p->getRight() == NULL) ? 0 : p->getRight()->getHeight();
    bool n_left = (l_h > r_h);  // is n left child of p
    if (p_left && n_left) {
        // left left
        rightRotate(g);
    } else if (p_left && !n_left) {
        // left right
        leftRotate(p);
        rightRotate(g);
    } else if (!p_left && !n_left) {
        // right right
        leftRotate(g);
    } else {
        // right left
        rightRotate(p);  // the new p's parent isn't g the new p is the current p's left child
        leftRotate(g);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* n) {
    // update height for n and all parents of n
    // update everything's heights
    int l_h = (n->getLeft() == NULL) ? 0 : n->getLeft()->getHeight();
    int r_h = (n->getRight() == NULL) ? 0 : n->getRight()->getHeight();
    int calc_height = std::max(l_h, r_h) + 1;
    if (n->getHeight() == calc_height) {  // might not work, if so delete
        return;
    }
    n->setHeight(calc_height);

    if (abs(l_h - r_h) <= 1) {
        if (n->getParent() != NULL)
            insertFix(n->getParent());
        return;
    }
    balance(n);
    // insertFix(n->getParent());
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n) {
    // update height for n and all parents of n
    // update everything's heights
    int l_h = (n->getLeft() == NULL) ? 0 : n->getLeft()->getHeight();
    int r_h = (n->getRight() == NULL) ? 0 : n->getRight()->getHeight();
    int calc_height = std::max(l_h, r_h) + 1;
    if (n->getHeight() == calc_height) {  // might not work, if so delete
        return;
    }
    n->setHeight(calc_height);

    if (abs(l_h - r_h) <= 1) {
        if (n->getParent() != NULL)
            removeFix(n->getParent());
        return;
    }
    balance(n);
    removeFix(n->getParent());
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* x) {
    AVLNode<Key, Value>* y = x->getRight();
    AVLNode<Key, Value>* b = y->getLeft();
    // first fix b
    if (b) {
        // if b exists b will become x's right child, else x' right child is nothing
        x->setRight(b);
        b->setParent(x);
    } else {
        x->setRight(NULL);
    }
    // check if x has a parent, if so we need to set it to be y's parent
    if (x->getParent()) {
        AVLNode<Key, Value>* p = x->getParent();
        if (p->getLeft() == x) {
            p->setLeft(y);
        } else {
            p->setRight(y);
        }
        y->setParent(p);
        // now that y is in the correct place below the parent we need to sort out x
        y->setLeft(x);
        x->setParent(y);

    } else {
        // x is the root set y to the root
        this->root_ = y;
        y->setParent(NULL);
        y->setLeft(x);
        x->setParent(y);
    }
    // now the nodes are in place. update x's height and then y's
    int x_l_h = (x->getLeft() == NULL) ? 0 : x->getLeft()->getHeight();
    int x_r_h = (x->getRight() == NULL) ? 0 : x->getRight()->getHeight();
    x->setHeight(std::max(x_l_h, x_r_h) + 1);
    int y_l_h = (y->getLeft() == NULL) ? 0 : y->getLeft()->getHeight();
    int y_r_h = (y->getRight() == NULL) ? 0 : y->getRight()->getHeight();
    y->setHeight(std::max(y_l_h, y_r_h) + 1);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* z) {
    // parent keeps n's right child as left child
    AVLNode<Key, Value>* y = z->getLeft();
    AVLNode<Key, Value>* c = y->getRight();
    // first fix c
    if (c) {
        // if c exists c is z' left child, otherwise z' left child is null
        z->setLeft(c);
        c->setParent(z);
    } else {
        z->setLeft(NULL);
    }
    // check if z has a parent
    if (z->getParent()) {
        AVLNode<Key, Value>* p = z->getParent();
        if (p->getLeft() == z) {
            p->setLeft(y);
        } else {
            p->setRight(y);
        }
        y->setParent(p);
        // now that the parent is sorted out, set z
        y->setRight(z);
        z->setParent(y);
    } else {
        // z is currently root, first move y to root
        this->root_ = y;
        y->setParent(NULL);
        y->setRight(z);
        z->setParent(y);
    }
    // set z height and then y height
    // now the nodes are in place. update x's height and then y's
    int z_l_h = (z->getLeft() == NULL) ? 0 : z->getLeft()->getHeight();
    int z_r_h = (z->getRight() == NULL) ? 0 : z->getRight()->getHeight();
    z->setHeight(std::max(z_l_h, z_r_h) + 1);
    int y_l_h = (y->getLeft() == NULL) ? 0 : y->getLeft()->getHeight();
    int y_r_h = (y->getRight() == NULL) ? 0 : y->getRight()->getHeight();
    y->setHeight(std::max(y_l_h, y_r_h) + 1);
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key) {
    // TODO
    // AVLNode<Key, Value>* to_delete = BinarySearchTree<Key, Value>::find(key);
    // if (to_delete == NULL)
    //     return;
    // AVLNode<Key, Value>* pred = BinarySearchTree<Key, Value>::predecessor(to_delete);
    // AVLNode<Key, Value>* pred_parent = pred->getParent();
    AVLNode<Key, Value>* to_delete = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
    // if the node we're removing doesn't exist, then don't do anything
    if (to_delete != NULL) {
        if (to_delete->getLeft() == NULL && to_delete->getRight() == NULL) {
            // is a leaf
            AVLNode<Key, Value>* to_delete_p = to_delete->getParent();
            if (to_delete == static_cast<AVLNode<Key, Value>*>(this->root_)) {
                delete to_delete;
                this->root_ = NULL;
            } else {
                AVLNode<Key, Value>* parent = to_delete->getParent();
                if (parent->getLeft() == to_delete) {
                    parent->setLeft(NULL);
                } else {
                    parent->setRight(NULL);
                }
                delete to_delete;
                removeFix(to_delete_p);
            }
        } else if ((to_delete->getLeft() != NULL && to_delete->getRight() != NULL)) {
            // has 2 child nodes
            // find predecessor and swap into correct position, then delete
            // predeccessior cant b null bc to_delete has left child
            AVLNode<Key, Value>* pred
                    = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(to_delete));
            nodeSwap(pred, to_delete);
            // if to_delete now has children, move the children up
            // remove link to to_delete from its parent
            if (to_delete->getLeft() == NULL) {
                AVLNode<Key, Value>* to_delete_p = to_delete->getParent();

                if (to_delete_p->getLeft() == to_delete) {
                    to_delete_p->setLeft(NULL);
                } else {
                    to_delete_p->setRight(NULL);
                }
                delete to_delete;
                removeFix(to_delete_p);
            } else {
                // if there is a left child
                AVLNode<Key, Value>* to_delete_p = to_delete->getParent();

                AVLNode<Key, Value>* child = to_delete->getLeft();
                // if to_delete has a parent
                if (to_delete_p->getLeft() == to_delete) {
                    to_delete_p->setLeft(child);
                } else {
                    to_delete_p->setRight(child);
                }
                child->setParent(to_delete_p);
                delete to_delete;
                removeFix(to_delete_p);
            }
        } else {
            // has 1 child node
            // find child, swap, and delete
            AVLNode<Key, Value>* to_delete_p = to_delete->getParent();
            AVLNode<Key, Value>* child = (to_delete->getLeft() == NULL) ? to_delete->getRight() : to_delete->getLeft();
            // if to_delete is root, we need to j set child parent to none set it to root and delete to_delete
            if (to_delete == static_cast<AVLNode<Key, Value>*>(this->root_)) {
                child->setParent(NULL);
                this->root_ = child;
                delete to_delete;
            } else {
                // if to_delete is not root
                if (to_delete_p->getLeft() == to_delete) {
                    to_delete_p->setLeft(child);
                } else {
                    to_delete_p->setRight(child);
                }
                child->setParent(to_delete_p);
                delete to_delete;
                // remove fix on the parent of the node we j removed
                removeFix(to_delete_p);
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2) {
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

#endif
