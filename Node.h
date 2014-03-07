#ifndef CLOJURE_NODE_H
#define CLOJURE_NODE_H

#include <memory>
#include <sstream>

namespace clojure {
    using namespace std;

    class BaseNode;
    typedef shared_ptr<BaseNode> NodePtr;

    class BaseNode {
    public:
        BaseNode() = default;
        BaseNode(NodePtr tail):
            tail_(tail)
        {}
        virtual ~BaseNode();
        
        NodePtr Tail() { return tail_; }
        const NodePtr Tail() const { return tail_; }
        
        virtual string ToString() const = 0;
    protected:
        NodePtr tail_ = nullptr;
    };

    template <typename T>
    class Node : public BaseNode {
    public:
        typedef shared_ptr<T> Ptr;
        Node() = default;
        Node(T head):
            head_(make_shared<T>(head))
        {}
        Node(Ptr head):
            head_(head)
        {}
        Node(T head, NodePtr tail):
            BaseNode(tail),
            head_(make_shared<T>(head))
        {}
        Node(Ptr head, NodePtr tail):
            BaseNode(tail),
            head_(head)
        {}
        
        Ptr Head() { return head_; }
        const Ptr Head() const { return head_; }
        
        virtual string ToString() const override {
            ostringstream os; 
            os << '<' << *Head() << '>';
            if (Tail()) os << ' ' << Tail()->ToString();
            return os.str();
        }
    protected:
        Ptr head_ = nullptr;
    };
    
    template <typename T>
    NodePtr MakeNode(T t, NodePtr ptr = nullptr) {
        return make_shared<Node<T>>(t, ptr); 
    }
}

#endif
