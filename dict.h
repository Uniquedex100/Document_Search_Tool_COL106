// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#define ll int

class trieNode{
    public : 
        trieNode* children[128];
        bool eow;//end of word;
        int count = 0;
        trieNode(){
            eow = false;
            for(int i = 0;i<128;i++){
                children[i] = NULL;
            }
        }
};
class Trie {
public:
    trieNode* root;
    Trie() {
        root = new trieNode;
    }
    void insert(string word) {
        trieNode* current = root;
        for(int i = 0;i<word.size();i++){
            int index = word[i];
            if(current->children[index] == nullptr){
                current->children[index] = new trieNode;
            }
            current = current->children[index];
        }
        current->eow = true;
        current->count = current->count + 1;
        // cout<<"count of "<<word<<" is now "<<current->count<<endl;
    }
    int search(string word) {
        trieNode* current = root;
        for(int i = 0;i<word.size();i++){
            int index = word[i];
            if(current->children[index] == nullptr){return 0;}
            current = current->children[index];
        }
        // cout<<"So the count of "<<word<<" is "<<current->count<<endl;
        return (current->count);
    }
    bool startsWith(string prefix) {
        trieNode* current = root;
        for(int i = 0;i<prefix.size();i++){
            int index = prefix[i];
            if(current->children[index] == nullptr){return false;}
            current = current->children[index];
        }
        return true;
    }
};

class Dict {
private:
public: 
    Trie mytrie;
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();
    ~Dict();
    void insert_sentence(ll book_code, ll page, ll paragraph, ll sentence_no, string sentence);
    ll get_word_count(string word);
    void dump_dictionary(string filename);
    /* -----------------------------------------*/
};