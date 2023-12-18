//
// Created by nilerrors on 06/12/2023.
//

#include "ArrayList.h"

template<typename T>
ArrayList<T>::ArrayList() : capacity(1), size(0), items(new T[1]) {}

template<typename T>
ArrayList<T>::ArrayList(int capacity) : capacity(capacity), size(0), items(new T[capacity]) {}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] items;
}

template<typename T>
void ArrayList<T>::clearList() {
    size = 0;
    for(int i=0; i<capacity; i++){
        items[i] = 0;
    }
}

template<typename T>
bool ArrayList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
int ArrayList<T>::getSize() const {
    return size;
}

template<typename T>
bool ArrayList<T>::set(int index, const T& newItem) {
    if(index >= size or index <0 ){
        return false;
    }
    else{
        items[index] = newItem;
        return true;
    }
}

template<typename T>
bool ArrayList<T>::get(int index, T &item) const {
    if(index >= size or index <0 ){
        return false;
    }
    else{
        item = items[index];
        return true;
    }
}

template<typename T>
bool ArrayList<T>::del(int index) {
    if(index >= size or index <0 ){
        return false;
    }
    else{
        //all elements after the deleted index are now shifted to the left
        for(int i = index; i < size-1;i++){
            items[i] = items[i+1];
        }
        size--;
        return true;
    }
}

template<typename T>
void ArrayList<T>::doubleCapacity() {
    int* newItems = new int[capacity * 2];
    //copy content lst->items to newItems
    for(int i=0; i<size; i++){
        newItems[i] = items[i];
    }
    //delete previous list
    delete[] items;
    //update new lst
    items = newItems;
    capacity = capacity * 2;
}

template<typename T>
void ArrayList<T>::add(const T& newItem) {
    if(size == capacity){
        doubleCapacity();
    }
    items[size] = newItem;
    size++;
}

template<typename T>
void ArrayList<T>::insert(int index, const T& newItem) {
    if(size == capacity){
        doubleCapacity();
    }
    for(int i= size - 1; i>=index; i--){
        items[i+1] = items[i];
    }
    items[index] = newItem;
    size +=1;
}
