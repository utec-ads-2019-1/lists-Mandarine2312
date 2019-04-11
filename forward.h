#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {}

        T front() {
            return List<T>::head->data;
        }

        T back() {
            return List<T>::tail->data;
        }

        void push_front(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
            newNode->next = List<T>::head;
            List<T>::head = newNode;
        }

/*    Esta implementación no usa tail
            void push_back(T value) {
            auto * newNode = new Node<T>;
            newNode->data = value;
            newNode->next = nullptr;

            if(List<T>::head == nullptr){
                List<T>::head = newNode;
            }else{
                auto temp = List<T>::head;
                while(temp->next != nullptr){
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            List<T>::nodes++;
        }*/

        void push_back(T value) {
            auto *newNode = new Node<T>;
            newNode->data = value;
            newNode->next = nullptr;

            if(List<T>::head == nullptr){
                List<T>::head = newNode;
                List<T>::tail = newNode;
            }else{
                List<T>::tail->next = newNode;
                List<T>::tail = newNode;
            }
            List<T>::nodes++;
        }

        void pop_front() {
            auto temp = List<T>::head;
            List<T>::head = List<T>::head->next;
            delete temp;
            List<T>::nodes--;
        }

        void pop_back() {
            if(List<T>::nodes > 0){
                auto temp = List<T>::head;
                while(temp->next != List<T>::tail){
                    temp = temp->next;
                }
                delete temp->next;
                temp->next = nullptr;
                List<T>::tail = temp;
                List<T>::nodes--;
            }
        }

        T operator[](int index) { //añadir un throw cuando está out of bounds
            auto temp = List<T>::head;
            for(int i = 0; i < index; i++){
                temp = temp->next;
            }
            return temp->data;
        }

        bool empty() {
            if(List<T>::nodes == 0){
                return true;
            }else{
                return false;
            }
        }

        int size() {
            return List<T>::nodes;
        }

        void clear() {
            List<T>::head->killChain();
            delete List<T>::head;
            List<T>::head = nullptr;
            List<T>::nodes = 0;
        }

        void sort() {
            for(int i = List<T>::nodes-2; i >= 0; i--){
                auto temp = List<T>::head;
                for(int j = 0; j < i; j++){
                    temp = temp->next;
                }
                for(int k = i; k < List<T>::nodes-1; k++){
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
            List<T>::tail = List<T>::head;
            if(List<T>::nodes == 2){
                auto temp = List<T>::head->next;
                List<T>::head->next = nullptr;
                temp->next = List<T>::head;
                List<T>::head = temp;
            }else if(List<T>::nodes > 2){
                auto ptrToPrev = List<T>::head;
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
                List<T>::head = ptrToCurr;
            }
        }

        string name() {
            return "Forward List";
        }

        ForwardIterator<T> begin() {
            // TODO
        }

	    ForwardIterator<T> end() {
            // TODO
        }

        void merge(ForwardList<T> list) {
            for(int i = 0; i < list.size(); i++){
                this->push_back(list[i]);
            }
        }
};

#endif