/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"


// #include<iostream>

//Write your code below this line

HeapNode* heapify_up(HeapNode* child){
    while(child->par){
        if(child->val<child->par->val){
            int x=child->val;
            child->val=child->par->val;
            child->par->val=x;
            child=child->par;
        }
        else{
            break;
        }
    }
    while(child->par){
        child=child->par;
    }
    return child;
}

// int compare(HeapNode* root){
//     if(root->left==NULL){
//         return 0;
//     }
// }

void heapify_down(HeapNode* root){

    if(root->left==NULL){
        return;
    }
    else if(root->left!=NULL && root->right==NULL){
        if(root->left->val<root->val){
            int x=root->val;
            root->val=root->left->val;
            root->left->val=x;
            return;
        }
        return;
    }
    else{
        if(root->val<root->left->val && root->val<root->right->val){
            return;
        }
        else if(root->val>root->left->val && root->val<root->right->val){
            int x=root->val;
            root->val=root->left->val;
            root->left->val=x; 
            heapify_down(root->left);
        }
        else if(root->val<root->left->val && root->val>root->right->val){
            int x=root->val;
            root->val=root->right->val;
            root->right->val=x; 
            heapify_down(root->right);
        }
        else{
            int x=root->left->val;
            int y=root->right->val;
            if(x<y){
                root->left->val=root->val; 
                root->val=x;
                heapify_down(root->left);
            }
            else{
                root->right->val=root->val; 
                root->val=y;
                heapify_down(root->right);
            }
        }
    }
}

std::string get_binary(int n){
    std::string binary="";
    while(n>0){
        binary=std::to_string(n%2)+binary;
        n=n/2;
    }
    return binary;
}


MinHeap::MinHeap(){
    root = new HeapNode();
}

void MinHeap::push_heap(int num){
    if(size==0){
        root->val=num;
        size++;
        return;
    }
    if(size==1){
        HeapNode* child = new HeapNode(num);
        root->left=child;
        child->par=root;
        heapify_up(child);
        size++;
        return;
    }
    // if(size==2){
    //     HeapNode* child = new HeapNode(num);
    //     root->right=child;
    //     child->par=root;
    //     heapify_up(child);
    //     size++;
    //     return;
    // }
    std::string binary=get_binary(size+1);
    binary.erase(binary.begin());
    HeapNode* current_parent=root;
    for(int i=0;i<binary.size()-1;i++){
        if(binary[i]=='0'){
            current_parent=current_parent->left;
        }
        else{
            current_parent=current_parent->right;
        }
    }
    HeapNode* child = new HeapNode(num);
    if(binary[binary.size()-1]=='0'){
        current_parent->left=child;
        child->par=current_parent;
    }
    else{
        current_parent->right=child;
        child->par=current_parent;
    }
    root=heapify_up(child);
    size++;
}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    if(size==1){
        root->val=0;
        size--;
        return;
    }
    std::string binary=get_binary(size);
    binary.erase(binary.begin());
    HeapNode* current_node=root;
    for(int i=0;i<binary.size();i++){
        if(binary[i]=='0'){
            current_node=current_node->left;
        }
        else{
            current_node=current_node->right;
        }
    }
    root->val=current_node->val;
    if(current_node->par->left==current_node){
        current_node->par->left=NULL;
    }
    else{
        current_node->par->right=NULL;
    }
    current_node->left=NULL;
    current_node->right=NULL;
    current_node->par=NULL;
    delete current_node;
    size--;
    heapify_down(root);
}

void destruct(HeapNode* root){
    if(!root){
        return;
    }
    destruct(root->left);
    destruct(root->right);
    delete root;
}

MinHeap::~MinHeap(){
    destruct(root);
}

// int main(){
//     MinHeap* s=new MinHeap();
//     // s->push_heap(10);
//     // s->push_heap(4);
//     // s->push_heap(1);
//     // s->push_heap(7);
//     // s->push_heap(9);
//     for(int i=500;i>0;i--){
//         s->push_heap(i);
//     }
//     for(int i=0;i<500;i++){
//         std::cout<<s->get_min()<<"\n";
//         s->pop();
//     }
//     // std::cout<<s->get_min()<<"\n";
//     // s->pop();
//     // std::cout<<s->get_min()<<"\n";
//     // s->pop();
//     // std::cout<<s->get_min()<<"\n";
//     // s->pop();
//     // std::cout<<s->get_min()<<"\n";
//     // s->pop();
//     // std::cout<<s->get_min()<<"\n";
//     // s->pop();
//     // std::cout<<s->root->val<<"\n";
// }