#ifndef FCFS_LIST_IMPL_H
#define FCFS_LIST_IMPL_H

template<class T>
FCFSNode<T>:: FCFSNode(const T& t, FCFSNode* node)
    : item(t)
    , next(node)
{}

// ============================ //
template<class T>
FCFSList<T>::FCFSList()
    : head(NULL)
{
    // Using a dummy node
    head = new FCFSNode<T>(T());
}

template<class T>
FCFSList<T>::FCFSList(const FCFSList& other)
{
    if (other.head == NULL){
        return;
    }
    
    head = new FCFSNode<T>(T());
    FCFSNode<T>* curr = head;
    FCFSNode<T>* otherCurr = other.head->next;
    while (otherCurr != NULL){
        curr->next = new FCFSNode<T>(otherCurr->item, NULL);
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
}

template<class T>
FCFSList<T>& FCFSList<T>::operator=(const FCFSList& other)
{
    if (this == &other){
        return *this;
    }
    
    FCFSNode<T>* current = head;
    while (current != NULL){
        FCFSNode<T>* temp = current->next;
        delete current;
        current = temp;
    }
    
    head = new FCFSNode<T>(T());
    FCFSNode<T>* curr = head;
    FCFSNode<T>* otherCurr = other.head->next;
    while (otherCurr != NULL){
        curr->next = new FCFSNode<T>(otherCurr->item, NULL);
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    
    return *this;
}

template<class T>
FCFSList<T>::~FCFSList()
{
    FCFSNode<T>* curr = head;
    while (curr != NULL){
        FCFSNode<T>* temp = curr->next;
        delete curr;
        curr = temp;
    }
}

template<class T>
void FCFSList<T>::Enqueue(const T& item)
{
    FCFSNode<T>* curr = head;
    while (curr->next != NULL){
        curr = curr->next;
    }
    curr->next = new FCFSNode<T>(item, NULL);
}

template<class T>
T FCFSList<T>::Dequeue()
{
    if (head->next){
        FCFSNode<T>* temp = head->next;
        T deqItem = temp->item;
        head->next = head->next->next;
        delete temp;
        return deqItem;
    }
    else{
        return T();
    }
        
}

template<class T>
bool FCFSList<T>::IsEmpty() const
{
    return head->next == NULL;
}

#endif