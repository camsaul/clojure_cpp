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

#include "Node.h"

using namespace clojure;

void TryEvalAndPrint(const Node& node) {
	try {
		std::cout << (node ? node.Eval()->Print() : "nil") << std::endl;
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

int main(int argc, const char * argv[])
{

	// insert code here...
	std::cout << "Hello, World!\n";
	
	auto n = MakeNode2Ptr("TESTING!");
	TryEvalAndPrint(n);
	
	auto n2 = MakeNodePtr();
	TryEvalAndPrint(n2);
	
	auto n3 = MakeNode2Ptr("YAY", n2);
	TryEvalAndPrint(n3);
	
	Node2<int> n4 { 100 }; // "Int: 100"
	TryEvalAndPrint(n4);
	
	Node2<int> n5 { 200, n4 };
	TryEvalAndPrint(n5);
	
	// function that takes one or more nodes ?
	
	/// NodeFn '+'
	NodeFn NodeFn_Plus = [](NodePtr node) -> NodePtr {
		if (!node) {
			return NilNode;
		}
		else if (!node->Next()) {
			return node->Eval();
		}
		else {
			// TODO: recursion: return H + NodeFn_Plus(T)
			
			// try to dyamic cast to int ?
			auto next = node->Next();
			const Node2<int> *intNode = dynamic_cast<const Node2<int> *>(node.get());
			if (!intNode) {
				throw std::runtime_error { "type error: " + node->ReadableTypeName() + " (value_ = " + node->Print() + ") is not an int!" };
			}
			const Node2<int> *intNode2 = dynamic_cast<const Node2<int> *>(next.get());
			if (!intNode2) {
				throw std::runtime_error { "type error: " + next->ReadableTypeName() + " (value_ = " + next->Print() + ") is not an int!" };
			}
			return MakeNodePtr<Node2<int>>(intNode->Value() + intNode2->Value());
		}
	};
	
	TryEvalAndPrint(NodeFn_Plus, MakeNodePtr(n5)); // 300 ?
	
	TryEvalAndPrint(NodeFn_Plus, n3); // n3 = {"YAY, nil} exception
	
    return 0;
}

