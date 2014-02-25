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
	class Node {
	public:
		template <typename T>
		Node(T n):
			next_ { std::make_shared<const T>(n) }
		{}
		
		Node(std::shared_ptr<const Node> next);
		
		std::shared_ptr<const Node> Next() const { return next_; }
		
		virtual void Run() const;
		
		virtual ~Node() = default;
		
	private:
		std::shared_ptr<const Node> next_;
	};
	
	template <typename T>
	class Node2 : public Node {
	public:
		Node2(const T& value, std::shared_ptr<const Node> next = nullptr):
			Node { next },
			value_ { value }
		{}
		
		const T& Value() const { return value_; }
		
		virtual void Run() const override {
			std::cout << "Value: " << Value() << std::endl;
			if (Next()) Next()->Run();
		}
		
		virtual ~Node2() override = default;
	private:
		const T value_;
	};
}

#endif /* defined(__clojure_cpp__Node__) */
