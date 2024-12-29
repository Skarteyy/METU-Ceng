#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "DSWTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key); // Declaration of the new method

    bool deletekey(const K &key); // Declaration of the new method

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

    int size();

    void balance();

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    DSWTree<KeyValuePair<K, V> > stree;

};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    stree.removeAllNodes(); 
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    const KeyValuePair<K,V> &pair = stree.get(key);
    return pair.getValue();

}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    return stree.getCeiling(key); 
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    return stree.getMin();
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    return stree.getMax();
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {
    std::vector<KeyValuePair<K, V> > v;
    KeyValuePair<K, V> first = stree.getCeiling(fromKey);
    
    while(first <= toKey) {
        v.push_back(first);
        if (first < stree.getMax())
            first = stree.getNext(first);
        else break;
    }

    return v;
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# DSWTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

template<class K, class V>
void TreeMap<K, V>::put(const K &key, const V &value) {
    KeyValuePair<K, V> pair(key, value);

    stree.remove(pair);

    stree.insert(pair);
}

template<class K, class V>
V& TreeMap<K, V>::operator[](const K &key) const {
    const KeyValuePair<K, V>& pair = stree.get(KeyValuePair<K, V>(key));
    return const_cast<V&>(pair.getValue());
}

template<class K, class V>
bool TreeMap<K, V>::deletekey(const K &key) {
    if (stree.remove(key)) return true;
    else return false;
}
template<class K, class V>
bool TreeMap<K, V>::containsKey(const K &key) {
    try{
        stree.get(KeyValuePair<K, V>(key));
        return true;
    } catch(const NoSuchItemException&){
        return false;
    }
}

template<class K, class V>
void TreeMap<K, V>::balance() {
    stree.balance();
}

#endif //TREEMAP_H
