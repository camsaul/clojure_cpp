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
	
	template <typename ValueT, typename PrintCastT>
	class Node2;
	
	typedef std::shared_ptr<const Node> NodePtr; // make this a custom class with ++ iterator behavior ?
	
//	template <typename ValueT>
//	using Node2Ptr = std::shared_ptr<const Node2<ValueT>>;
	
	 /// Make NodePtr by passing a node
	template <typename NodeT = Node>
	NodePtr NodePtrWithNode(NodeT node = {}) { return std::make_shared<const NodeT>(node); }
	
	/// Make a NodePtr by passing a value and optional next node
	template <typename ValueT, typename NextPtrT = NodePtr>
	NodePtr NodePtrWithValue(ValueT value, NextPtrT next = nullptr) { return NodePtrWithNode(Node2<ValueT, ValueT>(value, next)); }
	
	/// Make a NodePtr with a value for tail and value to be placed inside of a Node2 for next
	template <typename Value1T, typename Value2T>
	NodePtr NodePtrWithValues(Value1T v1, Value2T v2) {
		auto next = NodePtrWithValue<Value2T>(v2);
		return NodePtrWithNode(Node2<Value1T, Value1T>(v1, next));
	}
	
	typedef std::function<NodePtr(NodePtr)> NodeFn; // should take a const Node* param instead of NodePtr for efficiency ? Or just a plain node ?
	
	class Node {
	public:
		Node(); ///< nil node
		
		NodePtr Next() const { return next_; }
		
		virtual NodePtr Eval() const; ///< by default just evals to nil
		
		virtual std::string Print() const; ///< nil
		virtual std::string DebugPrint(int indent = 0) const; ///< 'nil'
		
		virtual std::string PrintNext() const;
		
		virtual std::string ReadableTypeName() const; ///< returns node type for debugging purposes. Default implementation just uses RTTI type_info
		
		virtual operator bool() const; // default implementation returns nil, since base class is empty node
		
		virtual const std::type_info& ValueTypeInfo() const { return typeid(nullptr); }
		
		virtual operator NodePtr() const {
			return *this;
		}
		
		virtual ~Node() = default;
	
	protected:
		template <typename NodeT>
		Node(NodeT n):
			next_ { n }
		{}
		
		Node(NodePtr next);
		
	private:
		NodePtr next_;
	};
	
	template <typename ValueT, typename PrintCastT = ValueT>
	class Node2 : public Node {
	public:
		Node2(const ValueT& value, NodePtr next = nullptr):
			Node { next },
			value_ { value }
		{}
				
		template <typename Value2T>
		Node2(const ValueT& value, const Value2T& value2):
			Node { NodePtrWithValue<Value2T>(value2) },
			value_ { value }
		{}
		
		const ValueT& Value() const { return value_; }
		
		virtual NodePtr Eval() const override {
			if (Next()) {
				throw std::runtime_error { "Not a function: " + ReadableTypeName() + " is not a function. " };
			}
			return *this;
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
			os << (PrintCastT)value_;
			
			if (Next()) os << std::endl << ", next_ = " << Next()->DebugPrint(indent+1);

			os << std::endl;
			return os.str();
		}
		
		virtual std::string Print() const override {
			std::ostrstream os;
			os << (PrintCastT)value_;
			return os.str();
		}
		
		virtual operator bool() const override {
			return bool(value_);
		}
		
		virtual const std::type_info& ValueTypeInfo() const override {
			return typeid(value_);
		}
		
		virtual operator NodePtr() const override {
			return NodePtrWithNode(*this);
		}
		
		virtual ~Node2() override = default;
	private:
		const ValueT value_; // rename head instead of value ?
	};
	static const NodePtr NilNode = NodePtrWithNode(Node{});
	
	class FnNode : public Node2<NodeFn, int> {
	public:
		FnNode (NodeFn fn, NodePtr args):
			Node2(fn, args)
		{}
		
		virtual std::string DebugPrint(int indent = 0) const override {
			std::ostrstream os;
			for (int i = 0; i < indent; i++) {
				os << "\t";
			}
			os << ReadableTypeName() << " = " << std::endl;
			for (int i = 0; i < indent + 1; i++) {
				os << "\t";
			}
			os << Print();
			
			if (Next()) os << std::endl << ", next_ = " << Next()->DebugPrint(indent+1);
			
			os << std::endl;
			return os.str();
		}
		
		virtual std::string Print() const override {
			return "<fn " + ReadableTypeName() + ">: " + PrintNext();
		}
	
		virtual NodePtr Eval() const override {
			return Next() ? Value()(Next()) : *this;
		}
	};
}

#endif /* defined(__clojure_cpp__Node__) */
