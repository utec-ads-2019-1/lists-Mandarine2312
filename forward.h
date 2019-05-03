#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {}

        T front() {
            // Si la lista está vacía?
            return this->head->data;
        }

        T back() {
            // Si la lista está vacía?
            return this->tail->data;
        }

        void push_front(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
            newNode->next = this->head;
            this->head = newNode;
        }

/*    Esta implementación no usa tail
            void push_back(T value) {
            auto * newNode = new Node<T>;
            newNode->data = value;
            newNode->next = nullptr;

            if(this->head == nullptr){
                this->head = newNode;
            }else{
                auto temp = this->head;
                while(temp->next != nullptr){
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            this->nodes++;
        }*/

        void push_back(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
            newNode->next = nullptr;

            if(this->head == nullptr){
                this->head = newNode;
                this->tail = newNode;
            }else{
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->nodes++;
        }

        void pop_front() {
            if(this->nodes ==1) {
                delete this->head;
                this->head = nullptr;
                this->tail = nullptr;
            }else if(this->nodes > 1){
                auto temp = this->head;
                this->head = this->head->next;
                delete temp;
                this->nodes--;
            }
        }

        void pop_back() {
            if(this->nodes ==1) {
                delete this->head;
                this->head = nullptr;
                this->tail = nullptr;
            }else if(this->nodes > 1){
                auto temp = this->head;
                while(temp->next != this->tail){
                    temp = temp->next;
                }
                this->tail = temp;
                delete this->tail->next;
                this->tail->next = nullptr;
                this->nodes--;
            }
        }

        T operator[](int index) {
            if(index >= this->nodes){
                throw std::out_of_range("Error: requested position is out of the list's range");
            }
            auto temp = this->head;
            for(int i = 0; i < index; i++){
                temp = temp->next;
            }
            return temp->data;
        }

        bool empty() {
            // Podría ser: return this->head == nullptr;
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
                auto temp = this->head->next;
                this->head->next = nullptr;
                temp->next = this->head;
                this->head = temp;
            }else if(this->nodes > 2){
                auto ptrToPrev = this->head;
                auto ptrToCurr = ptrToPrev->next;
                auto ptrToNext = ptrToCurr->next;
                ptrToPrev->next = nullptr;
                do{
                    ptrToCurr->next = ptrToPrev;
                    ptrToPrev = ptrToCurr;
                    ptrToCurr = ptrToNext;
                    ptrToNext = ptrToNext->next;
                }while(ptrToCurr->next != nullptr);
                ptrToCurr->next = ptrToPrev;
                this->head = ptrToCurr;
            }
        }

        string name() {
            return "Forward List";
        }

        ForwardIterator<T> begin() {
            auto newIt = new ForwardIterator<T>(this->head);
            return *newIt;
        }

	    ForwardIterator<T> end() {
            auto newIt = new ForwardIterator<T>(this->tail->next);
            return *newIt;
        }

        void merge(ForwardList<T> list) {
            for(int i = 0; i < list.size(); i++){
                this->push_back(list[i]);
            }
        }
};

#endif