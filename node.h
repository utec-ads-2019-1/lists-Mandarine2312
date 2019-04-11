#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killSelf() {
        //TODO
    }

    void killChain(){
        if(next != nullptr){
            next->killChain();
        }
        delete next;
    }
};

#endif