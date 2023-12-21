#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;
// ___________________________________________________________________________________________________________________________________
#define ll long long
#define advance hk = (hk+1) % nearestPrime
struct element{
    std::string id;
    long double elementscore;
};
class mapper{
public:
    std::vector<element> storage;
    ll toBeSize = 900013;
    ll nearestPrime = 900007;
    ll numberOfelements = 0;
    void createelement(std::string id, long double count){
        initialize();
        if(storage.size() == 0){
            storage.resize(toBeSize);
            element dummy;dummy.id = "-1";dummy.elementscore = -1;
            for(ll i = 0;i<toBeSize;i++){
                storage[i] = dummy;
            }
        }
        ll hk = hash(id);// hashkey
        element person;person.elementscore = count;person.id = id;
        while (storage[hk].elementscore != -1){
            advance;
        }
        storage[hk] = person;
        numberOfelements++;
    };
    std::vector<ll> getTopK(ll k){
        initialize();
        ll array[numberOfelements];
        std::vector<ll> result;
        ll i = 0;
        ll j = 0;

        while(i<numberOfelements){
            if(storage[j].elementscore>=0){
                array[i] = storage[j].elementscore;i++;
            }
            j++;
        }
        sorter(array,0,numberOfelements-1);
        for(ll i = 0;i<std::min(k,numberOfelements);i++){
            result.push_back(array[numberOfelements-1-i]);
        }
        return result;
        return std::vector<ll>(); // Placeholder return value
    };
    ll getelement(std::string id){
        initialize();
        ll hk = hash(id);
        while(storage[hk].elementscore != -1){
            if(storage[hk].id == id){
                return storage[hk].elementscore;
            }
            advance;
        }
        return 0;
    };
    void addScore(std::string id, double count){
        initialize();
        ll hk = hash(id);
        while(storage[hk].elementscore != -1){
            if(storage[hk].id == id){
                storage[hk].elementscore += count;
                return;
            }
            advance;
        }
        element person;person.elementscore = count;person.id = id;
        storage[hk] = person;
        numberOfelements++;
    };
    bool doesExist(std::string id){
        initialize();
        ll hk = hash(id);
        while(storage[hk].elementscore != -1){
            if(storage[hk].id == id){
                return true;
            }
            advance;
        }
        return false; // Placeholder return value
    };
    bool deleteelement(std::string id){
        initialize();
        ll hk = hash(id);
        while(storage[hk].elementscore != -1){
            if(storage[hk].id == id){
                storage[hk].id = "-2";
                storage[hk].elementscore = -2;
                numberOfelements--;
                return true;
            }
            advance;
        }
        return false; // Placeholder return value
    };
    ll databaseSize(){
        initialize();
        return numberOfelements; // Placeholder return value
    };
    ll hash(std::string id){
        initialize();
        long long hk = 0;
        for(ll i = 0;i<id.length();i++){
            long long value = id[i];
            long long value2 = id[id.length()-1-i];
            hk += (value*1069)^(hk*13)^(value2*143);
            hk %= nearestPrime;
        }
        // cout<<hk<<endl;
        return (hk % nearestPrime); // Placeholder return value
    };
    void sorter(ll array[],ll start,ll end){
        if(end-start <= 0){
            return;
        }
        else{
            ll res[end-start+1];
            ll mid = (end + start)/2;
            sorter(array,start,mid);
            sorter(array,mid+1,end);
            ll i = start,j= mid +1;ll k = 0;
            while(i<mid+1 && j<end+1){
                if(array[i]>array[j]){res[k] = array[j];j++;k++;}
                else{res[k] = array[i];i++;k++;}
            }
            while(i<mid+1){res[k] = array[i];i++;k++;}
            while(j<end+1){res[k] = array[j];j++;k++;}
            for(ll ii = start;ii<end+1;ii++){
                array[ii] = res[ii-start];
            }
        }
    }
    void initialize(){
        if(storage.size() == 0){
            storage.resize(toBeSize);
            element dummy;dummy.id = "-1";dummy.elementscore = -1;
            for(ll i = 0;i<toBeSize;i++){
                storage[i] = dummy;
            }
        }
    }
};
// ____________________________________________________________________________________________________________________________
class heapnode{
    public : 
    string index;
    double score;
};
class maxheap{
    public : 
        heapnode* data;
        int size = 0;
        void hup(int index){
            while(index > 0){
                int pindex = (index - 1)/2;
                if(data[pindex].score > data[index].score){
                    heapnode temp = data[pindex];data[pindex] = data[index];data[index] = temp;
                    index = pindex;
                }
                else break;
            }
            // cout<<"current top is : "<<data[0].id<<endl;
        }
        void hdown(int index){
            int smallest = index;
            int lc = 2*index + 1;
            int rc = 2*index + 2;
            if(lc < size && data[smallest].score > data[lc].score){smallest = lc;}
            if(rc < size && data[smallest].score > data[rc].score){smallest = rc;}
            if(smallest != index){
                heapnode temp = data[smallest]; data[smallest] = data[index]; data[index] = temp;
                hdown(smallest);
            }
        }
        void insert(string idd,double ct,int k){
            // cout<<"Inserting id : "<<idd<<" "<<ct<<endl;
            if(size < k){
                data[size].score = ct;
                data[size].index = idd;
                hup(size);
                size++;
            }
            else{
                if(data[0].score > ct){
                    //do not insert
                }
                else {
                    data[0].score = ct;
                    data[0].index = idd;
                    hdown(0);
                }
            }
        }
        heapnode getmin(){
            // cout<<"Returning result : "<<data[0].id<<" with count "<<data[0].count<<endl;
            heapnode result = data[0];
            data[0] = data[size-1];
            size--;
            hdown(0);
            return result;
        }
};
class QNA_tool {

private:

    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user

    // You can add attributes/helper functions here

public:
    SearchEngine mainengine;
    Dict dict;
    maxheap* mainHeap;
    mapper map;
    mapper csv;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
};