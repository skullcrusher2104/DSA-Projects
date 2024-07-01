/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    type="";
    val = new UnlimitedRational();
    evaluated_value= new UnlimitedRational();
    id="";
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::ExprTreeNode(std::string t, UnlimitedInt* v){
    type=t;
    UnlimitedInt* u = new UnlimitedInt(1);
    UnlimitedRational* r = new UnlimitedRational(v,u);
    val=r;
    evaluated_value=r;
    //delete u;
    //delete r;
    id="";
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::ExprTreeNode(std::string t, UnlimitedRational* v){
    type=t;
    val=v;
    evaluated_value=v;
    id="";
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::~ExprTreeNode(){
    type="";
    delete val;
    delete evaluated_value;
    id="";
    delete left;
    delete right;
}