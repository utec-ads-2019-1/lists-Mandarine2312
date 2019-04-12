#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

template <typename T>
class CircularLinkedList : public List<T> {
    public:
        CircularLinkedList() : List<T>() {}

        T front() {
            return this->head->data;
        }

        T back() {
            return this->tail->data;
        }

        void push_front(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
            if(this->nodes == 0) {
                this->head = newNode;
                this->tail = newNode;
            }else{
                newNode->prev = this->tail;
                newNode->next = this->head;
                this->head->prev = newNode;
                this->tail->next = newNode;
                this->head= newNode;
            }
        }

        void push_back(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
            if(this->nodes == 0) {
                this->head = newNode;
                this->tail = newNode;
            }else{
                newNode->prev = this->tail;
                newNode->next = this->head;
                this->head->prev = newNode;
                this->tail->next = newNode;
                this->tail= newNode;
            }
            this->nodes++;
        }

        void pop_front() {
            this->head = this->head->next;
            delete this->head->prev;
            this->tail->next = this->head;
            this->head->prev = this->tail;
            this->nodes--;
        }

        void pop_back() {
            this->tail = this->tail->prev;
            delete this->tail->next;
            this->tail->next = this->head;
            this->head->prev = this->tail;
            this->nodes--;
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
            this->head->killChainCircular(this->tail);
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
                this->head = this->tail;
                this->head = this->tail->next;
            }else if(this->nodes >2){
                auto nextNode = this->head->next;
                do{
                    this->head->next = this->head->prev;
                    this->head->prev = nextNode;
                    this->head = nextNode;
                    nextNode = nextNode->next;
                }while(this->head->next != this->tail); //optimizar????
                this->head->next = this->head->prev;
                this->head->prev = this->tail;
            }
        }

        string name() {
            return "Circular Linked List";
        }

        BidirectionalIterator<T> begin() {
            // TODO
        }

	    BidirectionalIterator<T> end() {
            // TODO
        }

        void merge(CircularLinkedList<T> list) {
            for(int i = 0; i < list.size(); i++){
                this->push_back(list[i]);
            }
        }
};

#endif