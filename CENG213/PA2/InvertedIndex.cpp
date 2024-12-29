#include "InvertedIndex.h"

#include <fstream>
#include <iostream>

InvertedIndex::InvertedIndex() {

}

InvertedIndex::InvertedIndex(const InvertedIndex &obj) {

    this->invertedIndex = obj.invertedIndex; // uses operator= of BST
}

InvertedIndex::~InvertedIndex() {

}

TreeMap<std::string, std::vector<int> >  &InvertedIndex::getInvertedIndex() {

    return invertedIndex;
}


InvertedIndex &InvertedIndex::addDocument(const std::string &documentName, int docid) {
    /* TODO */
    std::ifstream file(documentName.c_str(), std::ifstream::in);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << documentName << std::endl;
        return *this;
    }

    std::string word;
    while (file >> word) {
        // Check if the word is already in the inverted index
        if (invertedIndex.containsKey(word)) {
            //invertedIndex[word] = docid; /*???*/
            std::vector<int>& docidVector = invertedIndex[word];
            bool doesExist = false;

            for (unsigned int i = 0; i < docidVector.size(); i++){
                if (docid == docidVector[i]){
                    doesExist = true;
                    break;
                }
            }
            
            if (doesExist == false){
                unsigned int i = 0;
                while(i < docidVector.size() && docid > docidVector[i]){
                    i++;
                }
                docidVector.insert(docidVector.begin() + i, docid); /* ITERATOR */
            }
        } else {
            std::vector<int> v;
            v.push_back(docid);
            invertedIndex.put(word, v);
        }
    }

    file.close();
    return *this;

}

std::vector<int> InvertedIndex::search(const std::string &query) {
    std::vector<int> result;
    std::string word;
    for (unsigned int i = 0; i <= query.size(); ++i) {
        if (query[i] != ' ' && i != query.size()){
            word += query[i];
        }
        else{
            if (!word.empty() && invertedIndex.containsKey(word)){
                unsigned int j = 0;
                unsigned int k = 0;
                std::vector<int>& docidVector = invertedIndex[word];
                std::vector<int> temp;

                while (j < result.size() && k < docidVector.size()) {
                    if (result[j] < docidVector[k]) {
                        temp.push_back(result[j]); j++;
                    } else if (result[j] > docidVector[k]) {
                        temp.push_back(docidVector[k]); k++;
                    } else {
                        temp.push_back(docidVector[k]);
                        j++;
                        k++;
                    }
                }
                    if (docidVector.size() > k)
                        while (k < docidVector.size()) temp.push_back(docidVector[k++]);
                    if (result.size() > j)
                        while (j < result.size()) temp.push_back(result[j++]);
                    result = temp;
            }
            word = "";
        }
    }    
    return result;
}

InvertedIndex & InvertedIndex::printInvertedIndex() const {

    invertedIndex.print();

}

InvertedIndex &InvertedIndex::operator=(const InvertedIndex &rhs) {

    this->invertedIndex = rhs.invertedIndex; // uses operator= of BST

    return *this;
}
