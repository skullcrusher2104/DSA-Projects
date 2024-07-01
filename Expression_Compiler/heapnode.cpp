/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    val=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

HeapNode::HeapNode(int _val){
    val=_val;
    par=NULL;
    left=NULL;
    right=NULL;
}

HeapNode::~HeapNode(){
    val=0;
    // delete par;
    // delete left;
    // delete right;
}