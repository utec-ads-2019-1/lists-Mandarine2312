#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killChainCircular(Node<T> * tail) {
        if(next != tail){
            next->killChainCircular(tail);
        }
        delete this;
    }

    void killChain(){
        if(next != nullptr){
            next->killChain();
        }
        delete this;
    }
};

#endif