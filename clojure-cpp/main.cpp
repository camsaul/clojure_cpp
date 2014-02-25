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
		auto result = node.Eval();
		do {
			result = result->Eval();
		} while (result->Next()); // keep on evaluating until we get to an atom
		
		std::cout << (node ? result->DebugPrint() : "nil") << std::endl;
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
	
	auto n = NodePtrWithValue("TESTING!");
	TryEvalAndPrint(n);
	
//	auto n2 = NodePtrWithNode();
//	TryEvalAndPrint(n2);
	
	auto n3 = NodePtrWithValue("YAY", n);
	TryEvalAndPrint(n3);
	
	Node2<int> n100 { 100 }; // "Int: 100"
	TryEvalAndPrint(n100);
	
	Node2<int> n300 { 200, n100 };
	TryEvalAndPrint(n300);
	
	// function that takes one or more nodes ? ( should already be fully eval'ed )
	
	/// NodeFn '+'
	NodeFn NodeFn_Plus {};
	NodeFn_Plus = [&NodeFn_Plus](NodePtr node) -> NodePtr {
		if (!node) {
			return NilNode;
		}
		else if (!node->Next()) {
			return node;
		}
		else {
			// TODO: recursion: return H + NodeFn_Plus(T)
			
			// try to dyamic cast to int ?
			if (typeid(*node) == typeid(*node->Next()) && node->ValueTypeInfo() == typeid(int)) {
				auto n1 = TryDynamicCastNode<int>(node);
				auto n2 = TryDynamicCastNode<int>(node->Next());
				auto res = n1->Value() + n2->Value();
				if (n2->Next()) {
					FnNode fnNode { NodeFn_Plus, NodePtrWithValue(res, n2->Next()) };
					return NodePtrWithNode(fnNode);
				} else {
					return NodePtrWithValue(res);
				}
			} else { // just concat any other situation
				std::ostrstream os;
				os << node->Print() + " " + node->Next()->Print();
				return NodePtrWithValue(os.str());
			}
		}
	};
	
//	// ok, try eval and print with fn at head of list
	NodePtr node150 = NodePtrWithValues(100, 50);
	FnNode fnNode { NodeFn_Plus, node150};
	TryEvalAndPrint(fnNode); // 100 + 50 -> 150 ?
	
	TryEvalAndPrint(FnNode{ NodeFn_Plus, n300 }); // 200 + 100 -> 300 ?
	
	TryEvalAndPrint(FnNode{ NodeFn_Plus, n3 }); // n3 = {"YAY, "TESTING"} -> "YAY TESTING"
	
	// ok, try recursion
	NodePtr node1150 = NodePtrWithValue(1000, node150);
	TryEvalAndPrint(FnNode{ NodeFn_Plus, node1150 }); // (1000 + 100) + 50 -> 1150
	
	// with list of 4
	NodePtr node1500 = NodePtrWithValue(350, node1150);
	TryEvalAndPrint(FnNode { NodeFn_Plus, node1500 });
	
    return 0;
}

