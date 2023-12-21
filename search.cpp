// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine()
{
      
}

SearchEngine::~SearchEngine()
{
    delete SentenceStorage;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    vector<int> store;
    store.push_back(book_code);
    store.push_back(page);
    store.push_back(paragraph);
    store.push_back(sentence_no);
    pair<string,vector<int>> storage;
    for(int i=0;i<sentence.size();i++)
    {
        if(int(sentence[i])>64 && int(sentence[i])<91)
        {
            sentence[i]=int(sentence[i])+32;
        }
        else
        {
            continue;
        }
    }
    storage.first=sentence;
    storage.second=store;
    SentenceStorage->push_back(storage);
    return;
}
void getZvalues(string s,vector<int>& z)
{
    for(int i=0;i<s.size();i++)
    {
        if(int(s[i])>64 && int(s[i])<91)
        {
            s[i]=int(s[i])+32;
        }
        else
        {
            continue;
        }
    }
    int n = s.length();
    z.resize(n);
	int Left;
    int Right;
    int kValue;
    //initial condition
    Left=Right=0;
    for(int i=0;i<n;i++)
    {
        if(i>Right)
        {
            Left=Right=i;
            while (Right<n && s[Right-Left] == s[Right])
            {
                Right++;
            }
			z[i]=Right-Left;
			Right--;
        }
        else
        {
            kValue = i-Left;
            if(z[kValue] < Right-i+1)
            {
                z[i]=z[kValue];
            }
            else 
            {
                Left = i;
				while (Right<n && s[Right-Left] == s[Right])
                {
                    Right++;
                }
				z[i] = Right-Left;
				Right--;
            }
            

        }
    }
}
Node* SearchEngine::search(string pattern, int& n_matches)
{
    for(int i=0;i<pattern.size();i++)
    {
        if(int(pattern[i])>64 && int(pattern[i])<91)
        {
            pattern[i]=int(pattern[i])+32;
        }
        else
        {
            continue;
        }
    }
    Node* head=new Node();
    Node* temp=head;
    for(int i=0;i<SentenceStorage->size();i++)
    {
        Zvalues.clear();
        string h=pattern+"€"+(*SentenceStorage)[i].first;
        int l=h.length();
        getZvalues(h,Zvalues);
        for(int j=pattern.length()+3;j<l;j++)
        {
            if(Zvalues[j]==pattern.length() && n_matches!=0)
            {
                Node* value=new Node();
                value->book_code=(*SentenceStorage)[i].second[0];
                value->page=(*SentenceStorage)[i].second[1];
                value->paragraph=(*SentenceStorage)[i].second[2];
                value->sentence_no=(*SentenceStorage)[i].second[3];
                value->offset=j - pattern.length() -3;
                temp->right=value;
                value->left=temp;
                n_matches++;
                temp=value;
            }
            else if(Zvalues[j]==pattern.length() && n_matches==0)
            {
                temp->book_code=(*SentenceStorage)[i].second[0];
                temp->page=(*SentenceStorage)[i].second[1];
                temp->paragraph=(*SentenceStorage)[i].second[2];
                temp->sentence_no=(*SentenceStorage)[i].second[3];
                temp->offset=j - pattern.length() -3;
                n_matches++;
                
            }
            else 
            {
                continue;
            }
        }

    }
    return head;

}