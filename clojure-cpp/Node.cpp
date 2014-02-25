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
			static const vector<string> removals { "std::__1::", "clojure::", "const", "\\*"};
			for (auto& strToRemove : removals) {
				std::regex rx { strToRemove };
				result = std::regex_replace(result, rx, "");
			}
			static const vector<pair<string, string>> replacements { { "char", "string" }, {"Node2<([^>]+)>", "$1"}};
			for (auto& replacement : replacements) {
				std::regex rx { replacement.first };
				result = std::regex_replace(result, rx, replacement.second);
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
	
	std::string Node::DebugPrint(int) const {
		return "nil";
	}
	
	std::string Node::Print() const {
		return "nil";
	}
	
	std::string Node::PrintNext() const {
		std::ostrstream os;
		os << "(";
		auto next = Next();
		while (next) {
			os << " " << next->Print();
			next = next->Next();
		}
		os << ")";
		return os.str();
	}
	
	Node::Node(std::shared_ptr<const Node> next):
		next_ { next }
	{}
}