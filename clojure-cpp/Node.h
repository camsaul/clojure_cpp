//
//  Node.h
//  clojure-cpp
//
//  Created by Cam Saul on 2/24/14.
//  Copyright (c) 2014 Cam Saul. All rights reserved.
//

#ifndef __clojure_cpp__Node__
#define __clojure_cpp__Node__

#include <memory>
#include <iostream>

namespace clojure {

	class Node;
	typedef std::shared_ptr<const Node> NodePtr;
	
	template <typename NodeT>
	NodePtr MakeNodePtr(NodeT node) { return std::make_shared<const NodeT>(node); }
	
	class Node {
	public:
		template <typename NodeT>
		Node(NodeT n):
			next_ { MakeNodePtr<NodeT>(n) }
		{}
		
		Node(NodePtr next = nullptr);
		
		NodePtr Next() const { return next_; }
		
		virtual void Eval() const;
		
		virtual ~Node() = default;
		
	private:
		NodePtr next_;
	};
	
	template <typename ValueT>
	class Node2 : public Node {
	public:
		Node2(const ValueT& value, NodePtr next = nullptr):
			Node { next },
			value_ { value }
		{}
		
		template <typename NodeT>
		Node2(const ValueT& value, NodeT next):
			Node { MakeNodePtr<NodeT>(next) },
			value_ { value }
		{}
		
		const ValueT& Value() const { return value_; }
		
		virtual void Eval() const override {
			std::cout << "Value: " << Value() << std::endl;
			if (Next()) Next()->Eval();
		}
		
		virtual ~Node2() override = default;
	private:
		const ValueT value_;
	};
}

#endif /* defined(__clojure_cpp__Node__) */
