#ifndef SORTED_LIST_IMPL_H
#define SORTED_LIST_IMPL_H

template<class T>
SortedListNode<T>::SortedListNode(T* itemIn,
                                  SortedListNode* nextNodeIn,
                                  SortedListNode* prevNodeIn)
    : item(itemIn)
    , next(nextNodeIn)
    , prev(prevNodeIn)
{}

template<class T>
SortedList<T>::SortedList()
    : head(NULL)
    , back(NULL)
{}

template<class T>
SortedList<T>::SortedList(const SortedList& other)
    : head(NULL)
    , back(NULL)
{
    if (other.head == NULL){
        return;
    }

    head = new SortedListNode<T>(new T(*(other.head->item)), NULL, NULL);
    SortedListNode<T>* curr = head;
    SortedListNode<T>* otherCurr = other.head->next;
    
    while(otherCurr != NULL){
        curr->next = new SortedListNode<T>(new T(*(otherCurr->item)), NULL, curr);
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    back = curr;
}

template<class T>
SortedList<T>& SortedList<T>::operator=(const SortedList& other)
{   
    if (this == &other){
        return *this;
    }
    
    SortedListNode<T>* current = head;
    while (current != NULL){
        SortedListNode<T>* temp = current->next;
        current->prev = NULL;
        current->next = NULL;
        delete current->item;
        delete current;
        current = temp;
    }
    if (other.head == NULL){
        return *this;
    }
    head = new SortedListNode<T>(new T(*(other.head->item)), NULL, NULL);
    SortedListNode<T>* curr = head;
    SortedListNode<T>* otherCurr = other.head->next;
    
    while(otherCurr != NULL){
        curr->next = new SortedListNode<T>(new T(*(otherCurr->item)), NULL, curr);
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    back = curr;
    
    return *this;
}

template<class T>
SortedList<T>::~SortedList()
{
    SortedListNode<T>* curr = head;
    while (curr != NULL){
        SortedListNode<T>* temp = curr->next;
        curr->prev = NULL;
        curr->next = NULL;
        delete curr->item;
        delete curr;
        curr = temp;
    }
}

template<class T>
void SortedList<T>::InsertItem(T* i)
{
    SortedListNode<T>* node = new SortedListNode<T>(i,NULL,NULL);
    
    if (head == NULL){
        head = back = node;
        return;
    }
    
    SortedListNode<T>* curr = head;
    
    if (*node->item < *head->item) {
        node->next = head;
        head->prev = node;
        head = node;
        return;
    }
    
    while ((curr != NULL) && (*curr->item < *node->item || *node->item == *curr->item)){
        if (curr->next == NULL){
            curr->next = node;
            node->prev = curr;
            back = node;
            return;
        }
        curr = curr->next;
    }
    node->next = curr;
    node->prev = curr->prev;
    node->prev->next = node;
    node->next->prev = node;
    
}

template<class T>
void SortedList<T>::InsertItemPrior(T* i)
{
    SortedListNode<T>* node = new SortedListNode<T>(i);
    if (head == NULL){
        head = back = node;
        return;
    }
    
    SortedListNode<T>* curr = head;
    
    if (*node->item < *head->item) {
        node->next = head;
        head->prev = node;
        head = node;
        return;
    }
    if (*node->item == *head->item) {
        node->next = head;
        head->prev = node;
        head = node;
        return;
    }
    
    while ((curr != NULL) && (*curr->item < *node->item)){
        if (curr->next == NULL){
            curr->next = node;
            node->prev = curr;
            back = node;
            return;
        }
        curr = curr->next;
    }
    
    node->next = curr;
    node->prev = curr->prev;
    node->prev->next = node;
    node->next->prev = node;
}

template<class T>
T* SortedList<T>::RemoveFirstItem()
{
    if (head == NULL) return NULL;
    T* theItem = head->item;
    SortedListNode<T>* temp = head;
    if (head->next){
        head = head->next;
        head->prev = NULL;
    }
    else {
        head = back = NULL;
    }
    delete temp;
    return theItem;
}

template<class T>
T* SortedList<T>::RemoveFirstItem(int priority)
{
    if (head == NULL) return NULL;
    SortedListNode<T>* curr = head;
    SortedListNode<T>* temp;
    while (curr != NULL && !(*curr->item == priority)){
        curr = curr->next;
    }
    if (curr == NULL) return NULL;
    temp = curr;
    T* theItem = curr->item;
    if (curr->prev){
        if (curr->next){
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        else{
            back = curr->prev;
        }
    }
    else{
        if(curr->next){
            head = head->next;
            head->prev = NULL;
        }
        else {
            head = back = NULL;
        }
    }
    delete temp;
    return theItem;
}

template<class T>
T* SortedList<T>::RemoveLastItem(int priority)
{
    if (head == NULL) return NULL;
    SortedListNode<T>* curr = head;
    SortedListNode<T>* last = NULL;
    SortedListNode<T>* temp = NULL;
    T* theItem;
    while (curr != NULL){
        if (*curr->item == priority){
            last = curr;
        }
        curr = curr->next;
    }
    if (last == NULL) return NULL;
    temp = last;
    theItem = last->item;
    
    if (last->prev){
        if (last->next){
            last->prev->next = last->next;
            last->next->prev = last->prev;
        }
        else{
            back = last->prev;
            last->prev->next = NULL;
        }
    }
    else{
        if(last->next){
            head = last->next;
            head->prev = NULL;
        }
        else {
            head = back = NULL;
        }
    }
    delete temp;
    return theItem;
    
}

template<class T>
const T* SortedList<T>::FirstItem() const
{
    return (head) ? head->item : NULL;
}

template<class T>
const T* SortedList<T>::LastItem() const
{
    return (back) ? back->item : NULL;
}

template<class T>
bool SortedList<T>::IsEmpty() const
{
    return head == NULL;
}

template<class T>
void SortedList<T>::ChangePriorityOf(int priority, int newPriority)
{
    if (head == NULL) return;
    SortedListNode<T>* curr = head;
    int length = 0;
    int i = 0;
    while (curr != NULL){
        if (*curr->item == priority){
            curr->item->setPriority(newPriority);
        }
        curr = curr->next;
        length++;
    }
    
    T** items = new T*[length];
    while (!IsEmpty()){
        items[i] = RemoveFirstItem();
        i++;
    }

    for (i = 0; i<length; i++){
        InsertItem(items[i]);
    }
    delete[] items;

}

template<class T>
void SortedList<T>::Split(SortedList& listLeft,
                          SortedList& listRight,
                          int priority)
{
    assert(listLeft.head == NULL);
    assert(listRight.head == NULL);

    if (head == NULL) return;
    
    SortedListNode<T>* curr = head;

    while(curr != NULL){
        T* theItem = RemoveFirstItem();

        if (*theItem < priority){
            listLeft.InsertItem(theItem);
        }
        else{
            listRight.InsertItem(theItem);
        }
        curr = head;
    }
}

template<class T>
SortedList<T> SortedList<T>::Merge(const SortedList& list0,
                                   const SortedList& list1)
{
   SortedList<T> newList;
   SortedListNode<T>* list0curr = list0.head;
   SortedListNode<T>* list1curr = list1.head;
   while (list0curr != NULL){
       T* theItem = new T(*list0curr->item);
       newList.InsertItemPrior(theItem);
       list0curr = list0curr->next;
   }
   while (list1curr != NULL){
       T* theItem = new T(*list1curr->item);
       newList.InsertItem(theItem);
       list1curr = list1curr->next;
   }
   return newList;
}

#endif