// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class DictNode{
    public:
    int word_count = 0;
    vector <pair<char,DictNode*>> children;
    DictNode();
    ~DictNode();
};

class Dict {
private:
    DictNode* root;
    vector<pair<string,int>> traversal(DictNode* root,vector<pair<string,int>>& g,string& y);
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();
    
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);
    

    /* -----------------------------------------*/
};