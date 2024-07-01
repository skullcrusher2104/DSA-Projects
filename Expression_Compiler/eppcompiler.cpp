/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//#include<iostream> // remove before submission

//Write your code below this line

std::string commandmaker(ExprTreeNode* root, SymbolTable* symtable, Parser &targ){
    if(root->type=="VAL"){
        //std::cout<<"hi"<<"\n";
        return "PUSH "+std::to_string(root->num)+"\n";
    }
    else if(root->type=="VAR"){
        int index=symtable->search(root->id);
        if(index==-2){
            return "PUSH mem["+std::to_string(targ.last_deleted)+"]\n";
        }
        return "PUSH mem["+std::to_string(index)+"]\n";
    }
    else{
        std::string left=commandmaker(root->left,symtable,targ);
        std::string right=commandmaker(root->right,symtable,targ);
        //std::cout<<"hi"<<"\n";
        std::string x=root->type;
        //std::cout<<"hi:)"<<"\n";
        return right+left+x+"\n";
    }
}

EPPCompiler::EPPCompiler(){
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    //Parser* new_targ = new Parser();
    //targ = *new_targ;
    output_file=out_file;
    // for(int i=0;i<mem_limit;i++){
    //     mem_loc.emplace_back(i);
    // }
    for(int i=0;i<mem_limit;i++){
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    for(int i=0;i<code.size();i++){
        targ.parse(code[i]);
        ExprTreeNode* parse_tree=targ.expr_trees.back();
        std::vector<std::string>commands=generate_targ_commands();
        if(parse_tree->left->type=="VAR"){
            //std::cout<<"hello"<<"\n";
            int index=targ.symtable->search(parse_tree->left->id);
            //std::cout<<"bye"<<"\n";
            int free_memory=least_mem_loc.get_min();
            least_mem_loc.pop();
            if(index==-1){
                //std::cout<<"insert\n";
                //targ.symtable->insert(parse_tree->left->id);
                //std::cout<<"insert done\n";
                targ.symtable->assign_address(parse_tree->left->id,free_memory);
                commands[0]+="mem["+std::to_string(free_memory)+"] = POP\n";
            }
            else{
                least_mem_loc.push_heap(index);
                targ.symtable->assign_address(parse_tree->left->id,free_memory);
                commands[0]+="DEL = mem["+std::to_string(index)+"]\n";
                commands[0]+="mem["+std::to_string(index)+"] = POP\n";
                least_mem_loc.push_heap(free_memory);
            }
        }
        else if(parse_tree->left->type=="DEL"){
            int index=targ.last_deleted;//targ.symtable->search(parse_tree->left->id);
            least_mem_loc.push_heap(index);
            //targ.symtable->remove(parse_tree->left->id);
            commands[0]+="DEL = mem["+std::to_string(index)+"]\n";
        }
        else{
            commands[0]+="RET = POP";
        }
        write_to_file(commands);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* parse_tree=targ.expr_trees.back();
    std::vector<std::string> commands;
    commands.emplace_back(commandmaker(parse_tree->right,targ.symtable,targ));
    return commands;
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream x;
    x.open(output_file,ios::out|ios::app);
    for(int i=0;i<commands.size();i++){
        x<<commands[i]<<"\n";
    }
    x.close();
}

EPPCompiler::~EPPCompiler(){
    //delete &targ;
    // int x=mem_loc.size();
    // for(int i=0;i<x;i++){
    //     mem_loc.erase(mem_loc.begin());
    // }
    output_file="";
    memory_size=0;
}

// int main(){
//     EPPCompiler* complier = new EPPCompiler("",10);
//     std::vector<std::string> s1;
//     std::vector<std::string> s2;
//     std::vector<std::string> s3;
//     s1.emplace_back("a");
//     s1.emplace_back(":=");
//     s1.emplace_back("(");
//     s1.emplace_back("(");
//     s1.emplace_back("2");
//     s1.emplace_back("*");
//     s1.emplace_back("4");
//     s1.emplace_back(")");
//     s1.emplace_back("+");
//     s1.emplace_back("10");
//     s1.emplace_back(")");

//     s2.emplace_back("b");
//     s2.emplace_back(":=");
//     s2.emplace_back("(");
//     s2.emplace_back("3");
//     s2.emplace_back("*");
//     s2.emplace_back("4");
//     s2.emplace_back(")");

//     s3.emplace_back("ret");
//     s3.emplace_back(":=");
//     s3.emplace_back("(");
//     s3.emplace_back("a");
//     s3.emplace_back("+");
//     s3.emplace_back("b");
//     s3.emplace_back(")");
//     std::vector<std::vector<std::string>> s;
//     s.emplace_back(s1);
//     s.emplace_back(s2);
//     s.emplace_back(s3);
//     complier->compile(s);
//     std::cout<<complier->output_file;
// }