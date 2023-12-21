// Do NOT add any other includes
#include "dict.h"
string separators = " .,-:!\"\'()?—[]“”‘’˙;@";
Dict::Dict(){
    mytrie.root = new trieNode;
}
void destroyTrie(trieNode* node) {
    if (node) {
        for (int i = 0; i < 128; i++) {
            if (node->children[i] != NULL) {
                destroyTrie(node->children[i]);
                node->children[i]=NULL;
            }
        }
        // delete node;
    }
}
Dict::~Dict(){
    destroyTrie(this->mytrie.root);
}
void Dict::insert_sentence(ll book_code, ll page, ll paragraph, ll sentence_no, string sentence){
    string current;
    for (ll i = 0;i<sentence.size();i++){
        for (ll j = 0;j<separators.size();j++){
            if (sentence[i] == separators[j]){
                if(current != ""){
                    mytrie.insert(current);
                }
                current = "";
                goto loopend;
            }
        }
        if(sentence[i] >= 'A' && sentence[i]<='Z'){
            sentence[i]+=32;
        }
        current = current + sentence[i];
        if(i == sentence.length()-1){
            mytrie.insert(current);
            current = "";
        }
        loopend:;
    }
    return;
}
ll Dict::get_word_count(string word){
    ll answer = mytrie.search(word);
    // cout<<"answer is : "<<answer<<endl;
    return answer;
}


void dump(trieNode* node,string current,vector<string>& ans){ 
    if(node->eow){
        string a = current + ", " + to_string(node->count) + "\n";
        ans.push_back(a);
    }
    for(int i = 0;i<128;i++){
        if(node->children[i]){
            char temp = (char)i;
            current.push_back(temp);
            dump(node->children[i],current,ans);
            current.pop_back();
        }
    }
}
void Dict::dump_dictionary(string filename){
    // cout<<"dumping dictionary ..."<<endl;
    vector<string> ans;
    string current = "";
    dump(mytrie.root,current,ans);
    std::ofstream outputFile(filename);
    for(int i = 0;i<ans.size();i++){
        outputFile<<ans[i];
    }
    outputFile.close();
    return;
}