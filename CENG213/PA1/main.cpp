#include "FCFSList.h"
#include "SortedList.h"
#include "Hospital.h"

#include <iostream>

// These are the "secret" print files. Testers have these exact copies of these
// functions.
template<class T>
std::ostream& operator<<(std::ostream& stream, const FCFSList<T>& l)
{
    static const int MAX_PRINT = 100;

    if(l.head->next == NULL) stream << "Empty";
    //
    int printLimit = 0;
    for(const FCFSNode<T>* n = l.head->next; n != NULL; n = n->next)
    {
        stream << n->item;
        if(n->next != NULL) stream << " -> ";
        //
        printLimit++;
        if(printLimit == MAX_PRINT)
        {
            stream << std::endl << "***PrintLimitExceeded***" << std::endl;
            return stream;
        }
    }
    stream << std::endl;
    return stream;
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const FCFSList<T*>& l)
{
    static const int MAX_PRINT = 100;

    if(l.head->next == NULL) stream << "Empty";
    //
    int printLimit = 0;
    for(const FCFSNode<T*>* n = l.head->next; n != NULL; n = n->next)
    {
        stream << (*n->item);
        if(n->next != NULL) stream << " -> ";
        //
        printLimit++;
        if(printLimit == MAX_PRINT)
        {
            stream << std::endl << "***PrintLimitExceeded***" << std::endl;
            return stream;
        }
    }
    stream << std::endl;
    return stream;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const SortedList<T>& l)
{
    static const int MAX_PRINT = 100;

    stream << "Front to Back" << std::endl;
    if(l.head == NULL)
    {
        stream << "Empty" << std::endl;
    }
    else
    {
        int printLimit = 0;
        for(const SortedListNode<T>* n = l.head; n != NULL; n = n->next)
        {
            stream << *n->item;
            if(n->next != NULL) stream << " <-> ";
            //
            printLimit++;
            if(printLimit == MAX_PRINT)
            {
                stream << std::endl << "***PrintLimitExceeded***" << std::endl;
                return stream;
            }
        }
        stream << std::endl;
    }
    stream << "Back to Front" << std::endl;
    if(l.back == NULL)
    {
        stream << "Empty" << std::endl;
    }
    else
    {
        int printLimit = 0;
        for(const SortedListNode<T>* n = l.back; n != NULL; n = n->prev)
        {
            stream << *n->item;
            //
            if(n->prev != NULL) stream << " <-> ";
        }
        stream << std::endl;
        //
        printLimit++;
        if(printLimit == MAX_PRINT)
        {
            stream << std::endl << "***PrintLimitExceeded***" << std::endl;
            return stream;
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Hospital& h)
{
    stream << "***Reg Queue***" << std::endl;
    stream << h.regQueue << std::endl;

    stream << "***Exam Queue***" << std::endl;
    stream << h.examQueue << std::endl;

    stream << "***Events***" << std::endl;
    stream << h.eventQueue << std::endl;

    stream << "***Patients under Exam***" << std::endl;
    if(h.patientsInExam[0])
        stream << *(h.patientsInExam[0]) << std::endl;
    else
        stream << "Empty" << std::endl;
    stream << "--\n";
    if(h.patientsInExam[1])
        stream << *(h.patientsInExam[1]) << std::endl;
    else
        stream << "Empty" << std::endl;
    stream << "--";
    stream << std::endl;
    return stream;
}

// ========================= //
//           MAIN            //
// ========================= //
int main()
{
    // You can test using this main.
    FCFSList<int> newList;
    /*
    newList.Enqueue(0);
    newList.Enqueue(3);
    newList.Enqueue(5);*/
    Doctor d0(1);
    Doctor d1(3);
    Hospital h1(d0, d1, 2, 40);
    h1.AddPatient(1, 2);
    //h1.AddPatient(2, 3);
    //h1.AddPatient(3, 3);
    //h1.AddPatient(4, 3);

    for(int i = 0; i < 12; i++) std::cout << h1.DoSingleEventIteration();
    
    //std::cout << newList;
}







