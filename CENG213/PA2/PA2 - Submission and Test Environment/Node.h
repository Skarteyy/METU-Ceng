#ifndef NODE_H
#define NODE_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

template<class T>
class Node {
public:
    Node() {
        this->left = NULL;
        this->right = NULL;
        this->height= 0;
    }

    Node(const T &element, Node<T> *left, Node<T> *right,size_t height) {
        this->element = element;
        this->left = left;
        this->right = right;
        this->height = height;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << "Node(" << node.element << node.height  <<")";
        return os;
    }

    T element;
    size_t height;
    Node<T> *left;
    Node<T> *right;
};

#endif //NODE_H
