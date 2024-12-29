#ifndef DSWTREE_H
#define DSWTREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class DSWTree {
public: // DO NOT CHANGE THIS PART.
    DSWTree();

    DSWTree(const DSWTree<T> &obj);

    ~DSWTree();

    bool isEmpty() const;

    int getHeight() const;
    
    const int getNodeHeight(const T& element) const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    DSWTree<T> &operator=(const DSWTree<T> &rhs);

    bool isBalanced();

    void balance();

    void createBackbone(Node<T> *&root);

    void createCompleteTree(Node<T> *&root, int size);

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    void removeTree(Node<T>*& node);
    void copyTree(Node<T>* curr, Node<T>*& newNode);
    void changeHeights(Node<T> *r);
    void rotateWithLeftChild(Node<T> *&r);
    void rotateWithRightChild(Node<T> *&r);
    
    bool insert(Node<T> *&r,const T &element);
    bool remove(Node<T> *&r, const T &element);
    bool isBalanced(Node<T> *r);

    
    int getSize(Node<T> *r) const;
    
    const T &get(Node<T> *r,const T &element) const;
    const Node<T> &getNode(Node<T> *r, const T &element) const;
    Node<T>* copyNodes(const Node<T>* otherNode);

    const T &getMin(Node<T> *r) const;
    const T &getMax(Node<T> *r) const;

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;
};

template<class T>
DSWTree<T>::DSWTree() {
    root = NULL;
}

template<class T>
DSWTree<T>::DSWTree(const DSWTree<T> &obj) {
    
    if (obj.root == NULL){
        root = NULL; /*this might change*/
    }
    else{
        root = copyNodes(obj.root);
    }
}

template<class T>
DSWTree<T>::~DSWTree() {
    removeTree(root);
    root = NULL;
}

template<class T>
bool DSWTree<T>::isEmpty() const {
    return root == NULL;
}

template<class T>
int DSWTree<T>::getHeight() const {
    if (root == NULL) return -1;
    return root->height;
}

template<class T>
int DSWTree<T>::getSize() const {
    return getSize(root);
}
template<class T>
bool DSWTree<T>::insert(const T &element) {
    return insert(root, element);
}
template<class T>
bool DSWTree<T>::remove(const T &element) {
    return remove(root, element);
}

template<class T>
void DSWTree<T>::removeAllNodes() {
    removeTree(root);
    root = NULL;
}

template<class T>
const T &DSWTree<T>::get(const T &element) const {
    return get(root, element);
}

template<class T>
void DSWTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;        
    } else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    }
}

template<class T>
void DSWTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        if (node != NULL){
            std::cout << "\t" << node->element;
            if (node->left) {
                std::cout << "," << std::endl;
            }
            //std::cout << "\t";
            print(node->left,preorder);
            if (node->right) {
                std::cout << "," << std::endl;
            }
            print(node->right,preorder);
        }
    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == postorder) {
        if (node == NULL)
            return;

        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        std::cout << "\t" << node->element;
    }
}

template<class T>
void DSWTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void DSWTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
DSWTree<T> &DSWTree<T>::operator=(const DSWTree<T> &rhs) {
    if (this == &rhs) return *this;
    removeAllNodes();
    copyTree(rhs.root, root);
    return *this;
}

template <class T>
void DSWTree<T>::balance() {
    if (!root) return;
    createBackbone(root);
    createCompleteTree(root, getSize());
}

template <class T>
bool DSWTree<T>::isBalanced() {
    return isBalanced(root);
}

template <class T>
void DSWTree<T>::createBackbone(Node<T> *&root) {
    
    Node<T>** curr = &root;
    while(*curr){
        if ((*curr)->left){
            rotateWithLeftChild(*curr);
        }
        else {
            curr = &((*curr)->right);
        }
    }
}

template <class T>
void DSWTree<T>::createCompleteTree(Node<T> *&root, int size) {
    int m = pow(2,floor(log2(size+1))) - 1;
    Node<T>** curr = &root;
    
    for (int i = 0; i < size - m; i++){
        rotateWithRightChild(*curr);
        curr = &((*curr)->right);
    }
    
    curr = &root;
    /*
    for (int i = 0; i < floor(log2(size+1));i++){
        curr = &((*curr)->right);
        rotateWithRightChild(*curr);
        
    }
    
    if (m%2 == 1){
        rotateWithRightChild(root);
    }*/
    
    while (m > 1){
        m = m / 2;
        for (int i = 0; i< m; i++){
            rotateWithRightChild(*curr);
            curr = &((*curr)->right);
        }
        curr = &root;
        //curr = &((*curr)->right);
        //root = *curr;
    }
}

template<class T>
const T &DSWTree<T>::getCeiling(const T &element) const {
    if (getMax() < element) throw NoSuchItemException();
    Node<T>* ceiling = NULL;
    Node<T>* curr = root;
    while (curr){
        if (curr->element == element) return curr->element;
        if (curr->element < element){
            curr = curr->right;
        } 
        else{
            ceiling = curr;
            curr = curr->left;
        }
    }
    if (ceiling) return ceiling->element;
    else throw NoSuchItemException();
}

template<class T>
const T &DSWTree<T>::getFloor(const T &element) const {
    if (getMin() > element) throw NoSuchItemException();
    Node<T>* flooring = NULL;
    Node<T>* curr = root;
    while(curr){
        if (curr->element == element) return curr->element;
        if (curr->element > element){
            curr = curr->left;
        }
        else{
            flooring = curr;
            curr = curr->right;
        }
    }
    if (flooring) return flooring->element;
    else throw NoSuchItemException();
}

template<class T>
const T &DSWTree<T>::getMin() const {
    return getMin(root);
}

template<class T>
const T &DSWTree<T>::getMax() const {
    return getMax(root);
}

template<class T>
const T &DSWTree<T>::getNext(const T &element) const {
    if (getMax() < element) throw NoSuchItemException();
    Node<T>* next = NULL;
    Node<T>* curr = root;
    while (curr){
        if (curr->element < element || curr->element == element){
            curr = curr->right;
        } 
        else{
            next = curr;
            curr = curr->left;
        }
    }
    if (next) return next->element;
    else throw NoSuchItemException();
}

template<class T>
const int DSWTree<T>:: getNodeHeight(const T& element) const {
    try {
        //Node<T>* node = getNode(root, element);
        int nodeHeight = getNode(root, element).height;
        return nodeHeight;
    } 
    catch (const NoSuchItemException&) {
        return -1;
    }
}

template<class T>
Node<T>* DSWTree<T>::copyNodes(const Node<T>* otherNode){
    if (otherNode == NULL){
        return NULL;
    }
    
    Node<T>* newNode = new Node<T>(otherNode->element, NULL, NULL, otherNode->height);
    newNode->right = copyNodes(otherNode->right);
    newNode->left = copyNodes(otherNode->left);
    return newNode;
}

template<class T>
void DSWTree<T>::removeTree(Node<T>*& node){
    if (node == NULL){
        return;
    }
    removeTree(node->right);
    removeTree(node->left);
    delete node;
    node = NULL;
}

template<class T>
bool DSWTree<T>::insert(Node<T> *&r, const T &element){
    bool isInserted = false;
    if (r == NULL){
        r = new Node<T>(element, NULL, NULL, 0);
        return true;
    }
    else if (r->element > element){
        isInserted = insert(r->left,element);
    }
    else if (r->element < element){
        isInserted = insert(r->right,element);
    }
    else return false;
    
    if (isInserted) changeHeights(r);
    return isInserted;
}

template<class T>
bool DSWTree<T>::remove(Node<T> *&r, const T &element){
    if (r == NULL) return false;
    if (r->element > element){
        return remove(r->left, element);
    }
    else if (r->element < element){
        return remove(r->right, element);
    }
    else{
        if (r->left != NULL && r->right != NULL){
            r->element = getMin(r->right);
            remove(r->right, r->element);
        }
        else{
            Node<T>* oldNode = r;
            r = (r->left != NULL)? r->left : r->right;
            delete oldNode;
            return true;
        }
    }
}

template<class T>
const T &DSWTree<T>::getMin(Node<T> *r) const{
    if (r == NULL) {
        throw NoSuchItemException();
    }
    if (!r->left) return r->element;
    else return getMin(r->left);
}

template<class T>
const T &DSWTree<T>::getMax(Node<T> *r) const{
    if (r == NULL) {
        throw NoSuchItemException();
    }
    if (!r->right) return r->element;
    else return getMax(r->right);
}

template<class T>
int DSWTree<T>::getSize(Node<T> *r) const{
    if (r == NULL) return 0;
    return getSize(r->left) + getSize(r->right) + 1;
}

template<class T>
const T &DSWTree<T>::get(Node<T> *r,const T &element) const{
    if (r == NULL){
        throw NoSuchItemException();
    }
    if (r->element == element){
        return r->element;
    }
    else if (element > r->element) {
        return get(r->right, element);
    }
    else if (element < r->element){
        return get(r->left, element);
    }
    else throw NoSuchItemException();
}

template<class T>
const Node<T> &DSWTree<T>::getNode(Node<T> *r, const T &element) const{
    if (r == NULL){
        throw NoSuchItemException();
    }
    if (r->element == element){
        return *r;
    }
    else if (element > r->element) {
        return getNode(r->right, element);
    }
    else if (element < r->element){
        return getNode(r->left, element);
    }
    else throw NoSuchItemException();
}

template<class T>
void DSWTree<T>::copyTree(Node<T>* curr, Node<T>*& newNode){
    if (curr == NULL){
        newNode = NULL;
        return;
    }
    newNode = new Node<T>(curr->element, NULL, NULL, 0);
    copyTree(curr->left, newNode->left);
    copyTree(curr->right, newNode->right);
}

template<class T>
void DSWTree<T>::changeHeights(Node<T> *r){
    if (r == NULL) return;
    int left = -1;
    int right = -1;
    if (r->left) left = r->left->height;
    if (r->right) right = r->right->height;
    r->height = 1 + std::max(left,right);
}

template <class T>
bool DSWTree<T>::isBalanced(Node<T> *r) {
    if (r == NULL) return true;
    int leftHeight = -1;
    int rightHeight = -1;
    
    if (r->left){
        leftHeight = r->left->height;
        //std::cout << "LeftHeight:" << r->left->height << std::endl;
    }
    if (r->right){
        rightHeight = r->right->height;
        //std::cout << "RightHeight:" << r->right->height << std::endl;
    }
    if (abs(leftHeight - rightHeight) > 1){
        return false;
    }
    
    return isBalanced(r->left) && isBalanced(r->right);
}

template <class T>
void DSWTree<T>::rotateWithLeftChild(Node<T> *&r){
    Node<T>* leftNode = r->left;
    r->left = leftNode->right;
    leftNode->right = r;
    changeHeights(r);
    changeHeights(leftNode);
    r = leftNode;
}

template <class T>
void DSWTree<T>::rotateWithRightChild(Node<T> *&r){
    Node<T>* rightNode = r->right;
    r->right = rightNode->left;
    rightNode->left = r;
    changeHeights(r);
    changeHeights(rightNode);
    r = rightNode;
}



#endif //DSWTREE_H













