#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <cassert>

template<class T>
struct SortedListNode
{
    T*  item;
    SortedListNode<T>*  next;
    SortedListNode<T>*  prev;
    //
    SortedListNode(T* item,
                   SortedListNode* nextNode = NULL,
                   SortedListNode* prevNode = NULL);
};

template<class T>
class SortedList
{
    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const SortedList<U>&);

    private:
    SortedListNode<T>* head;
    SortedListNode<T>* back;

    public:
    // Constructors & Destructor
                    SortedList();
                    SortedList(const SortedList& list);
    SortedList&     operator=(const SortedList& list);
                    ~SortedList();

    // Insert patient into the list
    // Add
    void        InsertItem(T*);
    void        InsertItemPrior(T*);
    // Remove
    T*          RemoveFirstItem();
    T*          RemoveFirstItem(int priority);
    T*          RemoveLastItem(int priority);
    // Query
    const T*    FirstItem() const;
    const T*    LastItem() const;

    // Modification
    bool        IsEmpty() const;
    void        ChangePriorityOf(int priorty,
                                 int newPriority);
    void        Split(SortedList&, SortedList&, int priority);
    //
    static SortedList   Merge(const SortedList&,
                              const SortedList&);
};

#include "SortedList_impl.h"

#endif