/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="";
    id="";
    num=0;
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    type=t;
    id="";
    num=v;
    left=NULL;
    right=NULL;
}

ExprTreeNode::~ExprTreeNode(){
    // type="";
    // id="";
    // num=0;
    // delete left;
    // delete right;
}

