#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <typename ITEM_TYPE>
struct node
{
public:
	node(const ITEM_TYPE& item = ITEM_TYPE(), 
		node<ITEM_TYPE>* next = nullptr);

	template <typename U>
	friend ostream& operator <<(ostream& outs, 
		const node<U> &printMe);

	ITEM_TYPE _item; //crate
	node* _next; //label
};

template<typename ITEM_TYPE>
node<ITEM_TYPE>::node(const ITEM_TYPE& item, 
	node<ITEM_TYPE>* next)
	:_item(item), _next(next){
}

template<typename U>
ostream& operator <<(ostream& outs, 
	const node<U> &printMe){
	outs << printMe._item;
	return outs;
}
#endif //NODE_H