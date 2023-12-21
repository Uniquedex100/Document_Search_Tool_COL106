#include <assert.h>
#include <sstream>
#include "qna_tool.h"



using namespace std;
QNA_tool::QNA_tool(){
    // cout<<"Kuchh hua"<<endl;
    fstream fin; 
    fin.open("unigram_freq.csv", ios::in);   
    // cout<<1<<endl;
    vector<string> row; 
    string line, word, temp; 
    // cout<<1<<endl;
    int tts = 0;
    while (getline(fin, line)) { 
        if (tts == 0){tts = 1;continue;}
        row.clear();
        stringstream s(line); 
        // cout<<6<<endl;
        while (getline(s, word, ',')) { 
            row.push_back(word); 
        } 
        // cout<<row[0]<<" "<<row[1]<<endl;
        csv.createelement(row[0],stoll(row[1]));
    } 
    // for (int i=0; i<2; i++){
        // cout << csv.storage[i].id << endl;
    // }
}
QNA_tool::~QNA_tool(){}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // cout<<"insert called"<<endl;
    mainengine.insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    // cout<<"main engine inserted"<<endl;
    dict.insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    // cout<<"dict inserted"<<endl;
    return;
}


Node* QNA_tool::get_top_k_para(string question, int k) {
    mainHeap = new maxheap;
    mainHeap->data = new heapnode[k+1];
    string separators = " .,-:!\"\'()?[];@";
    string current = "";
    for(int i = 0;i<question.size();i++){// For every word...
        if(question[i] >= 'A' && question[i]<='Z'){
            question[i]+=32;
        }
        int nmatches = 0;
        for(int j = 0;j<separators.size();j++){
            if(question[i] == separators[j]){
                if(current == ""){continue;}
                
                Node* first =  mainengine.search(current,nmatches);
                // cout << first->book_code << endl;
                while(first != nullptr){
                    double score = double(dict.get_word_count(current)+1)/double(csv.getelement(current)+1);
                    // cout<<"score is : "<<score<<endl;
                    string encoded_para;
                    encoded_para += to_string(first->book_code) + '_';
                    encoded_para += to_string(first->page) + '_';
                    encoded_para += to_string(first->paragraph) + '_';
                    map.addScore(encoded_para,score);
                    first = first->right;
                }
                current = "";
                goto nextchar;
            }
        }
        current = current + question[i];
        nextchar:;
    }
    cout<<"Map insertion complete"<<endl;
    for(int i = 0;i<map.toBeSize;i++){
        if(map.storage[i].elementscore != -1){
            mainHeap->insert(map.storage[i].id,map.storage[i].elementscore,k);
        }
    }
    cout<<"Maxheap insertion complete"<<endl;

    Node* prev = nullptr;
    for(int i = 0;i<k;i++){
        Node* temp = new Node;
        heapnode hn = mainHeap->getmin();
        string s = hn.index;
        int bc;
        int pg;
        int par;
        double sc;
        int j = 0;
        string current = "";
        for(int i = 0;i<s.size();i++){        
            if(s[i] == '_'){
                cout<<current<<endl;
                if(j == 0){bc = stoi(current);j++;}
                else if(j == 1){pg = stoi(current);j++;}
                else if(j == 2){par = stoi(current);j++;}
                current = "";
                goto ends;
            }
            current += s[i];
            ends:;
        }
        // temp->score = hn.score;
        // cout<<temp->score<<"harami"<<endl;
        temp->book_code = bc;
        temp->page = pg;
        temp->paragraph = par;
        temp->right = prev;
        prev = temp;
    }
    cout<<"everything complete"<<endl;
    Node* final = prev;
    while(prev != nullptr){
        cout.precision(20);
        // cout<<"Book_Code: "<<prev->book_code<<" Page: "<<prev->page<<" Paragraph: "<<prev->paragraph<<" Score: "<<prev->score<<endl;
        prev = prev->right;
    }
    return final;
}

void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: " << "Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}