#include <iostream>
#include "nag.hpp"

using namespace std;

int main(){
    calc::list<int> myList;
    calc::list<int> l2;
    l2=myList;
    cout<<"l2: "<<l2<<endl;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_front(0);
    myList.insert(3, 2);
    myList.push_back(3);
    myList.push_back(2);
    myList.push_back(4);
    myList.push_back(5);
    cout<<"Elementy w liscie: "<<myList.all_elems()<<endl;
    cout << "All elements: "<<myList<<endl;
    myList.remove_all_same_val(3);
    myList.remove_first_val(2);
    myList.remove(0);
    myList.remove_front();
    myList.remove_back();
    cout << "All elements: "<<myList<<endl;
    cout<<"Elementy w liscie: "<<myList.all_elems()<<endl;
    cout<<"Elementy o wart 2: "<<myList.all_elems_same_val(2)<<endl;
    if(myList.is_empty()){
        cout<<"Lista jest pusta"<<endl;
    }
    else{
        cout<<"Lista nie jest pusta"<<endl;
    }
    return 0;
}