#include "LinkedList.h"

template <class ItemType>
class DequeType: protected LinkedListType<ItemType>
{
public:
	void InsertLeft(ItemType);
	void InsertRight(ItemType);
	ItemType RemoveLeft();
	ItemType RemoveRight();
	int LengthIs();
	void MoveCurPos();
	ItemType GetItem();
};

template <class ItemType>
ItemType DequeType<ItemType>::GetItem()
{
	return LinkedListType<ItemType>::GetItem();
}
template <class ItemType>
void DequeType<ItemType>::MoveCurPos()
{
	LinkedListType<ItemType>::MoveCurPos();
}
template <class ItemType>
void DequeType<ItemType>::InsertLeft(ItemType item)
{
	AddToFront(item);
}

template <class ItemType>
void DequeType<ItemType>::InsertRight(ItemType item)
{
	AddToRear(item);
}

template <class ItemType>
ItemType DequeType<ItemType>::RemoveLeft()
{
	ItemType temp;

	ResetListForward();
	if (GetNextItem(temp))
	{
		DeleteItem(temp);
		return temp;
	}
	else
		return temp;
}

template <class ItemType>
ItemType DequeType<ItemType>::RemoveRight()
{
	ItemType temp;

	ResetListBackward();
	if (GetPreviousItem(temp))
	{
		DeleteItem(temp);
		return temp;
	}
	else
		return temp;
}

template <class ItemType>
int DequeType<ItemType>::LengthIs()
{
	return LinkedListType<ItemType>::LengthIs();
}