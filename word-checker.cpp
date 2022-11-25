#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
#define MAX 50
//#include <stdio.h>
//#include <math.h>
//#include <vector>
//#include <stdlib.h>
using namespace std;
using namespace std::chrono;

/////////////////////////// TRIE /////////////////////////////////////////
class Trie {
public:
	class node {
	public:
		bool end;
		node* next[26];
		node() {
			end = false;
			for (int i = 0; i < 26; i++) {
				next[i] = NULL;
			}
		}
	};
	node* trie;
	Trie() {
		trie = new node();
	}
	void insertBT(string word) {
		int i = 0;
		node* it = trie;
		while (i < word.size()) {
			if (it->next[word[i] - 'a'] == NULL)
				it->next[word[i] - 'a'] = new node();
			it = it->next[word[i] - 'a'];
			i++;
		}
		it->end = true;

	}

	bool search(string word) {
		int i = 0;
		node* it = trie;
		while (i < word.size()) {
			if (it->next[word[i] - 'a'] == NULL)
				return false;
			it = it->next[word[i] - 'a'];
			i++;
		}
		return it->end;
	}
};

//////////////////////////////// END TRIE TREE ///////////////////////////////////////



///////////////////////// TERNARY TREE  //////////////////////////////////////

/*
 * Node Declaration
 */
struct Node
{
	char data;
	unsigned isEndOfString : 1;
	Node* left, * eq, * right;
};
/*
 * create a new ternary search tree node
 */
Node* newNode(char data)
{
	Node* temp = new Node;
	temp->data = data;
	temp->isEndOfString = 0;
	temp->left = temp->eq = temp->right = NULL;
	return temp;
}
/*
 * insert a new word in a Ternary Search Tree
 */
void insert(Node** root, const char* word)
{
	if (!(*root))
		*root = newNode(*word);
	if ((*word) < (*root)->data)
		insert(&((*root)->left), word);
	else if ((*word) > (*root)->data)
		insert(&((*root)->right), word);
	else
	{
		if (*(word + 1))
			insert(&((*root)->eq), word + 1);
		else
			(*root)->isEndOfString = 1;
	}
}
/*
 * traverse Utility function
 */
void traverseTSTUtil(Node* root, char* buffer, int depth)
{
	if (root)
	{
		traverseTSTUtil(root->left, buffer, depth);
		buffer[depth] = root->data;
		if (root->isEndOfString)
		{
			buffer[depth + 1] = '\0';
			cout << buffer << endl;
		}
		traverseTSTUtil(root->eq, buffer, depth + 1);
		traverseTSTUtil(root->right, buffer, depth);
	}
}
/*
 * traverse Ternary Search Tree
 */
void traverseTST(Node* root)
{
	char buffer[MAX];
	traverseTSTUtil(root, buffer, 0);
}
/*
 * search a given word in Ternary Search Tree
 */
int searchTST(Node* root, char* word)
{
	if (!root)
		return 0;
	if (*word < (root)->data)
		return searchTST(root->left, word);
	else if (*word > (root)->data)
		return searchTST(root->right, word);
	else
	{
		if (*(word + 1) == '\0')
			return root->isEndOfString;
		return searchTST(root->eq, word + 1);
	}
}
/////////////////// END TERNARY TREE /////////////////////////



int main() {


	string word;
	string file;
	char flag = 'Y';
	Trie* myTrie = new Trie();

	/// 
	Node* root = NULL;
	//char s[100];
	char myline_char[100];

	bool tree;


	//vector<string> words = { "jahanzaib", "zarak", "mohammed", "moha", "jahan"}; 
	cout << "\t\t\t\t\tWELCOME TO THE WORLD OF WORD CHECKER\n";
	cout << "\tIn this world you can search any word (comprising of 6 aplhabets exactly) from the given files below\n\n";

	cout << "Please select a textfile from which you want to search the word\n\n The names of given files are:\n\n1000.txt,\n10000.txt,\n100000.txt,\n1000000.txt,\n10000000.txt,\n100000000.txt,\n";
	cout << "\nWrite the file name here (Count the zeros carefully you might have one extra) > ";
	cin >> file;
	cout << "\n\t\t\t\tSelected file is:" << file << "\n\n\n";
	cout << "Now......\nSelect which solution to consider ? \n \t\t\t\t TRIE DS or TERNARY SEARCH TREE\n\n Please enter 1 for TRIE DS and 0 for TERNARY SEARCH TREE :> ";
	cin >> tree;


	ifstream myfile;
	myfile.open(file);
	string myline;

	if (myfile.is_open())
	{
		cout << "Generating a Search Tree, Please Wait...\n";
		// while 1
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		while (myfile)
		{
			// equivalent to myfile.good()

			getline(myfile, myline);
			if (tree == 1)
			{

				myTrie->insertBT(myline);

			}
			else if (tree == 0)
			{


				strcpy_s(myline_char, myline.c_str());
				insert(&root, myline_char);

			}
			else
			{
				cout << "Wrong input\n";
			}

		}
		// Get ending timepoint
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		cout << "Search Tree Generation Complete\n";
		cout << "Time taken for generating search tree and reading file: " << time_span.count() << " seconds\n\n" << endl;


		//while 2
		while (flag == 'Y' || flag == 'y')
		{
			cout << "Type the word to be searched: ";
			cin >> word; // get user input from the keyboard
			if (tree == 1) {

				// Get starting timepoint
				auto start = high_resolution_clock::now();
				if (myTrie->search(word))
				{

					cout << "Word '" << word << "' exists in the data file.\n";
				}
				else
				{
					cout << "Word '" << word << "' does not exist in the data file.\n";
				}
				// Get ending timepoint
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);

				cout << "Time taken to search the word: " << duration.count() << " microseconds" << endl;

				cout << "To continue searching type 'Y' else press any key and hit enter: ";
				cin >> flag;
				cout << '\n';
			}

			if (tree == 0)
			{
				strcpy_s(myline_char, word.c_str());
				// Get starting timepoint
				auto start = high_resolution_clock::now();

				//strcpy_s(myline_char, word.c_str());
				if (searchTST(root, myline_char)) {
					cout << "Word '" << myline_char << "' exists in the data file.\n";
				}
				else {
					cout << "Word '" << myline_char << "' does not exist in the data file.\n";
				}
				// Get ending timepoint
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);

				cout << "Time taken to search the word: " << duration.count() << " microseconds" << endl;
				cout << "To continue searching type 'Y' else press any key and hit enter: ";
				cin >> flag;
				cout << '\n';
			}
		}
	}
	else
	{
		cout << "Couldn't open file\n";
	}

	return 0;
}









// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
