//
//  main.cpp
//  clojure-cpp
//
//  Created by Cam Saul on 2/24/14.
//  Copyright (c) 2014 Cam Saul. All rights reserved.
//

#include <exception>
#include <functional>
#include <iostream>
#include <strstream>

#include "Node.h"

using namespace clojure;

void TryEvalAndPrint(const Node& node) {
	try {
		std::cout << (node ? node.Eval()->DebugPrint() : "nil") << std::endl;
	} catch (const std::runtime_error& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
}
void TryEvalAndPrint(NodePtr node) {
	if (!node) {
		std::cout << "nil" << std::endl;
	} else {
		TryEvalAndPrint(*node);
	}
}

NodePtr TryEvalAndPrint(NodeFn fn, NodePtr node = nullptr) {
	NodePtr result = nullptr;
	try {
		result = fn(node);
		TryEvalAndPrint(result);
	} catch (const std::runtime_error& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	return result;
}

template <typename ValueT>
const Node2<ValueT>* TryDynamicCastNode(NodePtr node) {
	if (!node) {
		throw std::runtime_error { "TryDynamicCastNode was called with a nil node!" };
	}
	const Node2<ValueT>* result =  dynamic_cast<const Node2<ValueT> *>(node.get());
	if (!result) {
		throw std::runtime_error { "type error: " + node->ReadableTypeName() + " (value_ = " + node->DebugPrint() + ") is not an int!" };
	}
	return result;
}


int main(int argc, const char * argv[])
{

	// insert code here...
	std::cout << "Hello, World!\n";
	
	auto n = MakeNode2Ptr("TESTING!");
	TryEvalAndPrint(n);
	
//	auto n2 = MakeNodePtr();
//	TryEvalAndPrint(n2);
	
	auto n3 = MakeNode2Ptr("YAY", n);
	TryEvalAndPrint(n3);
	
	Node2<int> n4 { 100 }; // "Int: 100"
	TryEvalAndPrint(n4);
	
	Node2<int> n5 { 200, n4 };
	TryEvalAndPrint(n5);
	
	// function that takes one or more nodes ? ( should already be fully eval'ed )
	
	/// NodeFn '+'
	NodeFn NodeFn_Plus = [](NodePtr node) -> NodePtr {
		if (!node) {
			return NilNode;
		}
		else if (!node->Rest()) {
			return node;
		}
		else {
			// TODO: recursion: return H + NodeFn_Plus(T)
			
			// try to dyamic cast to int ?
			if (typeid(*node) == typeid(*node->Rest()) && node->ValueTypeInfo() == typeid(int)) {
				auto n1 = TryDynamicCastNode<int>(node);
				auto n2 = TryDynamicCastNode<int>(node->Rest());
				return MakeNodePtr<Node2<int>>(n1->Value() + n2->Value());
			} else { // just concat any other situation
				std::ostrstream os;
				os << node->Print() + " " + node->Rest()->Print();
				return MakeNode2Ptr(os.str());
			}
		}
	};
	
	TryEvalAndPrint(NodeFn_Plus, n5); // 300 ?
	
	TryEvalAndPrint(NodeFn_Plus, n3); // n3 = {"YAY, nil} -> YAY nil
	
	// ok, try eval and print with fn at head of list
	NodePtr node = MakeNodePtr3(100, 50);
	std::cout << node->Print() << " " << node->PrintRest() << std::endl;
	FnNode fnNode { NodeFn_Plus, node};
	TryEvalAndPrint(fnNode);

	
	// ok, try recursion
	
    return 0;
}

