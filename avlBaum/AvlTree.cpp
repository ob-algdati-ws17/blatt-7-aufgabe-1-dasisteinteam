#include "AvlTree.h"

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

AvlTree::Node::Node(Node *parent, int value) {
    this->parent = parent;
    this->value = value;
    this->child_left = nullptr;
    this->child_right = nullptr;
    this->bal = 0;

}

AvlTree::~AvlTree() {
    delete root;
}

bool AvlTree::isEmpty() {
    return root == nullptr;
}

bool AvlTree::hasChild(Node *p) {
    return p->child_right != nullptr || p->child_left != nullptr;
}

bool AvlTree::addValue(int val) {
    // first element
    if(isEmpty()) {
        root = new Node(nullptr, val);
        return true;
    }

    //other elements
    Node* p = add(val, root);
    if(p != nullptr && p->parent != nullptr) {
        upIn(p->parent);
    }
    return true;
}

AvlTree::Node* AvlTree::add(int val, Node *p) {

    // value found
    if(p->value == val) {
        return nullptr;
    }
        //dive in left side
    else if(val < p->value) {
        if (p->child_left == nullptr) {
            p->child_left = new Node(p, val);
            p->bal -= 1;
            return p->child_left;
        } else {
            return add(val, p->child_left);
        }
    }
        //dive in right side
    else {
        if(p->child_right == nullptr) {
            p->child_right = new Node(p, val);
            p->bal += 1;
            return p->child_right;
        }
        else {
            return add(val, p->child_right);
        }
    }
}

bool AvlTree::searchValue(int val) {

    Node* p = root;
    while(true) {
        if(p == nullptr) {
            return false;
        }
        else if(p->value == val) {
            return true;
        }
        else if(val < p->value){
            p = p->child_left;
        }
        else {
            p = p->child_right;
        }
    }

}

void AvlTree::upIn(Node *p) {

    if(p->parent == nullptr) {
        return;
    }
    // linker nachfolger
    if(p->value < p->parent->value) {
        //Fall 1.1
        if(p->parent->bal == 1) {
            p->parent->bal = 0;
        }
            // Fall 1.2
        else if(p->parent->bal == 0) {
            p->parent->bal = -1;
        }
            // Fall 1.3
        else {
            if(p->bal == -1) {
                rotateRight(p);
                return;
            }
            else if(p->bal == 1) {
                rotateLeft(p->child_right);
                rotateRight(p->parent);
                return;
            }
        }
    }
        //rechter nachfolger
    else {
        //Fall 1.1
        if(p->parent->bal == -1) {
            p->parent->bal = 0;
        }
            // Fall 1.2
        else if(p->parent->bal == 0) {
            p->parent->bal = 1;
        }
            // Fall 1.3
        else {
            if(p->bal == 1) {
                rotateLeft(p);
                return;
            }
            else if(p->bal == -1) {
                rotateRight(p->child_left);
                rotateLeft(p->parent);
                return;
            }
        }
    }

    upIn(p->parent);
}

void AvlTree::rotateRight(Node *p) {

    Node* parent = p->parent;
    if(p->parent == root) {
        root = p;
    }
    parent->child_left = p->child_right;
    p->child_right = parent;

    p->parent = parent->parent;
    parent->parent = p;

    if(p->parent != nullptr) {
        if (p->parent->child_left == p->child_right) {
            p->parent->child_left = p;
        } else {
            p->parent->child_right = p;
        }
    }

    p->bal = 0;
    parent->bal = 0;
}

void AvlTree::rotateLeft(Node *p) {

    Node* parent = p->parent;
    if(p->parent == root) {
        root = p;
    }
    parent->child_right = p->child_left;
    p->child_left = parent;

    p->parent = parent->parent;
    parent->parent = p;

    if(p->parent != nullptr) {
        if (p->parent->child_left == p->child_left) {
            p->parent->child_left = p;
        } else {
            p->parent->child_right = p;
        }
    }

    p->bal = 0;
    parent->bal = 0;
}

std::string AvlTree::print() {
    return printTree(root) + "\n";
}

std::string AvlTree::printTree(Node *p) {

    //preorder
    if(p == nullptr) {
        return "";
    }
    return std::to_string(p->value) + ", " + printTree(p->child_left) + printTree(p->child_right);

}