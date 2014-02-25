//
//  Node.cpp
//  clojure-cpp
//
//  Created by Cam Saul on 2/24/14.
//  Copyright (c) 2014 Cam Saul. All rights reserved.
//

#include <iostream>
#include <cxxabi.h>

#include "Node.h"

using namespace std;



namespace clojure {
	std::string readable_name(const std::type_info& typeInfo) {
		int status ;
		char *temp = __cxxabiv1::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
		if(temp) {
			string result{temp};
			free(temp);
			return result;
		}
		else return typeInfo.name() ;
	}
	
	Node::Node():
		next_ { nullptr }
	{}
	
	NodePtr Node::Eval() const {
		return nullptr;
	}
	
	std::string Node::Print() const {
		return "nil [empty node]";
	}
	
	Node::Node(std::shared_ptr<const Node> next):
		next_ { next }
	{}
	
//	NodePtr Node::Eval() const {
//		if (Next()) {
//			throw runtime_error { "Not a function: " + readable_name(typeid(*this).name()) + " is not a function. " };
//		}
//		return MakeNodePtr(*this);
//	}
}