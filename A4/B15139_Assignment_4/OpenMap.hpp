#ifndef OPENMAP_HPP_
#define OPENMAP_HPP_
#include "Dictionary.hpp"
#include<limits.h>
#include <iostream>
using namespace std;
using namespace cs202;

namespace cs202
{
template<class Key, class Value>
class OpenMap  : public Dictionary<Key,Value>
{
    /*
     * Function rehash:
     * Resizes the has table to the next convenient size.
     * Called when all the slots are full and a new element needs to be inserted.
     */
	void rehash();
public:
 	OpenMap();
 	OpenMap(const int& num);
 	OpenMap(OpenMap<Key, Value>& ht);
 	~OpenMap();
	Value& operator[](const Key& key);
    bool has(const Key& key);
    bool remove(const Key& key);
    Value get(const Key& key);
    void put(const Key& key, const Value& value);
    void print();
};

template<class Key, class Value>
void OpenMap<Key,Value>::rehash(){
    LinearList<pair<Key,Value> > ntab ;
    LinearList<int> nexist ;
    int psize = this->size;
    ntab.resize(psize);
    nexist.resize(psize);
    for(int i = 0 ;i<psize;i++)
    {
        ntab[i]=this->hashTable[i];
        nexist[i]=this->exist[i];
    }
    this->mod=2*this->mod;
    this->hashTable.resize(this->mod);
    this->exist.resize(this->mod);
    this->exist.fill(0);
	this->size=0;
    for(int i = 0 ;i<psize;i++)
    {
        if(nexist[i]==1)
            this->put(ntab[i].first,ntab[i].second);
    }
}
template<class Key, class Value>
OpenMap<Key,Value>::OpenMap()
{   int i;
    this->hashTable.resize(103);
    this->exist.resize(103);
    this->mod=103;
    for(i=0;i<103;i++)
		this->exist[i] = 0;
	this->size = 0;
}

template<class Key, class Value>
OpenMap<Key,Value>::OpenMap(const int& num)
{
    int i;
    this->hashTable.resize(num);
    this->exist.resize(num);
    this->mod=num;
    for(i=0;i<num;i++)
		this->exist[i] = 0;
	this->size = 0;

}

template<class Key, class Value>
OpenMap<Key,Value>::OpenMap(OpenMap<Key, Value>& ht)
{   int i;
        this->hashTable.resize(ht.mod);
    this->exist.resize(ht.mod);
    this->mod=ht.mod;
    for(i=0;i<ht.mod;i++)
		this->exist[i] = ht.exist[i];
        this->hashTable[i]=ht.hashTable[i];
	this->size = ht.size;
}

template<class Key, class Value>
OpenMap<Key,Value>::~OpenMap(){
    this->hashTable.~LinearList();
    this->exist.~LinearList();
}

template<class Key, class Value>
Value& OpenMap<Key,Value>::operator[](const Key& key)
{
    int ind=this->hash(key);
    int i=0;
    while(this->exist[ind] && i < this->mod)
	{
		if(this->exist[ind] == -1 || this->hashTable[ind].first != key)
		{
			ind++;
			ind %= this->mod;
			i++;
		}
		else
		{
			return this->hashTable[ind].second;
		}
	}

}

template<class Key, class Value>
bool OpenMap<Key,Value>::has(const Key& key)
{
    int ind=this->hash(key);
    int i=0;
    while(this->exist[ind] && i < this->mod)
	{
		if(this->exist[ind] == -1 || this->hashTable[ind].first != key)
		{
			ind++;
			ind %= this->mod;
			i++;
		}
		else
		{
			return true;
		}
	}
    return false;    
}

template<class Key, class Value>
bool OpenMap<Key,Value>::remove(const Key& key)
{
    int ind=this->hash(key);
    int i=0;
    while(this->exist[ind] && i < this->mod)
	{
		if(this->exist[ind] == -1 || this->hashTable[ind].first != key)
		{
			ind++;
			ind %= this->mod;
			i++;
		}
		else
		{
            this->exist[ind] = -1;
			this->size--;
            return true;
		}
	}
    return false;
}


template<class Key, class Value>
Value OpenMap<Key,Value>::get(const Key& key)
{
        int ind=this->hash(key);
    int i=0;
    while(this->exist[ind] && i < this->mod)
	{
		if(this->exist[ind] == -1 || this->hashTable[ind].first != key)
		{
			ind++;
			ind %= this->mod;
			i++;
		}
		else
		{
			return this->hashTable[ind].second;
		}
	}
	if(i == this->mod || this->exist[ind] == 0)
	{
     //   return INT_MAX;
	}
}

template<class Key, class Value>
void OpenMap<Key,Value>::put(const Key& key, const Value& value)
{
    int ind=this->hash(key);
    int i=0;
    while(this->exist[ind]==1 && i < this->mod)
	{
		if(this->hashTable[ind].first == key)
		break;
			ind++;
			ind %= this->mod;
			i++;
	}
    if(i == this->mod)
	{
        cout<<"Hash Table Full!"<<endl;
		this->rehash();
       return; 
	}
    this->exist[ind]=1;
    this->size++;
    this->hashTable[ind]=make_pair(key,value);
}

template<class Key, class Value>
void OpenMap<Key,Value>::print()
{
    for(int i=0;i<this->mod;i++)
	{
		if(this->exist[i] == 1)
			cout<<this->hashTable[i].first<<" "<<this->hashTable[i].second<<endl;
	}
}


}

#endif 