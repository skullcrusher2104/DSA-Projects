// Do NOT add any other includes
#include "search.h"

SNode::SNode(int b_code, int pg, int para, int s_no, string s){
    next = NULL;
    s_book_code = b_code;
    s_page = pg;
    s_paragraph = para;
    s_sentence_no = s_no;
    s_sentence = s;
}

string convert_to_lowercase(string s){
    int n = s.length();
    for(int i = 0 ; i<n ;i++){
        int x = int (s[i]);
        if(x>=65 and x<=90){
            s[i] = char(x+32);
        }
    }
    return s;
}

SearchEngine::SearchEngine(){
    head = new SNode(-1,-1,-1,-1,"");
}

SearchEngine::~SearchEngine(){
    SNode* temp = head;
    while(temp!=NULL){
        SNode* temptemp = temp->next;
        delete temp;
        temp = temptemp;
    } 
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string new_sentence = convert_to_lowercase(sentence);
    SNode* temp = new SNode(book_code,page,paragraph,sentence_no,new_sentence);
    temp->next = head->next;
    head->next = temp;
}

void calculatez(string str,int* arr){
    int n=str.length();
    int l,r,prev;
    l=r=0;
    arr[0]=0;
    for(int i=1;i<n;i++){
        if(i>r){
            l=r=i;
            while(str[r-l]==str[r] and r<n){
                r++;
            }
            r--;
            arr[i]=r-l+1;
        }
        else{
            prev=i-l;
            if(arr[prev]==0){
                arr[i]=0;
            }
            else{
                if(arr[prev]<r-i+1){
                    arr[i]=arr[prev];
                }
                else{
                    l=i;
                    while(r<n and str[r-l]==str[r]){
                        r++;
                    }
                    r--;
                    arr[i]=r-l+1;
                }
            }
        }
    }
}

Node* SearchEngine::search(string pattern,long int& n_matches){
    // Implement your function here 
    string new_pattern = convert_to_lowercase(pattern);
    SNode* temp=head->next;
    Node* res= NULL;
    Node* back=res;
    while(temp!=NULL){
        string cur=new_pattern+"S"+temp->s_sentence;
        int x = new_pattern.length();
        int n=cur.length();
        int arr[n];
        calculatez(cur,arr);
        for (int i = x+1; i < n; i++){
            if(arr[i]==x){
                Node* newnode = new Node(temp->s_book_code,temp->s_page,temp->s_paragraph,temp->s_sentence_no,i-x-1);
                n_matches++;
                newnode->left=NULL;
                newnode->right=NULL;
                if(res==NULL){
                    res=newnode;
                    back=res;
                }
                else{
                    back->right=newnode;
                    newnode->left=back;
                    back=newnode;
                }
            }
        }
        temp=temp->next;
    }
    return res;
}