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
	class Node;
	
	template <typename ValueT>
	class Node2;
	
	typedef std::shared_ptr<const Node> NodePtr;
	
//	template <typename ValueT>
//	using Node2Ptr = std::shared_ptr<const Node2<ValueT>>;
	
	template <typename NodeT = Node>
	NodePtr MakeNodePtr(NodeT node = {}) { return std::make_shared<const NodeT>(node); }
	
	template <typename ValueT>
	NodePtr MakeNode2Ptr(ValueT value, NodePtr next = nullptr) { return MakeNodePtr(Node2<ValueT>(value, next)); }
	
	typedef std::function<NodePtr(NodePtr)> NodeFn; // should take a const Node* param instead of NodePtr for efficiency ?
	
	class Node {
	public:
		Node(); ///< nil node
		
		NodePtr Next() const { return next_; }
		
		virtual NodePtr Eval() const; ///< by default just evals to nil
		
		virtual std::string Print() const; ///< nil
		virtual std::string DebugPrint(int indent = 0) const; ///< 'nil'
		
		virtual std::string ReadableTypeName() const; ///< returns node type for debugging purposes. Default implementation just uses RTTI type_info
		
		virtual operator bool() const; // default implementation returns nil, since base class is empty node
		
		virtual const std::type_info& ValueTypeInfo() const { return typeid(nullptr); }
		
		virtual operator NodePtr() const {
			return MakeNodePtr(*this);
		}
		
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
				throw std::runtime_error { "Not a function: " + ReadableTypeName() + " is not a function. " };
			}
			return MakeNodePtr(*this);
		}
		
		virtual std::string DebugPrint(int indent = 0) const override {
			std::ostrstream os;
			for (int i = 0; i < indent; i++) {
				os << "\t";
			}
			os << ReadableTypeName() << " = " << std::endl;
			for (int i = 0; i < indent + 1; i++) {
				os << "\t";
			}
			os << value_;
			
			if (Next()) os << std::endl << ", next_ = " << Next()->DebugPrint(indent+1);

			os << std::endl;
			return os.str();
		}
		
		virtual std::string Print() const override {
			std::ostrstream os;
			os << value_;
			return os.str();
		}
		
		virtual operator bool() const override {
			return value_;
		}
		
		virtual const std::type_info& ValueTypeInfo() const override {
			return typeid(value_);
		}
		
		virtual operator NodePtr() const override {
			return MakeNodePtr(*this);
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

	static const NodePtr NilNode = MakeNodePtr(Node{});
}

#endif /* defined(__clojure_cpp__Node__) */
