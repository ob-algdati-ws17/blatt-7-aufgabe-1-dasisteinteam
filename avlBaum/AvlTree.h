#ifndef BLATT_7_AUFGABE_1_DASISTEINTEAM_AVLTREE_H
#define BLATT_7_AUFGABE_1_DASISTEINTEAM_AVLTREE_H
#endif
#include <iostream>
#include <string>

class AvlTree{

private:
    struct Node {
        Node* parent;
        Node* child_left;
        Node* child_right;
        int value;
        int bal;

        Node(Node* parent, int value);
    };

    Node* root = nullptr;

    void upIn(Node* p);
    void rotateRight(Node* p);
    void rotateLeft(Node* p);
    void upOut(Node* *);

    Node* add(int val, Node*p);

    std::string printTree(Node* p);

public:
    ~AvlTree();

    bool addValue(int val);
    bool removeValue(int val);

    bool searchValue(int val);

    bool isEmpty();

    std::string print();

};
