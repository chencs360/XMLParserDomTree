#include "ReadCheck.h"

template <class ItemType>
class Domtree
{
public:
	Domtree();
	Domtree(string, string, ifstream&);
	//void TraverseTree();
	//void AddSibling(int, int);
	//void AddChild();
	void CreateSubTree(string, StackType<string>&, ifstream&);

protected:

	struct Node
	{
		Node();
		Node(string, StackType<string>&, ifstream&)
		{

		}

		Node *Child;
		Node *Sibling;
		string nodeName;
		int nodeType;
		ItemType nodeValue;
		ItemType data;
		int length;
		int depth;
		string inputEncoding;
	};
	Node *firstChild;
	Node *lastChild;
};

template <class ItemType>
Domtree<ItemType>::Domtree()
{
}
template <class ItemType>
Domtree<ItemType>::Domtree(string docname, string tag, ifstream &infile)
{
	StackType<string> headers;
	Node *Document = new Node;
	Document->nodeName = docname;
	Document->nodeType = 9;
	Document->inputEncoding = tag;
	Node *temp = new Node(readIn(infile), headers, infile);
	Document->Child = temp;
	firstChild = Document->Child;
}
//template <class ItemType>
//{
//
//}
template <class ItemType>
void Domtree<ItemType>::CreateSubTree(string tag, StackType<string> &headers, ifstream &infile)
{
	//depth = headers.LengthIs();
	//if (TagType(tag) == 2 || TagType(tag) == 3 || TagType(tag) == 4 || TagType(tag) == 5)
	//{

	//}
	//else if (TagType(tag) == 1)
	//{
	//}
	//else if (TagType(tag) == 6)
	//{
	//}
	//else
	//{
	//	cout << "Error with a tag." << endl;
	//}
}
//template <class ItemType>
//void Domtree<ItemType>::AddSibling(int num, int type, string tag, )
//{
//	Node *temp = new Node;
//	temp->depth = num;
//	temp->nodeType = type;
//	temp->data = tag;
//	temp->length = tag.length();
//
//	listRear->Sibling = temp;
//}