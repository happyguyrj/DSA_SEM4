/*
 * queue.hpp
 *
 * functionality of a singly linked-list
 *
 * define your methods in coherence with the following
 * function signatures
 * 
 * 
 */
#ifndef LIST_HPP
#define LIST_HPP 1
#include <iostream>
#include "Dictionary.hpp"
using namespace std;
namespace cs202
{   

template<class T>
class list;

    

template<class T>
class listnode{
    friend class list<T>;
    public:
            T data;
            listnode *link;

};

  template<class T>
    class list
    {
        public:  
            listnode<T> *first;
            listnode<T> *last;
                int len;

        list();
        list(const list<T> & x);
        ~list();
        void append(const T& value);
        inline int length();
        inline bool empty();
        void cons(const T& value);
        void remove(const T & x);
        void print();
        void append(list<T>& x);
            
    };
    
    template<class T>
    list<T>::list(){
        first=NULL;
        last=NULL;
        len=0;
    }
    
    template<class T>
    list<T>::list(const list<T> & x)
    {    first=NULL;
         last=NULL;
        len=0;

         listnode<T> *tmp=x.first;
        while ( tmp!= NULL ) 
       
        {   
            this->append(tmp->data);
            tmp = tmp->link;
        }

    }
    
    template<class T>
    list<T>::~list()
    {
        listnode<T> *tmp;
        while (first) 
       
        {   tmp = first->link;
            delete first;
            first=tmp;
        }
        len=0;
    }
    
    
    template<class T>
    void list<T>::append(const T& value)
    {
        listnode<T>* newnode=new listnode<T>();
        newnode->data=value;
        //cout<<(newnode->data).first;
        //cout<<(newnode->data).second;
        newnode->link=NULL;
         listnode<T> *tmp = last;
    if ( tmp != NULL ) {

        last->link=newnode;
        last=newnode;
    len++;
    }
    else {
    first = last = newnode;
    len++;
    }
    
    }

     template<class T>
    void list<T>::print()
    {
        listnode<T> *tmp=first;
        while ( tmp!= NULL ) 
       
        {   
            cout<<(tmp->data).first<<" "<<(tmp->data).second<<endl;
            tmp = tmp->link;
        }
    }
  

    template<class T>
    inline int list<T>::length(){
        return len;
    }

    template<class T>
    inline bool list<T>::empty()
    {
        if (len>0) return false;
        return true;
    }
    
    template<class T>
    void list<T>::cons(const T& value)
    {
        listnode<T>* newnode=new listnode<T>();
        newnode->data=value;
        newnode->link=NULL;
         listnode<T> *tmp = first;
         first=newnode;
         first->link=tmp;
         len++;
    }
    
        template<class T>
    void list<T>::remove(const T & x)
    {
        listnode<T> *tmp = first,*tmp2=NULL;
        if((tmp->data).first==x.first){
        	tmp = first->link;
            delete first;
            first=tmp;
            len--;
        }
        else{while (tmp->link!=NULL) 
       
        {   
            if((tmp->link->data).first==x.first) 
            {
                
                tmp2=tmp->link;
                tmp->link=tmp->link->link;
                if(tmp->link==NULL) last=tmp;
                delete tmp2;
                len--;
                return;
            }
            tmp = tmp->link;
        }
        return;}

    }

           template<class T>
    void list<T>::append(list<T>& x){

         listnode<T> *tmp=x.first;
        last->link=tmp;
        last=x.last;
        len=len+x.len;

    }



}

#endif