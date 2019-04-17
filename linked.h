#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template <typename T>
class LinkedList : public List<T> {
    public:
        LinkedList() : List<T>() {}

        T front() {
            return this->head->data;
        }

        T back() {
            return this->tail->data;
        }

        void push_front(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
        }

        void push_back(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
            if (this->nodes == 0) {
                this->head = newNode;
                this->tail = newNode;
            } else {
                newNode->prev = this->tail;
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->nodes++;
        }

        void pop_front() {
            if(this->nodes ==1){
                delete this->head;
                this->head = nullptr;
                this->tail = nullptr;
            }else if(this->nodes > 1){
                this->head = this->head->next;
                delete this->head->prev;
                this->head->prev = nullptr;
                this->nodes--;
            }
        }

        void pop_back() {
            if(this->nodes ==1){
                delete this->head;
                this->head = nullptr;
                this->tail = nullptr;
            }else if(this->nodes > 1){
                this->tail = this->tail->prev;
                delete this->tail->next;
                this->tail->next = nullptr;
                this->nodes--;
            }
        }

        T operator[](int index) {
            if(index >= this->nodes){
                throw std::out_of_range("Error: requested position is out of the list's range");
            }
            if(index < (this->nodes)/2){
                auto temp = this->head;
                for(int i = 0; i < index; i++){
                    temp = temp->next;
                }
                return temp->data;
            }else{
                auto temp = this->tail;
                for(int i = 0; i < (this->nodes)-index-1; i++){
                    temp = temp->prev;
                }
                return temp->data;
            }
        }

        bool empty() {
            if(this->nodes == 0){
                return true;
            }else{
                return false;
            }
        }

        int size() {
            return this->nodes;
        }

        void clear() {
            this->head->killChain();
            this->head = nullptr;
            this->tail = nullptr;
            this->nodes = 0;
        }

        void sort() {
            for(int i = this->nodes-2; i >= 0; i--){
                auto temp = this->head;
                for(int j = 0; j < i; j++){
                    temp = temp->next;
                }
                for(int k = i; k < this->nodes-1; k++){
                    compare(temp, temp->next);
                    temp = temp->next;
                }
            }
        }

        void compare(Node<T>* a, Node<T> * b){
            if(a->data > b->data){
                swap(a->data, b->data);
            }
        }

        void reverse() {
            this->tail = this->head;
            if(this->nodes == 2){
                this->head->prev = this->head->next;
                this->head->next = nullptr;
                this->head = this->head->prev;
                this->head->next = this->head->prev;
                this->head->prev = nullptr;
            }else if(this->nodes >2){
                auto nextNode = this->head->next;
                do{
                    this->head->next = this->head->prev;
                    this->head->prev = nextNode;
                    this->head = nextNode;
                    nextNode = nextNode->next;
                }while(this->head->next != nullptr);
                this->head->next = this->head->prev;
                this->head->prev = nullptr;
            }
        }

        string name() {
            return "Linked List";
        }

        BidirectionalIterator<T> begin() {
            auto newIt = new BidirectionalIterator<T>(this->head);
            return *newIt;
        }

	    BidirectionalIterator<T> end() {
            auto tempEnd = new Node<T>;
            tempEnd->prev = this->tail;

            auto newIt = new BidirectionalIterator<T>(tempEnd);
            return *newIt;
        }

        void merge(LinkedList<T> list) {
            for(int i = 0; i < list.size(); i++){
                this->push_back(list[i]);
            }
        }
};

#endif