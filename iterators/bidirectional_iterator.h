#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "../iterator.h"

template <typename T> 
class BidirectionalIterator : public Iterator<T> {
    public:
        BidirectionalIterator() : Iterator<T>() {};
        BidirectionalIterator(Node<T> *node) : Iterator<T>(node) {};

        BidirectionalIterator<T> operator=(BidirectionalIterator<T> other) {
            this->current = other.current;
            // Falta return
        }

        bool operator!=(BidirectionalIterator<T> other) {
            return this->current != other.current;
        }

        BidirectionalIterator<T> operator++() {
            this->current = this->current->next;
            // Falta return
        }

        BidirectionalIterator<T> operator--() {
            this->current = this->current->prev;
            // Falta return
        }

        T operator*() {
            // Si la lista está vacía?
            return this->current->data;
        }
};

#endif