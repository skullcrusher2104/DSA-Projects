#include <assert.h>
#include <sstream>
#include "qna_tool.h"
using namespace std;

#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"


int get_height(TreeNode* root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}

TreeNode::TreeNode(){
    word="";
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

TreeNode::TreeNode(string k){
    word=k;
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

TreeNode* TreeNode::LeftLeftRotation(){
    TreeNode* temp=this->right->left;
    TreeNode* new_root=this->right;
    if(temp){
        this->right=temp;
        temp->par=this;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->left=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
    else{
        this->right=temp;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->left=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
}

TreeNode* TreeNode::RightRightRotation(){
    TreeNode* temp=this->left->right;
    TreeNode* new_root=this->left;
    if(temp){
        this->left=temp;
        temp->par=this;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->right=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
    else{
        this->left=temp;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->right=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
}

TreeNode* TreeNode::LeftRightRotation(){
    TreeNode* new_right=this->right->RightRightRotation();
    this->right=new_right;
    new_right->par=this;
    this->height=std::max(get_height(this->left),get_height(this->right))+1;
    return this->LeftLeftRotation();
}

TreeNode* TreeNode::RightLeftRotation(){
    TreeNode* new_left=this->left->LeftLeftRotation();
    this->left=new_left;
    new_left->par=this;
    this->height=std::max(get_height(this->left),get_height(this->right))+1;
    return this->RightRightRotation();
}

TreeNode::~TreeNode(){
}

Tree::Tree(){
    size=0;
    root = new TreeNode();
}

bool is_left_heavy(TreeNode* root){
    if(get_height(root->left)-get_height(root->right)>1){
        return true;
    }
    return false;
}

bool is_balancedd(TreeNode* root){
    if(get_height(root->left)-get_height(root->right)<=1 && get_height(root->right)-get_height(root->left)<=1){
        return true;
    }
    return false;
}

TreeNode* balance_tree(TreeNode* root){
    while(root->par!=NULL){
        if(!is_balancedd(root)){
            bool left_child=false;
            TreeNode* parent=root->par;
            if(parent->left==root){
                left_child=true;
            }
            TreeNode* child;
            if(is_left_heavy(root)){
                if(get_height(root->left->left)>=get_height(root->left->right)){
                    child=root->RightRightRotation();
                }
                else{
                    child=root->RightLeftRotation();
                }
            }
            else{
                if(get_height(root->right->left)<=get_height(root->right->right)){
                    child=root->LeftLeftRotation();
                }
                else{
                    child=root->LeftRightRotation();
                }
            }
            child->par=parent;
            if(left_child){
                parent->left=child;
            }
            else{
                parent->right=child;
            }
            root=parent;
            root->height=std::max(get_height(root->left),get_height(root->right))+1;
        }
        else{
            root=root->par;
            root->height=std::max(get_height(root->left),get_height(root->right))+1;
        }
    }
    if(root->par==NULL){
        if(is_balancedd(root)){
            return root;
        }
        if(is_left_heavy(root)){
            if(get_height(root->left->left)>=get_height(root->left->right)){
                root=root->RightRightRotation();
            }
            else{
                root=root->RightLeftRotation();
            }
        }
        else{
            if(get_height(root->right->left)<=get_height(root->right->right)){
                root=root->LeftLeftRotation();
            }
            else{
                root=root->LeftRightRotation();
            }
        }
        root->par=NULL;
        return root;
    }
    while(root->par!=NULL){
        root=root->par;                     
    }
    return root;
}

void Tree::insert(std::string k){
    if(size==0){
        delete root;
        root = new TreeNode(k);
        size++;
        return;
    }
    TreeNode* current_node=root;
    while(current_node->word!=k && get_height(current_node)>=0){
        if(current_node->word<k){
            if(!current_node->right){
                break;
            }
            current_node=current_node->right;
        }
        else{
            if(!current_node->left){
                break;
            }
            current_node=current_node->left;
        }
    }
    if(current_node->word==k){
        return;
    }
    TreeNode* current_parent=current_node->par;
    TreeNode* child = new TreeNode(k);
    if(k>current_node->word){
        current_node->right=child;
        child->par=current_node;
        current_node=current_node->right;
    }
    else{
        current_node->left=child;
        child->par=current_node;
        current_node=current_node->left;
    }
    size++;
    while(current_node->par!=NULL){
        current_node=current_node->par;
        current_node->height=1+std::max(get_height(current_node->left),get_height(current_node->right));
    }
    if(!current_parent){
        return;
    }
    while(is_balancedd(current_parent) && current_parent->par!=NULL){
        current_parent=current_parent->par;
    }

    root=balance_tree(current_parent);
}

bool Tree::search(string k){
    TreeNode* current_node=root;
    if(!root){
        return false;
    }
    while(current_node->word!=k && get_height(current_node)>=0){
        if(current_node->word<k){
            if(!current_node->right){
                break;
            }
            current_node=current_node->right;
        }
        else{
            if(!current_node->left){
                break;
            }
            current_node=current_node->left;
        }
    }
    if(current_node->word!=k){
        return false;
    }
    return true;
}

int Tree::get_size(){
    return size;
}

TreeNode* Tree::get_root(){
    return root;
}

void destruct(TreeNode* root){
    if(!root){
        return;
    }
    destruct(root->left);
    destruct(root->right);
    delete root;
}

Tree::~Tree(){
    size=0;
    destruct(root);
}



maxHeap::maxHeap(){
    size=0;
}
int maxHeap::get_parent(int x){
    return (x-1)/2;
}
int maxHeap::get_left(int x){
    return 2*x+1;
}
int maxHeap::get_right(int x){
    return 2*x+2;
}

void maxHeap::heapifyUp(int index){
    int parent=get_parent(index);
    if(parent==index){
        return;
    }
    if(heap[index].first>heap[parent].first){
        std::swap(heap[index],heap[parent]);
        heapifyUp(parent);
    }
    return;
}

void maxHeap::heapifyDown(int index){
    int left = get_left(index);
    int right = get_right(index);
    int y=index;
    if(left>=heap.size()){
        return;
    }
    if(heap[index].first<heap[left].first){
        y=left;
    }
    if(right<heap.size() && heap[y].first<heap[right].first){
        y=right;
    }
    if(y!=index){
        std::swap(heap[y],heap[index]);
        heapifyDown(y);
    }
    return;
}

std::pair<double,vector<int>> maxHeap::top(){
    return heap[0];
}

void maxHeap::push(std::pair<double,vector<int>> element){
    heap.push_back(element);
    heapifyUp(size);
    size++;
}

void maxHeap::pop(){
    if(size==0){
        return;
    }
    size--;
    std::swap(heap[0],heap[size]);
    heap.pop_back();
    heapifyDown(0);
}

bool maxHeap::empty(){
    if(size) return false;
    return true;
}


void deletenode(){
    return;
}

string convert_to_lower(string s){
    int n = s.length();
    for(int i = 0 ; i<n ;i++){
        int x = int (s[i]);
        if(x>=65 and x<=90){
            s[i] = char(x+32);
        }
    }
    return s;
}

vector<string> convert_to_words(string sentence){
    vector<string> result;
    string s="";
    for(char c:sentence){
        int x = int (c);
        if((x>=97 and x<=122) or (x>=48 and x<=57)){
            s+=c;
        }
        else if(x>=65 and x<=90){
            s+= char(x+32);
        }
        else{
            if(s.length()){
                result.push_back(s);
                s="";
            }
        }
    } 
    if(s.length()) result.push_back(s);
    return result;
}

std::string process_text(std::string query, Tree* t){
    // string lowquery = convert_to_lower(query);
    std::vector<string> new_query=convert_to_words(query);
    std::string question="";
    for(auto x:new_query){
        if(!(t->search(x))){
            question+=x+" ";
        }
    }
    return question;
}

long int compute_score(string s){
    ifstream file("unigram_freq.csv", ios::in);
    string line, word, temp,c; 
    long int count=0;
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 0;
    }
    bool flag=false;
    while (std::getline(file, line)) {
        istringstream iss(line); 
        while (std::getline(iss, word, ',') && std::getline(iss,c,' ')) { 
            if(word==s){
                count=stol(c);
                flag=true;
                break;
            }
        }
        if(flag){
            break;
        }
    } 
    return count;
}

QNA_tool::QNA_tool(){
    dictionary= new Dict();

    //s= new SearchEngine();

    std::vector<std::string> words = {
    "the","effect", "of", "according" ,"and", "to", "a", "in", "for", "is", "on", "that", "by", "this", "with", "i", "you", "it", "not", "or", "be", "are", "from", "at", "as", "your", "all", "have",  "an", "was", "we", "will",  "can", "us", "about", "if",  "my", "has",  "but", "our", "one", "other", "do", "no", "they", "he", "up", "may", "what", "which", "their",  "any", "there", "only", "so", "his", "when",  "here",  "who",  "also", "now", "get", "c", "e",  "am", "been", "would", "how", "were", "me", "s",  "some", "these",  "its",  "x", "than", 
    "who", "what", "when" ,"where", "why","view", "how", "which", "are", "is", "could", "should", "would", "can", "will", "did", "does", "if",  "suppose", 
    };
    t = new Tree();
    for(auto x:words){
        t->insert(x);
    }
    // Implement your function here  
}

QNA_tool::~QNA_tool(){
    delete t;
    delete dictionary;
    // Implement your function here  
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    dictionary->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    // Implement your function here  
    return;
}

Node* QNA_tool::get_top_k_para(string question, int k) {
    // Implement your function here
    int  max_books  = 99;
    int  max_pages = 540;
    int max_paras  =80;
        
    double*** arr = new double**[max_books];
    for (int i = 0; i < max_books; i++) {
        arr[i] = new double*[max_pages];
        for (int j = 0; j < max_pages; j++) {
            arr[i][j] = new double[max_paras]();
        }
    }
    for(int i = 0; i< max_books; i++){
        for(int j = 0 ; j<max_pages;j++){
            for(int p =0 ; p<max_paras; p++){
                arr[i][j][p]=0;
            }
        }
    }
    
    string new_question=convert_to_lower(question);
    vector<string> ques_words;

    ques_words=convert_to_words(new_question);

    for(int i=0;i<ques_words.size();i++){
        // cout << ques_words[i] << endl;
        double score;
        long int count=dictionary->get_word_count(ques_words[i]);
        long int den=compute_score(ques_words[i])+1;

        Node2* temp= dictionary->get_head(ques_words[i]);/////!!!!!!!!
        // Node2* temp=s->search(ques_words[i],count);
        score=((1+count)*1.0)/den;
        while(temp!=NULL){
            arr[temp->book_code][temp->page][temp->paragraph]+=score;
            temp = temp->right;
        }
        // deletenode();
    }
    maxHeap pq;
    // priority_queue<pair<double,vector<int>>,vector<pair<double,vector<int>>>,greater<pair<double,vector<int>>>> pq;
    for(int i = 0; i< max_books; i++){
        for(int j = 0 ; j<max_pages;j++){
            for(int p =0 ; p<max_paras; p++){
                if(arr[i][j][p]){
                    pair<double,vector<int>> pa;
                    pa.first = arr[i][j][p];
                    pa.second.push_back(i), pa.second.push_back(j), pa.second.push_back(p);
                    pq.push(pa);
                }
            }
        }
    }
    for (int i = 0; i < max_books; i++) {
        for (int j = 0; j < max_pages; j++) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
    // cout << arr[29][226][4] << endl;
    // cout << arr[30][0][3] << endl;
    // cout << arr[9][484][4] << endl;

    Node* permhead= NULL;
    Node* head=NULL;
    for(int i = 0; i< k ;i++){
        if(pq.empty()) break;
        pair<double,vector<int>> p = pq.top();
        pq.pop(); 
        int _book = p.second[0],_page = p.second[1],_para = p.second[2];
        Node* newnode = new Node(_book,_page,_para,0,0);
        newnode->right =NULL;
        newnode->left=NULL;
        if(head==NULL){
            head=newnode;
            permhead = head;
            continue;
        }
        newnode->left=head;
        head->right = newnode;
        head = head->right;
    }
 
    return permhead;
}

void QNA_tool::query(string question, string filename){
    // Implement your function here 
    std::string new_question=process_text(question,t);
    // string new_question = question;
    cout << new_question << endl;
    int k=7;
    Node* head=get_top_k_para(new_question,k);

    // std::cout << "Q: " << question << std::endl;
    // std::cout << "A: Studying COL106 :)" << std::endl;
    string api_key = "api_key";
    query_llm(filename,head,k,api_key,question);
    Node* temp = head->right;
    for(int i = 0; i< k-1 ; i++){
        temp->left = NULL;
        delete head;
        head = temp;
        temp = temp->right;
    }
    delete head;
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
    int count=0;
    // first write the k paragraphs into different files
    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != NULL);
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
    outfile << "These are the excerpts from Mahatma Gandhi's books.\n";
    bool flag = false;
    for(int i = 0 ;i< k ; i++){
        string p_file = "paragraph_";
        p_file += to_string(i);
        p_file += ".txt";
        ifstream file(p_file, ios::in);
        string line;
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open the file." << std::endl;
            continue;
        }
        
        while (std::getline(file, line)) {
        istringstream iss(line);
        if(flag) break;
        for(char h : line){
            if(h==' '){
                count++;
            }
           outfile << h;
           if(count>3300) {
            flag = true;
            break;
           }
        }
        outfile <<endl;
        if (flag) break;
        
        }
    }
    outfile << "Use only the above paragraphs to frame an answer for the question below.\n";
    outfile << "Do not include any information other than that can be extracted from the given paragraphs\n";
    outfile << " The only different things that you should use are grammatical words to coherently frame the answer \n";
    outfile << question;
    outfile << "\nFirstly and most importantly, give the answer for the above question in about 10 sentences and after that ";
    outfile << "give references to the sentences from the given paragraphs in sequence which you have used to frame the answer. ";
    outfile << endl;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close(); 
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += "api_call.py";
    command += " ";
    command += API_KEY;
    command += " ";
    // for(int i=0;i<k;i++){
    //     command += "paragraph_"+to_string(i)+".txt";
    //     command += " ";
    // }
    command += "query.txt";
    command += " ";
    command+= "answer.txt";

    // ofstream ofile(filename);
    // ofile << system(command.c_str());
     system(command.c_str());
    
    
}


// int main(){
//     string s="the";
//     cout<<compute_score(s)<<endl;
//     cout<<compute_score("is")<<endl;
// }

// int main(){
//     maxHeap* q = new maxHeap();
//     for(int i=0;i<100;i++){
//         std::pair<double,vector<int>> element;
//         element.first=((i+3457)*(i+2397)*(i+6537))%10000;
//         q->push(element);
//     }
//     for(int i=0;i<100;i++){
//         std::cout<<q->top().first<<"\n";
//         q->pop();
//     }
//     delete q;
// }