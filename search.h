// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine 
{
private:
    vector<pair<string,vector<int>>> *SentenceStorage=new vector<pair<string,vector<int>>>;
    vector<int> Zvalues;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};