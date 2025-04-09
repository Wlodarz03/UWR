#include <iostream>
#include "nag.hpp"

using namespace std;

//list
template <typename T>
void calc::list<T>::clear(){
    while (head != nullptr) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
void calc::list<T>::insert(const T &value, int pos){
    if (pos<0 or pos>size){
        throw invalid_argument("Poza zakresem");
    }
    if(pos==0){
        push_front(value);
    }
    if(pos==size){
        push_back(value);
    }
    else{
        node* curr = head;
        for(int i=0; i<pos-1;i++){
            curr=curr->next;
        }
        curr->next=new node(value,curr->next);
        size++;
    }
}

template<typename T>
void calc::list<T>::push_front(const T &value){
    node* newNode = new node(value);
    if (head==nullptr){
        head=newNode;
        tail=newNode;
        size=1;
    }
    else{
        newNode->next = head;
        head = newNode;
        size++;
    }
}

template<typename T>
void calc::list<T>::push_back(const T &value){
    node* newNode = new node(value);
    if (head==nullptr){
        head = newNode;
        tail = newNode;
        size=1;
    }
    else{
        tail->next=newNode;
        tail = newNode;
        size++;
    }
}

template<typename T>
void calc::list<T>::remove(int pos){
    if (pos<0 or pos>=size){
        throw invalid_argument("Poza zakresem");
    }
    if (head==nullptr){
        throw invalid_argument("Nie mozna usunac z pustej listy");
    }
    if(pos==0){
        remove_front();
        return;
    }
    if(head==tail){
        head=nullptr;
        tail=nullptr;
        size--;
    }
    if(pos==size-1 and size>1){
        remove_back();
        return;
    }
    else{
        node* curr=head;
        for(int i=0;i<pos-1;i++){
            curr=curr->next;
        }
        node* toRemove =curr->next;
        curr->next = toRemove->next;
        toRemove=nullptr;
    }
}

template<typename T>
void calc::list<T>::remove_front(){
    if (head==nullptr){
        throw invalid_argument("Nie mozna usunac z pustej listy");
    }
    if (head==tail){
        head=nullptr;
        tail==nullptr;
        size--;
    }
    else{
        node* toRemove = head;
        head = head->next;
        toRemove=nullptr;
        size--;
    }
}

template <typename T>
void calc::list<T>::remove_back(){
    if (head==nullptr){
        throw invalid_argument("Nie mozna usunac z pustej listy");
    }
    if(head==tail){
        head=nullptr;
        tail=nullptr;
        size--;
    }
    else{
        node* curr=head;
        while(curr->next != tail){
            curr=curr->next;
        }
        tail = curr;
        curr->next = nullptr;
        size--;
    }
}

template<typename T>
void calc::list<T>::remove_first_val(const T& val){
    if(head==nullptr){
        throw invalid_argument("Nie usune z pustej listy");
    }
    if(head==tail){
        if (head->el == val){
            head=nullptr;
            tail=nullptr;
            size--;
        }
    }
    else{
        node* curr=head;
        if (curr->el == val){
            remove_front();
        }
        else{
            for(int i=0;i<size;i++){
                node* x = curr->next;
                if (x == nullptr){
                    if (curr->el ==val){
                        remove_back();
                    }
                }
                else if (x->el == val){
                    curr->next = x->next;
                    delete x;
                    size--;
                    break;
                }
                curr=curr->next;
            }
        }
    }
}

template<typename T>
void calc::list<T>::remove_all_same_val(const T& val){
    if(head==nullptr){
        throw invalid_argument("Pusta lista");
    }
    int ilosc = all_elems_same_val(val);
    while(ilosc>0){
        remove_first_val(val);
        ilosc--;
    }
}

template<typename T>
bool calc::list<T>::is_empty() const{
    if (head==nullptr){
        return true;
    }
    return false;
}

template<typename T>
int calc::list<T>::find(const T& val) const{
    if(head==nullptr){
        throw invalid_argument("Lista pusta nie ma tego elementu");
    }
    node* curr=head;
    for (int i=0;i<size;i++){
        if (curr->el == val){
            return i;
        }
        curr=curr->next;
    }
    return -1;
}

template<typename T>
int calc::list<T>::all_elems(){
    return size;
}

template<typename T>
int calc::list<T>::all_elems_same_val(const T& val){
    int s = 0;
    if(head==nullptr){
        return 0;
    }
    node* curr=head;
    for (int i=0;i<size;i++){
        if (curr->el == val){
            s++;
        }
        curr=curr->next;
    }
    return s;
}
//queue
template<typename T>
void calc::queue<T>::enqueue(const T& val){
    list<T>::push_back(val);
}

template<typename T>
T calc::queue<T>::dequeue(){
    if (list<T>::is_empty()){
        throw out_of_range("Pusta kolejka");
    }
    T el = list<T>::first();
    list<T>::remove_front();
    return el;
}

template<typename T>
bool calc::queue<T>::is_empty(){
    return list<T>::is_empty();
}

//stack
template<typename T>
void calc::stack<T>::push(const T& val){
    list<T>::push_front(val);
}

template <typename T>
T calc::stack<T>::pop(){
    if (list<T>::is_empty()){
        throw out_of_range("Pusta kolejka");
    }
    T el = list<T>::first();
    list<T>::remove_front();
    return el;
}

template <typename T>
bool calc::stack<T>::is_empty(){
    return list<T>::is_empty();
}

template<typename T>
T calc::list<T>::first(){
    return head->el;
}
template class calc::list<int>;
