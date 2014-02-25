//
//  Node.h
//  clojure-cpp
//
//  Created by Cam Saul on 2/24/14.
//  Copyright (c) 2014 Cam Saul. All rights reserved.
//

#ifndef __clojure_cpp__Node__
#define __clojure_cpp__Node__

#include <exception>
#include <memory>
#include <iostream>
#include <strstream>

namespace clojure {
	std::string readable_name(const std::type_info& typeInfo);

	class Node;
	typedef std::shared_ptr<const Node> NodePtr;
	
	template <typename NodeT>
	NodePtr MakeNodePtr(NodeT node) { return std::make_shared<const NodeT>(node); }
	
	class Node {
	public:
		Node(); ///< nil node
		
		NodePtr Next() const { return next_; }
		
		virtual NodePtr Eval() const; ///< by default just evals to nil
		
		virtual std::string Print() const; ///< 'nil'
		
		virtual ~Node() = default;
	
	protected:
		template <typename NodeT>
		Node(NodeT n):
			next_ { MakeNodePtr<NodeT>(n) }
		{}
		
		Node(NodePtr next);
		
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
		
		virtual NodePtr Eval() const override {
			if (Next()) {
				throw std::runtime_error { "Not a function: " + readable_name(typeid(*this)) + " is not a function. " };
			}
			return MakeNodePtr(*this);
		}
		
		virtual std::string Print() const override {
			std::ostrstream os;
			os << value_;
			return os.str();
		}
		
		virtual ~Node2() override = default;
	private:
		const ValueT value_;
	};
	
//	template <> class Node2<int> : public Node {
//	public:
//		Node2(int value, NodePtr next = nullptr):
//			Node { next },
//			value_ { value }
//		{}
//		
//		template <typename NodeT>
//		Node2(int value, NodeT next):
//			Node { MakeNodePtr<NodeT>(next) },
//			value_ { value }
//		{}
//		
//		int Value() const { return value_; }
//
//		virtual void Eval() const {
//			std::cout << "Int: " << std::to_string(Value()) << std::endl;
//			if (Next()) Next()->Eval();
//		}
//	private:
//		const int value_;
//	};
}

#endif /* defined(__clojure_cpp__Node__) */
