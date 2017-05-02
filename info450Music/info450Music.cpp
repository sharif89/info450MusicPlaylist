#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;

class node
{
	string data;
	node *next;
public:
	node(string x);
	friend class linkedList;
};

node::node(string x)
{
	data = x;
	next = NULL;
}


class linkedList
{
	node *head;
	node *tail;
public:
	linkedList();
	int OpenMusicList(string filename);
	int SaveMusicList(string filename);
	void addNodeToEnd(node *nptr);
	void addNodeToHead(node *nptr);
	int insertAfter(node *ptr, string i);
	int removeNode(string i);
	void showList();
	node * findItem(string i);
};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}

int linkedList::OpenMusicList(string filename)
{
	int count = 0;
	string songName;
	ifstream infile(filename, ios::in);

	if (!infile)
	{
		cout << "Error: Could not read file" << endl;
		return READERROR;
	}

	while (!infile.eof())
	{
		getline(infile, songName);
		if (!songName.empty()) {
			if (count == 0)
			{
				node *newnode = new node(songName);
				count++;
			}

			addNodeToEnd(new node(songName));
			count++;
		}
	}
	infile.close();
	return 0;
}

int linkedList::SaveMusicList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (!output)
	{
		cout << "file could not be written" << endl;
		return WRITEERROR;
	}
	if (output)
	{
		node *ptr;
		ptr = head;
		while (ptr != NULL)
		{
			output << ptr->data << endl;
			ptr = ptr->next;
		}
	}
	output.close();
	return 0;
}

void linkedList::showList()
{
	node *ptr;
	ptr = head;
	char answer;
	if (ptr == NULL)
	{
		cout << "no items exist on this list " << endl;
		return;
	}

	while (ptr != NULL)
	{
		cout << "Next Song in Queue:" << ptr->data << endl;
		cout << "(P)lay, (S)kip, (A)dd, (D)elete, (Q)uit" << endl;
		cin >> answer;
		if (answer == 'p' || answer == 'P')
		{
			cout << "Currently Playing: " << ptr->data << endl;
			ptr = ptr->next;

		}
		else if (answer == 's' || answer == 'S')
		{
			int skipNumber;
			cout << "How many songs would you like to skip?" << endl;
			cin >> skipNumber;
			for (int i = 0; i < skipNumber; i++)
			{
				if (ptr == NULL)
				{
					ptr = head;
				}
				cout << "Skipping: " << ptr->data << endl;
				ptr = ptr->next;


			}
		}

		else if (answer == 'a' || answer == 'A')
		{
			cin.ignore();
			cin.clear();
			string songTitle;
			cout << "Enter name of artist and the song (example: Kid Cudi, The Guide):" << endl;
			getline(cin, songTitle);
			insertAfter(new node(songTitle), ptr->data);
			cout << "Song has been added to list for your listening..." << endl;
		}

		else if (answer == 'd' || answer == 'D')
		{
			string deletenode = ptr->data;
			ptr = ptr->next;
			removeNode(deletenode);


		}
		else
		{
			return;
		}
	}
	if (ptr == NULL)
	{
		ptr = head;
		showList();
	}
}

void linkedList::addNodeToEnd(node *ptr)
{

	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void linkedList::addNodeToHead(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

int linkedList::insertAfter(node *newnode, string i)
{
	node *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i)
		{
			newnode->next = ptr->next;
			ptr->next = newnode;
			if (tail == ptr)
				tail = newnode;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

node * linkedList::findItem(string i)
{
	node *ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i)
		{

			return ptr;
		}
		ptr = ptr->next;
	}

	cout << "Song was not found in list" << endl;
	return NULL;
}


int linkedList::removeNode(string i)
{
	node *ptr = head;
	if (ptr == NULL)
		return -1;


	if (head->data == i)
	{

		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (ptr->next)->data == i)
		{
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

int main()
{
	string musicPlaylist;
	linkedList *mylist = new linkedList();


	cout << "Thanks for using Sharif's Music player" << endl;
	cout << "Please enter a valid filepath to a music playlist contained" << endl;
	cout << "on a text file. Enjoy the tunes!" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	cout << "Enter filepath here: " << endl;
	getline(cin, musicPlaylist);
	mylist->OpenMusicList(musicPlaylist);
	mylist->showList();
	mylist->SaveMusicList(musicPlaylist);

	return 0;
}