#include "Node.h"
#include <assert.h>

Node::Node() {
    left=NULL;
    right=NULL;
}

Node::Node(int b_code, int pg, int para, int s_no, int off){
    left=NULL;
    right=NULL;
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    offset = off;
}