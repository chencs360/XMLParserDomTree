/*Billy Gallon
April 15, 2011
Project 4 DOM Tree
This project will parse an XML document from a .xml file, create a DOM tree from
the input, and then output both a pretty print file and a debugging file*/
#include "ReadCheck.h"

bool KeepChecking()//prompts user to check multiple xml files, to allow for multiple parses before closing the program
{
	char answer;
	cout << "Would you like to parse another file? (Y/N)" << endl;
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		return true;
	else
		return false;
}
struct Node
{
	Node(string docname, string tag, ifstream &infile)
	{//Default constructor for the document node, which is the first node created.
		hasChild = false;
		hasSibling = false;
		error = false;
		StackType<string> headers;
		nodeName = docname;
		nodeType = document;
		inputEncoding = tag;
		AddChild(readIn(infile), headers, infile); 
	}
	Node(string tag, StackType<string> &headers, ifstream &infile)
	{//Constructor to build the rest of the nodes in the tree
		hasChild = false;
		hasSibling = false;
		error = false;
		depth = headers.LengthIs();
		while (tag != "" && !error)
		{
			if (nodeType > -1 && TagType(tag) != close && TagType(tag) != nottag)
			{
				if (tag.substr(2, tag.length()-2).find(nodeName.substr(1, nodeName.length()-1)) != string::npos)
				{//if closing tag to the node currently in
					break;
				}
				else if (nodeType != commentnode)
					AddChild(tag, headers, infile);
				else
					AddSibling(tag, headers, infile);
			}
			else if (nodeType > -1 && TagType(tag) == nottag && data == "")
			{//if a data tag for a node that is already set
				data = tag;
			}
			else if (TagType(tag) == vers)
			{
				cout << "Error, extra version tag in code" << endl;
				error = true;
				break;
			}
			else if (TagType(tag) == selfclose)
			{
				nodeType = element;
				nodeName = tag;
				data = "";
				break;
			}
			else if (TagType(tag) == comment)
			{
				nodeType = commentnode;
				nodeName = tag;
				data = "";
				length = tag.length();
				break;
			}
			else if (TagType(tag) == open)
			{
				headers.Push(tag);
				data = "";
				nodeType = element;
				nodeName = tag;

				if (!infile.eof())
				{
					string temptag = readIn(infile);
					if (TagType(temptag) == close)
					{
						string close = temptag.substr(2, tag.length()-2);
						close = "<" + close;
						close = close.substr(0, close.length()-1);
						if (headers.GetItem().find(close) != string::npos)
						{
							//exit the recursion, node is closed
							headers.Pop();
							break;
						}
						else
						{
							cout << "Error, Malformed/missing/extra closing tag" << temptag << endl;
							error = true;
							break;
						}
					}
					else if (TagType(temptag) == open || TagType(temptag) == selfclose)
					{
						AddChild(temptag, headers, infile);
					}
					else if (TagType(temptag) == nottag)
					{
						data = temptag;
					}
					else if (TagType(temptag) == comment)
					{
						AddChild(temptag, headers, infile);
					}
					else if (TagType(temptag) == vers)
					{
						cout << "Error, extra version tag" << endl;
						error = true;
						break;
					}
				}
				else
					error = true;
			}
			else if (TagType(tag) == close)
			{
				string close = tag.substr(2, tag.length()-2);
				close = "<" + close;
				if (headers.GetItem().find(close) != string::npos)
				{
					headers.Pop();
					break;
					//exit the recursion, node is closed
				}
				else
				{
					cout << "Error, Malformed/missing/extra closing tag" << tag << endl;
					error = true;
					break;
				}
			}
			else if (TagType(tag) == nottag)
			{
				cout << "Error, reading data outside of a tag." << endl;
				error = true;
				break;
			}
			else
			{
				error = true;
				break;
				//exit, file is empty
			}
			if (!infile.eof())
			{//reads another tag to continue the loop of either filling the current node
				//or creating a new one
				tag = readIn(infile);
			}
			else
			{
				tag = "";
			}
		}
	}
	Node *Child;
	Node *Sibling;
	string nodeName;
	int nodeType;
	string nodeValue;
	string data;
	int length;
	int depth;
	string inputEncoding;
	bool hasChild;
	bool hasSibling;
	bool error;
	bool Error()
	{//This function is used to check if there was an error in reading in the XML document
		if (error)
			return true;
		if (hasChild)
			return Child->Error();
		if (hasSibling)
			return Sibling->Error();
		return false;
	}
	void AddSibling(string tag, StackType<string> &headers, ifstream &infile)
	{//This function checks if a sibling already exists before attempting to add a new sibling
		if (!hasSibling)
		{
			hasSibling = true;
			Sibling = new Node(tag, headers, infile);
		}
		else
			Sibling->AddSibling(tag, headers, infile);
	}
	void AddChild(string tag, StackType<string> &headers, ifstream &infile)
	{//This function checks if a child already exists before attempting to add a new child
		if (!hasChild)
		{
			hasChild = true;
			Child = new Node(tag, headers, infile);
		}
		else
			Child->AddSibling(tag, headers, infile);
	}
	void PrettyPrint(ofstream &outfile)
	{//This function writes out the XML code in a pretty print format.
		if (nodeType == element || nodeType == attribute || nodeType == text || nodeType == commentnode || nodeType == document)
		{
			for (int i = 0; i < depth; i++)
				outfile << "  ";
			outfile << nodeName << endl;
			if (hasChild || hasSibling)
			{
				if (hasChild)
				{
					Child->PrettyPrint(outfile);
				}
			}
			else if (data != "")
				for (int i = 0; i < depth-1; i++)
				outfile << "  ";
				outfile << "  " << data << endl;

			if (TagType(nodeName) != nottag && TagType(nodeName) != comment)
			{
			string temp = nodeName.substr(1, nodeName.length()-1);
			temp = "</" + temp;
			for (int i = 0; i < depth; i++)
				outfile << "  ";
			outfile << temp << endl;
			if (hasSibling)
				Sibling->PrettyPrint(outfile);
			}
			else if (TagType(nodeName) == nottag || TagType(nodeName) == comment)
			{
				if (hasSibling)
					Sibling->PrettyPrint(outfile);
			}
		}
		else
		{
		}
	}
	void TreePrint(ofstream &outfile)
	{//This function writes out the XML code in a debugging format.
		if (nodeType > -1)
		{
			outfile << "Node Type is " << nodeType << " ";
			if (nodeName != "")
				outfile << "Node Name is " << nodeName << " ";
			if (nodeValue != "")
				outfile << "Node Value is " << nodeValue << " ";
			if (hasChild)
				outfile << "Child address is " << Child << " ";
			if (hasSibling)
				outfile << "Sibling address is " << Sibling << " ";
			if (data != "")
				outfile << "Data is " << data << " ";

			outfile << endl;
		}
		if (hasChild)
		{
			outfile << "Going to Child of " << nodeName << endl;
			Child->TreePrint(outfile);
		}
		if (hasSibling)
		{
			outfile << "Going to Sibling of " << nodeName << endl;
			Sibling->TreePrint(outfile);
		}
	}
};
void main()
{
	do
	{
		StackType<string> headers;
		string file = GetName();
		ifstream infile(file + ".xml");
		Node XMLcode(file, readIn(infile), infile);
		if (!XMLcode.Error())
		{
			ofstream debug(file + "_tree.txt");
			ofstream pretty(file + "_xml.txt");
			XMLcode.PrettyPrint(pretty);
			XMLcode.TreePrint(debug);
		}
		else
			cout << "Error in the XML code." << endl;
	}
	while (KeepChecking());
}