#ifndef NAG
#define NAG

#include <iostream>

using namespace std;

namespace calc{
    template<typename T>
    class list{
        private:
            class node{
                public:
                    T el;
                    node* next;
                    node(const T& val) : el(val),next(nullptr){}
                    node(const T& val, node* n) : el(val),next(n){}
            };
            node* head;
            node* tail;
            int size;
            void clear();
            T first();
        public:
            list() : head(nullptr),tail(nullptr),size(0){} //konstruktor domyslny
            list(const list<T> &l) : head(l.head),tail(l.tail),size(l.size){} //konstruktor kopiujacy
            list(list<T> &&l) : head(l.head),tail(l.tail),size(l.size){ //konstruktor przenoszacy
                l.head = nullptr;
                l.tail = nullptr;
                l.size = 0;
            }
            list<T>& operator=(const list<T>& l){ //przypisanie kopiujace
                if(this==&l){
                    return *this;
                }
                clear();
                node* curr=l.head;
                while (curr!=nullptr){
                    push_back(curr->el);
                    curr=curr->next;
                }
                return *this;
            }
            list<T>& operator=(list<T>&& l){ //przypisanie przenoszace
                if(this==&l){
                    return *this;
                }
                clear();
                head=l.head;
                tail=l.tail;
                size=l.size;
                l.head=nullptr;
                l.tail=nullptr;
                l.size=0;
                return *this;
            }
            friend ostream& operator<<(ostream& os, const list<T>& l){
                if (l.head == nullptr){
                    os << "Lista jest pusta";
                }
                else{
                    node* curr = l.head;
                    while (curr != nullptr) {
                        os << curr->el << "->";
                        curr = curr->next;
                    }
                }
                return os;
            }
            ~list(){
                clear();
            }
            void insert(const T &value, int pos);
            void push_front(const T &value);
            void push_back(const T &value);
            void remove(int pos);
            void remove_front();
            void remove_back();
            void remove_first_val(const T& val);
            void remove_all_same_val(const T& val);
            bool is_empty() const;
            int find(const T& val) const;
            int all_elems();
            int all_elems_same_val(const T& val);   
    };
    template<typename T>
    class queue : private list<T>{
        public:
            using list<T>::list;
            void enqueue(const T& val);
            T dequeue();
            bool is_empty();
    };
    template<typename T>
    class stack : private list<T>{
        public:
            using list<T>::list;
            void push(const T& val);
            T pop();
            bool is_empty();
    };
}

#endif