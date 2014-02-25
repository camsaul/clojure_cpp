//
//  Node.cpp
//  clojure-cpp
//
//  Created by Cam Saul on 2/24/14.
//  Copyright (c) 2014 Cam Saul. All rights reserved.
//

#include <iostream>

#include "Node.h"

namespace clojure {
	Node::Node(std::shared_ptr<const Node> next):
		next_ { next }
	{}
	
	void Node::Eval() const {
		std::cout << "HERE!" << std::endl;
		if (next_) next_->Eval();
	}
}