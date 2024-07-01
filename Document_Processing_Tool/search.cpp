// Do NOT add any other includes
#include "search.h"

Sentence::Sentence(int _book_code, int _page, int _paragraph, int _sentence_no, string _sentence){
    book_code=_book_code;
    page=_page;
    paragraph=_paragraph;
    sentence_no=_sentence_no;
    sentence=_sentence;
}

std::vector<int> shift_array(string pattern){
    int pattern_length= pattern.length();
    vector<int> backtrack;
    backtrack.push_back(-1);
    int proper_pref_suff=0;
    for(int i=1; i<=pattern_length; i++){
        // cout<<"pattern[i] is "<<pattern[i]<<endl;
        // cout<<"proper_pref_suff is "<<proper_pref_suff<<endl;
        if(pattern[proper_pref_suff]==pattern[i-1]){
            proper_pref_suff+=1;
            if(i==1){
                proper_pref_suff-=1;
            }

            int to_be_pushed= proper_pref_suff;
            //
            if(i==pattern_length){
                backtrack.push_back(to_be_pushed);
                break;
            }
            if(pattern[proper_pref_suff]!=pattern[i]){

            }
            else{
                to_be_pushed-=1;
                int flag=1;
                while(flag==1){
                    flag=0;
                    for(int j=0; j<to_be_pushed; j++){
                        if(pattern[j]!=pattern[i-to_be_pushed+j]){
                            to_be_pushed-=1;
                            flag=1;
                            break;
                        }
                    }
                    if(pattern[to_be_pushed]==pattern[i] && flag==0){
                        to_be_pushed-=1;
                        flag=1;
                    }
                }
            }
            //some process
            backtrack.push_back(to_be_pushed);
        }
        else{

            int to_be_pushed= proper_pref_suff;
            proper_pref_suff=0;
            //

            //cout<<"deii "<<to_be_pushed<<endl;
            int flag=1;
            while(flag==1){
                flag=0;
                for(int j=0; j<to_be_pushed; j++){
                    if(pattern[j]!=pattern[i-to_be_pushed+j]){
                        to_be_pushed-=1;
                        flag=1;
                        break;
                    }
                }
                if(flag==0){
                    if(to_be_pushed>proper_pref_suff){
                        proper_pref_suff=to_be_pushed;
                    }
                }
                
                if(pattern[to_be_pushed]==pattern[i] && flag==0){
                    to_be_pushed-=1;
                    flag=1;
                }
            }
            //some process
            if(i==pattern_length){
                backtrack.push_back(proper_pref_suff);
                break;
            }
            backtrack.push_back(to_be_pushed);

        }
    }
    return backtrack;
}

SearchEngine::SearchEngine(){
}

SearchEngine::~SearchEngine(){
    for(int i=0;i<size;i++){
        delete sentences[i];
    }
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    Sentence* temp = new Sentence(book_code,page,paragraph,sentence_no,sentence);
    sentences.push_back(temp);
    size++;
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    std::vector<int> backtrack = shift_array(pattern);
    int pattern_len=pattern.size();
    Node* head = nullptr;
    Node* current_node=nullptr;
    for(int i=0;i<size;i++){
        Sentence* s=sentences[i];
        std::string current_sentence=s->sentence;
        int current_sentence_len=current_sentence.size();
        int sentence_index=0;
        int pattern_index=0;
        while(sentence_index<current_sentence_len){
            // std::cout<<"Hello\n";
            if(pattern_index<pattern_len && tolower(current_sentence[sentence_index])==tolower(pattern[pattern_index])){
                sentence_index++;
                pattern_index++;
            }
            else if(pattern_index==pattern_len){
                // std::cout<<"reached end\n";
                if(!head){
                    head = new Node(s->book_code,s->page,s->paragraph,s->sentence_no,sentence_index-pattern_len);
                    current_node=head;
                }
                else{
                    Node* temp = new Node(s->book_code,s->page,s->paragraph,s->sentence_no,sentence_index-pattern_len);
                    current_node->right=temp;
                    temp->left=current_node;
                    current_node=temp;
                }
                pattern_index=backtrack[pattern_index];
                n_matches++;
            }
            else{
                if(pattern_index==-1){
                    sentence_index++;
                    pattern_index=0;
                }
                else{
                    pattern_index=backtrack[pattern_index];
                }
            }
        }
        if(pattern_index==pattern_len){
            // std::cout<<"reached end\n";
            if(!head){
                head = new Node(s->book_code,s->page,s->paragraph,s->sentence_no,sentence_index-pattern_len);
                current_node=head;
            }
            else{
                Node* temp = new Node(s->book_code,s->page,s->paragraph,s->sentence_no,sentence_index-pattern_len);
                current_node->right=temp;
                temp->left=current_node;
                current_node=temp;
            }
            n_matches++;
        }
    }
    return head;
}

// int main(){
//     SearchEngine* s = new SearchEngine();
//     // s->insert_sentence(0,0,0,0,"abacababacababaabacababa");
//     // int x=0;
//     // Node* y=s->search("abacababa",x);
//     s->insert_sentence(0,0,0,0,"the quick brown fox jumps TEST over the lazy dog. it is a beautiful day, and the sun is shining brightly. nature is full of wonders, and we should take time to appreciate its beauty.");
//     s->insert_sentence(0,0,0,0,"tEst");
//     int x=0;
//     Node* y=s->search("test",x);
//     while(y){
//         std::cout<<y->offset<<"\n";
//         y=y->right;
//     }
//     std::cout<<"the value of x is: "<<x<<"\n";
//     delete s;
// }