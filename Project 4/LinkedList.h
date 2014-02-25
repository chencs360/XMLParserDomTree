#include <iostream>

using namespace std;

template <class ItemType>
class LinkedListType
{
	public:
		LinkedListType();
		~LinkedListType();

	    bool IsEmpty() const;
		int LengthIs() const;
		void MakeEmpty();
		bool RetrieveItem(ItemType&);
		void AddToFront(ItemType);
		void InsertInOrder(ItemType);
		void AddToRear(ItemType);
		bool DeleteItem(ItemType);
		void ResetListForward();
		void ResetListBackward();
		bool GetNextItem(ItemType&);
		bool GetPreviousItem(ItemType&);
		ItemType GetItem();
		void MoveCurPos();
		
	protected:

		struct NodeType
		{
			ItemType info;
			NodeType *next;
			NodeType *previous;
			NodeType() {next=previous=0;}
			//~NodeType() {delete next;}
			bool RetrieveItem(ItemType&);
			void InsertInOrder(ItemType, int&);
			bool DeleteItem(ItemType&, int&);
			ItemType GetItem();
		};
		NodeType *listFront;
		NodeType *listRear;
		int length;
		NodeType *currentPos;
};
template <class ItemType>
bool LinkedListType<ItemType>::NodeType::RetrieveItem(ItemType& item)
{
	if (item == info)
		{
			item = info;
			return true;
		}
	else if (next->next)
		return next->RetrieveItem(item);
	else return false;
}
template <class ItemType>
ItemType LinkedListType<ItemType>::GetItem()
{
	return currentPos->GetItem();
}
template <class ItemType>
void LinkedListType<ItemType>::MoveCurPos()
{
	currentPos = currentPos->next;
}
template <class ItemType>
ItemType LinkedListType<ItemType>::NodeType::GetItem()
{
	return info;
}
template <class ItemType>
bool LinkedListType<ItemType>::NodeType::DeleteItem(ItemType& item, int& length)
{
	NodeType *temp;

	if (next && info == item)
	{
		temp = this; //remember node address to delete later
		next->previous = previous;
		previous->next = next; //bypass the node
		temp->next=0;
		delete temp;
		length--;
		return true;
	}
	else if (next)
		return next->DeleteItem(item, length);
	else
		return false;
}

template <class ItemType>
void LinkedListType<ItemType>::NodeType::InsertInOrder(ItemType item, int& length)
{
	if (item < info || next==0) //the new item goes in front of me
	{
		NodeType *temp = new NodeType;

		temp ->info = item;
		temp->previous = previous;
		temp->next = this;
		previous->next = temp;
		previous = temp;
		length++;
	}
	else
		next->InsertInOrder(item, length);
}


template <class ItemType>
LinkedListType<ItemType>::LinkedListType()
{
	listFront = new NodeType;
	listRear = new NodeType;
	listFront->next = listRear;
	listRear->previous = listFront;
	length = 0;
	currentPos = listFront;
}


template <class ItemType>
LinkedListType<ItemType>::~LinkedListType()
{
	delete listFront;
}


template <class ItemType>
bool LinkedListType<ItemType>::IsEmpty() const
{
	return length == 0;
}


template <class ItemType>
int LinkedListType<ItemType>::LengthIs() const
{
	return length;
}



template <class ItemType>
void LinkedListType<ItemType>::MakeEmpty()
{
	delete listFront;
	listFront = new NodeType;
	listRear = new NodeType;
	listFront->next = listRear;
	listRear->previous = listFront;
	length = 0;
	currentPos = 0;
}

template <class ItemType>
bool LinkedListType<ItemType>::RetrieveItem(ItemType &item)
{
	if (length>0)
		return listFront->next->RetrieveItem(item);
	else
		return false;
}


template <class ItemType>
void LinkedListType<ItemType>::AddToFront(ItemType item)
{
	NodeType *temp = new NodeType;

	temp->info = item;
	temp->next = listFront->next;
	temp->previous = listFront;
	listFront->next->previous = temp;
	listFront->next = temp;
	currentPos = listFront->next;
	length++;
}

template <class ItemType>
void LinkedListType<ItemType>::InsertInOrder(ItemType item)
{
	listFront->next->InsertInOrder(item, length);
}
	
template <class ItemType>
void LinkedListType<ItemType>::AddToRear(ItemType item)
{
	NodeType *temp = new NodeType;

	temp->info = item;
	temp->previous = listRear->previous;
	temp->next = listRear;
	listRear->previous->next = temp;
	listRear->previous = temp;
	length++;
}

template <class ItemType>
bool LinkedListType<ItemType>::DeleteItem(ItemType item)
{
	if (length>0)
	{
		currentPos = listFront->next->next;
		return listFront->next->DeleteItem(item, length);
	}
	else
		return false;
}

template <class ItemType>
void LinkedListType<ItemType>::ResetListForward()
{
	currentPos = listFront->next;
}

template <class ItemType>
bool LinkedListType<ItemType>::GetNextItem(ItemType &item)
{
	if (currentPos != listRear)
	{
		item = currentPos->info;
		currentPos = currentPos->next;
		return true;
	}
	else
	{
		return false;
	}
}
template <class ItemType>
void LinkedListType<ItemType>::ResetListBackward()
{
	currentPos = listRear->previous;
}

template <class ItemType>
bool LinkedListType<ItemType>::GetPreviousItem(ItemType &item)
{
	if (currentPos != listFront)
	{
		item = currentPos->info;
		currentPos = currentPos->previous;
		return true;
	}
	else
	{
		return false;
	}
}




