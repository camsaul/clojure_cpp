#include <functional>
#include <iostream>
#include <memory>
#include <regex>
#include <string>

using namespace std;

class BaseNode;
typedef shared_ptr<BaseNode> NodePtr;

class BaseNode {
public:
    BaseNode() = default;
    BaseNode(NodePtr tail):
        tail_(tail)
    {}
    virtual ~BaseNode() {}

    NodePtr Tail() { return tail_; }
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
protected:
    Ptr head_ = nullptr;
};

template <typename T>
NodePtr MakeNode(T t, NodePtr ptr = nullptr) {
    return make_shared<Node<T>>(t, ptr); 
}

/// \param read Tokens that have already been read
/// \param text remaining text to parse
NodePtr Read(string::iterator begin, string::iterator end) {
    if (begin == end) {
        return nullptr;
    }

    // ignore whitespace
    while (begin != end && *begin == ' ') begin++;

    // read a token
    bool escape = false;
    string token = "";
    while (begin != end) {
        if (!escape && *begin == ' ') break;
        escape = *begin == '\\';
        token.push_back(*begin);
        begin++;
    }
    if (token.empty()) return nullptr;

    return MakeNode(token, Read(begin, end));
}

void Print(NodePtr node) {
    if (auto strNode = dynamic_cast<Node<string> *>(node.get())) {
        cout << '[' << (strNode->Head() ? *strNode->Head() : "(null)") << "] ";
    }
    if (node->Tail()) {
        Print(node->Tail());
    } else {
        cout << endl;
    }
}

int main() {
    auto RP = [](string s){
        auto node = Read(s.begin(), s.end());
        Print(node);
    };

    RP("12");
    RP("12 abcde 1997");
    RP("12 ab\\ cde 1997");
    
    return 0;
}








