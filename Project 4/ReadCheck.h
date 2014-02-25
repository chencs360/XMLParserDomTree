#include <fstream>
#include <string>
#include <sstream>
#include "stack.h"

using namespace std;

enum { open = 1, close, selfclose, comment, vers, nottag };
enum { element=1, attribute, text, commentnode=8, document=9 };
string readIn(ifstream &infile)
{//This function will parse the actual XML file, and return either a tag
	//or a piece of data that needs placed into the tree
	bool openCheck = false, stringLitCheck = false, end = false;
	infile.unsetf(ios_base::skipws);
	char temp;
	string line = "";

	infile >> temp;
	while (temp == ' ' || temp == '\n')
	{
		if (infile.eof())
			return 0;
		else
			infile >> temp;
	}
	line += temp;
	if (temp == '<')
	{
		while (!end)
		{
			infile >> temp;
			if (temp == '>' && !stringLitCheck)
			{
				end = true;
			}
			if (temp == '"') //checks for a string literal and flips the flag for entering or exiting
			{
				if (stringLitCheck)
					stringLitCheck = false;
				else if (!stringLitCheck)
					stringLitCheck = true;
			}
			if (temp == '<' && !stringLitCheck)
			{
				if (openCheck)
				{
					cout << "Error with a tag" << endl;
				}
				openCheck = true;
			}
			line += temp;
		}
		return line;
	}
	else if (temp == '>' && !end)
		cout << "Error with syntax" << endl;
	else if (temp >= 'a' && temp <='z' || temp >= 'A' && temp <= 'Z')
	{
		while (temp != '<')
		{
			infile >> temp;
			if (temp == '>')
				cout << "Error with syntax" << endl;
			line += temp;
		}
		int pos = infile.tellg();
		infile.seekg(pos-1);
		line = line.substr(0, line.length()-1);
		return line;
	}
	if (!infile.eof())
		return readIn(infile);
	else
		return "";
}
string GetName()//gets filename of file to be checked, so user can check multiple files
{
	string name = "";
	do
	{
	cout << "Please enter the name of the xml file you wish to parse.  Please ensure that thefile is in the same folder as this program, and that you do not add the .xml\nextension at the end of the name.\n";
	cin >> name;
	}
	while (name == "");
	return name;
}
int TagType(string tag)
{//returns the type of tag the user has, in order to work on the tag in other functions
	if (tag.substr(0, 2) == "</" && tag.substr(tag.length()-1, 1) == ">")
		return close;
	else if (tag.substr(0, 1) == "<" && tag.substr(tag.length()-2, 2) == "/>")
		return selfclose;
	else if (tag.substr(0, 4) == "<!--" && tag.substr(tag.length()-3, 3) == "-->")
		return comment;
	else if (tag.substr(0, 2) == "<?" && tag.substr(tag.length()-2, 2) == "?>")
		return vers;
	else if (tag.substr(0, 1) == "<" && tag.substr(tag.length()-1, 1) == ">")
		return open;
	else
		return nottag;
}