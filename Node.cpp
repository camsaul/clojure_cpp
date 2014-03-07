
#include "Node.h"

namespace clojure {
    BaseNode::~BaseNode() {}


    //****** MakeNode *****//

    template <>
    NodePtr MakeNode<NodePtr>(NodePtr ptr1, NodePtr ptr2) {
        return make_shared<Node<BaseNode>>(ptr1, ptr2);
    }


    //***** Node::ToString() *****//

    template <>
    string Node<string>::ToString() const {
        return '"' + *Head() + "\" " + (Tail() ? Tail()->ToString() : " ");
    }

    template <>
    string Node<BaseNode>::ToString() const {
        return "( " + (Head() ? Head()->ToString() : "") + ") " + (Tail() ? Tail()->ToString() : "");
    }
}
