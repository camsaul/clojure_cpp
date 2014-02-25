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

typedef std::shared_ptr<const Node> NodePtr;
typedef std::function<NodePtr(NodePtr)> NodeFn;

void TryEvalAndPrint(const Node& node) {
	try {
		auto val = node.Eval();
		std::cout << (val ? val->Print() : "nil") << std::endl;
	} catch (const std::runtime_error& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
}

int main(int argc, const char * argv[])
{

	// insert code here...
	std::cout << "Hello, World!\n";
	
	Node2<std::string> n {"TESTING!"};	// "Value: Testing!"
	TryEvalAndPrint(n);
	
	Node n2 {};
	TryEvalAndPrint(n2);
	
	Node2<std::string> n3 { "YAY", n2 }; // "Value: YAY"
	TryEvalAndPrint(n3);
	
	Node2<int> n4 { 100 }; // "Int: 100"
	TryEvalAndPrint(n4);
	
	// function that takes one or more nodes ?
	
	
    return 0;
}

