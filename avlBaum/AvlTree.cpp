#include "AvlTree.h"
#include <cmath>

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
    // when p i a nullptr, the value was already in the tree
    // -> do nothing
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

    Node* p = search(val);

    return p != nullptr;

}

AvlTree::Node* AvlTree::search(int val) {

    Node* p = root;
    while(true) {
        if(p == nullptr) {
            return nullptr;
        }
        else if(p->value == val) {
            return p;
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

    if(p == root) {
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

bool AvlTree::remove(Node *p) {
    Node* parent;
    parent = p->parent;
    // Fall 1 : 2 Blätter
    if(p->child_right == nullptr && p->child_left == nullptr) {
        if (p == root) {
            root = nullptr;
            delete p;
            return true;
        }
        if(parent->child_left == p) {
            parent->child_left = nullptr;

            //check height
            if(parent->child_right != nullptr) {
                // height 2
                if (parent->child_right->child_left != nullptr) {
                    rotateRight(parent->child_right->child_left);
                    rotateLeft(parent->child_right);
                }
                else if(parent->child_right->child_right != nullptr) {
                    rotateLeft(parent->child_right);
                }
                    // height 1
                else {
                    parent->bal = 1;
                    delete p;
                    return true;
                }
            }
            // height 0
            else {
                parent->bal = 0;
            }
        }
        else {
            parent->child_right = nullptr;

            //check height
            if(parent->child_left != nullptr) {
                // height 2
                if (parent->child_left->child_right != nullptr) {
                    rotateLeft(parent->child_left->child_right);
                    rotateRight(parent->child_right);
                }
                else if(parent->child_left->child_left != nullptr) {
                    rotateRight(parent->child_left);
                }
                // height 1
                else {
                    parent->bal = -1;
                    delete p;
                    return true;
                }
            }
            // height 0
            {
                parent->bal = 0;
            }
        }

    }
        //Fall 2 : 1 Blatt, 1 Nachfolger
    else if (p->child_right != nullptr && p->child_left == nullptr) {
        if(p == root) {
            root = p->child_right;
            p->child_right->parent = nullptr;
        }
        else {
            if(parent->child_right == p) {
                parent->child_right = p->child_right;
                p->child_right->parent = parent;
            }
            else {
                parent->child_left = p->child_right;
                p->child_right->parent = parent;
            }
        }
    }
    else if(p->child_left != nullptr && p->child_right == nullptr) {
        if(p == root) {
            root = p->child_left;
            p->child_left->parent = nullptr;
        }
        else {
            if(parent->child_left == p) {
                parent->child_left = p->child_left;
                p->child_left->parent = parent;
            }
            else {
                parent->child_right = p->child_left;
                p->child_left->parent = parent;
            }
        }
    }
        // Fall 3: 2 Nachfolger
    else {
        Node* symChild = getSymChild(p);
        p->value = symChild->value;
        return remove(symChild);

    }


    delete p;
    upOut(parent);
    return true;
}

bool AvlTree::removeValue(int val) {

    Node* p = search(val);

    if(p == nullptr) {
        return true;
    }

    return remove(p);
}


AvlTree::Node * AvlTree::getSymChild(Node *p) {

    // there is no need for security nullptr checks because this function is only called when the
    // given parameter p has two childs;
    Node* right = p->child_right;
    Node* left = p->child_left;

        while(right->child_left != nullptr) {
            right = right->child_left;
        }

        while(left->child_right != nullptr) {
            left = left->child_right;
        }

    if(right->value - p->value  < p->value - left->value) {
        return right;
    }
    else {
        return left;
    }


}

void AvlTree::upOut(Node * p) {

    if( p == root) {
        return;
    }

    // linker nachfolger
    if(p->parent->child_left == p) {

        if(p->parent->bal == -1) {
            p->parent->bal = 0;
        }
        else if (p->parent->bal == 0){
            p->parent->bal = 1;
            return;
        }
        else {
            //1.3.1
            if(p->parent->child_right->bal == 0) {
                rotateLeft(p->parent->child_right);
                // correct bal because bal is set in rotate
                p->parent->bal = 1;
                p->parent->parent->bal = -1;
                return;
            }
                //1.3.2
            else if(p->parent->child_right->bal == 1) {
                rotateLeft(p->parent->child_right);
            }
                //1.3.3
            else {
                rotateRight(p->parent->child_right->child_left);
                rotateLeft(p->parent->child_right);
                return;
            }
        }
    }
    // rechter nachfolger
    else {
        if(p->parent->bal == 1) {
            p->parent->bal = 0;
        }
        else if (p->parent->bal == 0){
            p->parent->bal = -1;
            return;
        }
        else {
            //1.3.1
            if(p->parent->child_left->bal == 0) {
                rotateRight(p->parent->child_left);
                // correct bal because bal is set in rotate
                p->parent->bal = -1;
                p->parent->parent->bal = 1;
                return;
            }
                //1.3.2
            else if(p->parent->child_left->bal == -1) {
                rotateRight(p->parent->child_left);
            }
                //1.3.3
            else {
                rotateLeft(p->parent->child_left->child_right);
                rotateRight(p->parent->child_left);
                return;
            }
        }
    }

    upOut(p->parent);

}