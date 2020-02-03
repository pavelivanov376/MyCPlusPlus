#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void myCopy(string text, int firstIndex, int lastIndex, vector<string> *clipboard);
void myPaste(string& text, int indexOfWord, int indexToPlace, vector<string>* clipboard);
int main()
{
	ifstream inputData("Input.txt");
	string text="this is a sample text which should conatain words with capital letters";
	string& changedText = text;
	getline(inputData, text);
	vector<string> clipboard;
	vector<string> *myClipboard=&clipboard;
	string command;
	int firstParam = 0;
	int secondParam = 0;
	while (command != "stop")
	{
		cout << "Enter a command:\n";
		cin >> command;
		if (command=="copy")
		{
			cout << "Enter from where to where you want to copy:\n";
			cin >> firstParam;
			cin >> secondParam;
			myCopy(text, firstParam, secondParam, myClipboard);
			cout << "Words in the clipboard: ";
			for (int i = 0; i < clipboard.size(); i++)
			{
				cout << clipboard[i] << ' ';
			}
			cout << endl;
		}
		else if (command == "paste")
		{
			cout << "Enter the index of the word and where to paste it:\n";
			cin >> firstParam;
			cin >> secondParam;
			myPaste(changedText, firstParam, secondParam, myClipboard);
			cout << "The text is: \n";
			cout << text;
		}
		else
		{
			cout << "Worng command!";
		}
		cout << endl;
	}

	delete[] myClipboard;
	return 0;
}
void myCopy(string text, int firstIndex, int lastIndex, vector<string>* clipboard)
{
	while (isalpha(text[firstIndex])&&firstIndex>0)
	{
		firstIndex--;
	}
	while (isalpha(text[lastIndex])&&lastIndex<text.size()-1)
	{
		lastIndex++;
	}
	string copiedText = text.substr(firstIndex, lastIndex - firstIndex + 1);
	stringstream copiedTextStream(copiedText);
	int wordCounter = 0;
	int n = copiedText.size();
	for (int i = 1; i < n; i++)
	{
		char first = copiedText[i - 1];
		char second = copiedText[i];
		if (first ==' ' && isalpha(second))
		{
			wordCounter++;
		}
	}
	
	string currWord;
	
	for (int i = 0; i < wordCounter; i++)
	{
		copiedTextStream >> currWord;
		clipboard->push_back(currWord);
	}
	
}
void myPaste(string &text, int indexOfWord,int indexToPlace, vector<string>* clipboard)
{
	string changed = text;
	string word = clipboard->at(indexOfWord);
	changed.insert(indexToPlace,word);
	text = changed;
}
