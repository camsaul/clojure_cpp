//
//  Node.cpp
//  clojure-cpp
//
//  Created by Cam Saul on 2/24/14.
//  Copyright (c) 2014 Cam Saul. All rights reserved.
//
#include <cxxabi.h>
#include <iostream>
#include <regex>

#include "Node.h"

using namespace std;



namespace clojure {
	std::string Node::ReadableTypeName() const {
		const std::type_info& typeInfo = typeid(*this);
		int status ;
		char *temp = __cxxabiv1::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
		if(temp) {
			string result{temp};
			free(temp);
			
			// it would be nice (maybe) to remove std::__1::, etc.
			static const vector<string> removals { "std::__1::", "clojure::"};
			for (auto& strToRemove : removals) {
				std::regex rx { strToRemove };
				result = std::regex_replace(result, rx, "");
			}
			
			return result;
		}
		else return typeInfo.name() ;
	}
	
	Node::Node():
		next_ { nullptr }
	{}
	
	Node::operator bool() const {
		return false;
	}
	
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