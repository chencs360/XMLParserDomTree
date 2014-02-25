#include "Deque.h"

template <class ItemType>
class StackType: protected DequeType<ItemType>  //could be private as well
{
public:
	void Push(ItemType);
	ItemType Pop();
	int LengthIs();
	bool IsEmpty();
	ItemType GetItem();
	void MoveCurPos();
};
template <class ItemType>
void StackType<ItemType>::MoveCurPos()
{
	DequeType<ItemType>::MoveCurPos();
}
template <class ItemType>
ItemType StackType<ItemType>::GetItem()
{
	return DequeType<ItemType>::GetItem();
}

template <class ItemType>
void StackType<ItemType>::Push(ItemType item)
{
	InsertLeft(item);
}

template <class ItemType>
ItemType StackType<ItemType>::Pop()
{
	return RemoveLeft();
}

template <class ItemType>
int StackType<ItemType>::LengthIs()
{
	return DequeType<ItemType>::LengthIs();
}

template <class ItemType>
bool StackType<ItemType>::IsEmpty()
{
	return (Deque<ItemType>::LengthIs()==0);
}