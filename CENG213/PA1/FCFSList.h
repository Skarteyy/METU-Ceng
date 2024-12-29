#ifndef FCFS_LIST_H
#define FCFS_LIST_H

#include <cstring>
#include <iostream>

template<class T>
struct FCFSNode
{
    T           item;
    FCFSNode*   next;

    FCFSNode(const T&, FCFSNode* node = NULL);
};

template<class T>
class FCFSList
{
    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const FCFSList<U>&);

    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const FCFSList<U*>&);

    private:
    FCFSNode<T>*    head;

    public:
    // Constructors & Destructor
                FCFSList();
                FCFSList(const FCFSList&);
    FCFSList&   operator=(const FCFSList&);
                ~FCFSList();

    //
    void    Enqueue(const T& item);
    T       Dequeue();
    bool    IsEmpty() const;
};

#include "FCFSList_impl.h"

#endif