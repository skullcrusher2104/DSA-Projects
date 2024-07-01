/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable(){
    size=0;
    root = new SymEntry();
}

SymbolTable::~SymbolTable(){
    size=0;
    delete root->left;
    delete root->right;
    delete root;
}

SymEntry* get_successor(SymEntry* s){
    if(s->right==nullptr){
        return nullptr;
    }
    else{
        SymEntry* current_node=s->right;
        while(current_node->left){
            current_node=current_node->left;
        }
        return current_node;
    }
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    if(size==0){
        root->key=k;
        root->val=v;
        size++;
    }
    else{
        SymEntry* current_node = root;
        SymEntry* current_parent= nullptr;
        while(current_node){
            current_parent=current_node;
            if(current_node->key<k){
                current_node=current_node->right;
            }
            else{
                current_node=current_node->left;
            }
        }
        if(current_parent->key<k){
            current_parent->right = new SymEntry(k,v);
        }
        else{
            current_parent->left = new SymEntry(k,v);
        }
        size++;
    }
}

void SymbolTable::remove(string k){
    if(root->key==k){
        SymEntry* successor=get_successor(root);
        if(!successor){
            root=root->left;
            delete root;
        }
        else{
            root=successor;
            delete successor;
        }
    }
    else{
        SymEntry* current_node = root;
        SymEntry* current_parent = nullptr;
        while(current_node->key!=k){
            current_parent=current_node;
            if(current_node->key<k){
                current_node=current_node->right;
            }
            else{
                current_node=current_node->left;
            }
        }
        SymEntry* successor=get_successor(current_node);
        if(!successor){
            if(!current_node->left){
                delete current_node;
            }
            else{
                if(current_parent->left==current_node){
                    current_parent->left=current_node->left;
                    delete current_node;
                }
                else{
                    current_parent->right=current_node->left;
                    delete current_node;
                }
            }
        }
        else{
            current_node=successor;
            delete successor;
        }
    }
    size--;
}

UnlimitedRational* SymbolTable::search(std::string k){
    if(root->key==k){
        return root->val;
    }
    else{
        SymEntry* current_node = root;
        while(current_node->key!=k){
            if(current_node->key<k){
                current_node=current_node->right;
            }
            else{
                current_node=current_node->left;
            }
        }
        return current_node->val;
    }
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}