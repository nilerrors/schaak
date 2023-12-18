//
// Created by nilerrors on 06/12/2023.
//

#ifndef SCHAAK_ARRAYLIST_H
#define SCHAAK_ARRAYLIST_H

template <class T>
class ArrayList {
    int size;
    int capacity;
    T* items;

   public:
    explicit ArrayList();

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

template <class T>
ArrayList<T>::ArrayList() {
    size = 0;
    capacity = 10;
    items = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(int capacity) {
    size = 0;
    this->capacity = capacity;
    items = new T[capacity];
}

template <class T>
ArrayList<T>::~ArrayList() {
    if (items != nullptr) delete[] items;
}

template <class T>
void ArrayList<T>::clearList() {
    size = 0;
    for (int i = 0; i < capacity; i++) {
        items[i] = 0;
    }
}

template <class T>
bool ArrayList<T>::isEmpty() const {
    return size == 0;
}

template <class T>
int ArrayList<T>::getSize() const {
    return size;
}

template <class T>
bool ArrayList<T>::set(int index, const T& newItem) {
    if (index >= size || index < 0) {
        return false;
    } else {
        items[index] = newItem;
        return true;
    }
}

template <class T>
bool ArrayList<T>::get(int index, T& item) const {
    if (index >= size || index < 0) {
        return false;
    } else {
        item = items[index];
        return true;
    }
}

template <class T>
const T& ArrayList<T>::getItem(int index) const {
    if (index >= size || index < 0) {
        throw "Index out of range";
    }
    return items[index];
}

template <class T>
bool ArrayList<T>::del(int index) {
    if (index >= size || index < 0) {
        return false;
    } else {
        // all elements after the deleted index are now shifted to the left
        for (int i = index; i < size - 1; i++) {
            items[i] = items[i + 1];
        }
        size--;
        return true;
    }
}

template <class T>
void ArrayList<T>::doubleCapacity() {
    T* newItems = new T[capacity * 2];
    // copy content lst->items to newItems
    for (int i = 0; i < size; i++) {
        newItems[i] = items[i];
    }
    // delete previous list
    delete[] items;
    // update new lst
    items = newItems;
    capacity = capacity * 2;
}

template <class T>
void ArrayList<T>::add(const T& newItem) {
    if (size == capacity) {
        doubleCapacity();
    }
    items[size] = newItem;
    size++;
}

template <class T>
void ArrayList<T>::insert(int index, const T& newItem) {
    if (size == capacity) {
        doubleCapacity();
    }
    for (int i = size - 1; i >= index; i--) {
        items[i + 1] = items[i];
    }
    items[index] = newItem;
    size += 1;
}

#endif  // SCHAAK_ARRAYLIST_H
