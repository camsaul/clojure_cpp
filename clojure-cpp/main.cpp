//
//  main.cpp
//  clojure-cpp
//
//  Created by Cam Saul on 2/24/14.
//  Copyright (c) 2014 Cam Saul. All rights reserved.
//

#include <cassert>
#include <iostream>
#include "Node.h"

using namespace clojure;

int main(int argc, const char * argv[])
{

	// insert code here...
	std::cout << "Hello, World!\n";
	
	Node empty {};
	empty.Eval();

	Node2<std::string> n {"TESTING!"};
	Node n2 {n};
	assert(n2.Next());
	Node2<std::string> n3 { "YAY", n2 };
	n3.Eval();
	
	
    return 0;
}

