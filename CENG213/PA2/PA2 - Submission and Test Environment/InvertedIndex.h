#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "TreeMap.h"

class InvertedIndex {
public: // DO NOT CHANGE THIS PART.
    InvertedIndex();

    InvertedIndex(const InvertedIndex &obj);

    ~InvertedIndex();

    TreeMap<std::string, std::vector<int> > &getInvertedIndex();

    InvertedIndex &addDocument(const std::string &documentName,int docid);
    std::vector<int> search(const std::string &query);
    InvertedIndex & printInvertedIndex() const;

    InvertedIndex &operator=(const InvertedIndex &rhs);


private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.

    TreeMap<std::string, std::vector<int> > invertedIndex;

};

#endif //INVERTEDINDEX_H
