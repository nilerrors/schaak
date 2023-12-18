//
// Created by nilerrors on 06/12/2023.
//

#ifndef WEEK12_WO_ARRAYLIST_H
#define WEEK12_WO_ARRAYLIST_H

template<typename T>
class ArrayList {
    int size;
    int capacity;
    T* items;

public:
    ArrayList();

    explicit ArrayList(int capacity);

    virtual ~ArrayList();

    void clearList();
    bool isEmpty() const;
    int getSize() const;
    bool set(int index, const T& newItem);
    bool get(int index, T& item) const;
    const T& getItem(int index) const;
    bool del(int index);
    void doubleCapacity();
    void add(const T& newItem);
    void insert(int index, const T& newItem);


};


#endif //WEEK12_WO_ARRAYLIST_H
