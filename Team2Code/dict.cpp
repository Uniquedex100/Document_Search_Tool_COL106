// Do NOT add any other includes
#include "dict.h"

DictNode::DictNode(){}

DictNode::~DictNode(){
    children.clear();
}

Dict::Dict(){
    // Implement your function here
    root = new DictNode();  
}

Dict::~Dict(){
    delete root;
    // Implement your function here    
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string separators = ".,-:!\"\'()?[];@";
    separators+=" ";
    // Implement your function here
    int i = 0;
    DictNode* current = root;
    while(i<sentence.size()){
        int a = sentence[i];
        size_t found = separators.find(sentence[i]);
        if (found!=string::npos) {
            size_t finds = separators.find(sentence[i-1]);
            if (finds!=string::npos) i++;
            else {
                if (i!=0){
                    current->word_count++;
                    current=root;
                    i++;
                }
                else {i++;}
            }
        }
        else{
            char temp=sentence[i];
            if(a>64 && a<91){
                temp = a+32;
            }
            int h = 0;
            string r = "";
            while(h<current->children.size()){
                if (current->children[h].first==temp){
                    current=current->children[h].second;
                    r="l";
                    break;
                }
                else h++;
            }
            if(r==""){
                pair<char,DictNode*> en;
                en.first = temp;
                en.second = new DictNode();
                current->children.push_back(en);
                current=current->children.back().second;
            }
            if (i+1==sentence.size()) current->word_count++;
            i++;
        }
    }
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here 
    int i = 0;
    DictNode* current = root;
    while(i<word.size()){
        int a = word[i];
        char temp = word[i];
        if(a>64 && a<91) {
            temp=a+32;
        }
        int d=0;
        string y ="";
        while(d<current->children.size()){
            if (current->children[d].first==temp){
                current=current->children[d].second;
                y="l";
                break;
            }
            else d++;
        }
        if (y=="") return 0;
        else i++;
    }
    return current->word_count;
}

vector<pair<string,int>> Dict::traversal(DictNode* node,vector<pair<string,int>>& sd,string& k){
    if (node==nullptr) return sd;
    if (node->children.size()==0){
        pair<string,int> l;
        l.first=k;
        l.second=node->word_count;
        sd.push_back(l);
        k.pop_back();
        return sd;
    }
    for(int f=0;f<node->children.size();f++){
        traversal(node->children[f].second,sd,k+=node->children[f].first);
    }
    if (node->word_count>0) {
        pair<string,int> l;
        l.first=k;
        l.second=node->word_count;
        sd.push_back(l);
    }
    k.pop_back();
    return sd;
}

void Dict::dump_dictionary(string filename){
    vector<pair<string,int>> d;
    string h="";
    vector<pair<string,int>> output = Dict::traversal(root,d,h);
    ofstream MyFile(filename);
    for (int e = 0;e<output.size();e++){
        string line=output[e].first+","+" "+std::to_string(output[e].second);
        MyFile<<line<<endl;
        line="";
    }
    MyFile.close();
    return;
}

// int main(){
//     Dict a;
//     a.insert_sentence(1,1,1,1,"I am a girl.");
//     a.insert_sentence(1,1,1,2,"I am a normal GIrL.");
//     cout<<a.get_word_count("girl")<<endl;
//     vector<pair<string,int>> d;
//     string h="";
//     vector<pair<string,int>> output=a.traversal(a.root,d,h);
//     for(int f = 0;f<output.size();f++){
//         string line=output[f].first+","+" "+std::to_string(output[f].second);
//         cout<<line<<endl;
//     }
//     //a.dump_dictionary("result.txt");
// }