#include <iostream>

using namespace std;

namespace calc{
    template<typename T>
    class queue : private list<T>{
        public:
            using list<T>::list;
            void enqueue(const T& val){
                list<T>::push_back(val);
            }
            T dequeue(){
                if (list<T>::is_empty()){
                    throw out_of_range("Pusta kolejka");
                }
                T el = list<T>.head->el;
                list<T>::remove_front();
                return el;
            }
            bool is_empty(){
                return list<T>::is_empty();
            }
    };
    template<typename T>
    class stack : private list<T>{
        public:
            using list<T>::list;
            void push(const T& val){
                list<T>::push_front(val);
            }
            T pop(){
                if (list<T>::is_empty()){
                    throw out_of_range("Pusta kolejka");
                }
                T el = list<T>.head->el;
                list<T>::remove_front();
                return el;
            }
            bool is_empty(){
                return list<T>::is_empty();
            }
    };
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
            void clear(){
                while (head != nullptr) {
                    node* temp = head;
                    head = head->next;
                    delete temp;
                }
                tail = nullptr;
                size = 0;
            }
        public:
            list() : head(nullptr),tail(nullptr),size(0){} //konstruktor domyslny
            list(const list<T> &l) : head(l.head),tail(l.tail),size(l.size){} //konstruktor kopiujacy
            list(list<T> &&l) : head(l.head),tail(l.tail),size(l.size){ //konstruktor przenoszacy
                l.head = nullptr;
                l.tail = nullptr;
                l.size = nullptr;
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
            list<T>& operator=(const list<T>&& l){
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
            void insert(const T &value, int pos){
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
            void push_front(const T &value){
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
            void push_back(const T &value){
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
            void remove(int pos){
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
            void remove_front(){
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
            void remove_back(){
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
            void remove_first_val(const T& val){
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
            void remove_all_same_val(const T& val){
                if(head==nullptr){
                    throw invalid_argument("Pusta lista");
                }
                int ilosc = all_elems_same_val(val);
                while(ilosc>0){
                    remove_first_val(val);
                    ilosc--;
                }
            }
            bool is_empty() const{
                if (head==nullptr){
                    return true;
                }
                return false;
            }
            int find(const T& val) const{
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
                if (curr==nullptr){
                    clog<<"Nie ma takiego value w liscie"<<endl;
                }
            }
            int all_elems(){
                return size;
            }
            int all_elems_same_val(const T& val){
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
            friend ostream& operator<<(ostream& os, const list<T>& l) {
            if (l.head == nullptr){
                os << "List is empty";
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
    };
}

// int main(){
//     calc::list<int> myList;
//     myList.push_back(1);
//     myList.push_back(2);
//     myList.push_back(3);
//     myList.push_front(0);
//     myList.insert(3, 2);
//     myList.push_back(3);
//     myList.push_back(2);
//     myList.push_back(4);
//     myList.push_back(5);
//     cout<<myList.all_elems()<<endl;
//     cout << "All elements: "<<myList<<endl;
//     myList.remove_all_same_val(3);
//     myList.remove_first_val(2);
//     myList.remove(0);
//     myList.remove_front();
//     myList.remove_back();
//     cout << "All elements: "<<myList<<endl;
//     cout<<myList.all_elems()<<endl;
//     cout<<myList.all_elems_same_val(2)<<endl;
//     if(myList.is_empty()){
//         cout<<"Lista jest pusta";
//     }
//     else{
//         cout<<"List nie jest pusta";
//     }
//     return 0;
// }