
#include <iostream>
#include <memory>

template<typename T>
class Operation {
	public:
		std::shared_ptr<Operation> left = nullptr;
		std::shared_ptr<Operation> right = nullptr;
		T value;
		
		Operation() = default;
		virtual ~Operation() {
			
		}
		
		operator T&() {
			return value;
		}
		operator const T&() {
			return value;
		}
		operator T&&() {
			return std::move(value);
		}
		
		virtual T eval() = 0;
};

template<typename T>
class Add : virtual public Operation<T> {
	public:
		Add() = default;
		virtual T eval() {
			T result;
			
			if(this->left) result += this->left->eval();
			if(this->right) result += this->right->eval();
			
			return result;
		}
};

template<typename T>
class Subtract : virtual public Operation<T> {
	public:
		Subtract() = default;
		virtual T eval() {
			T result;
			
			if(this->left) result += this->left->eval();
			if(this->right) result -= this->right->eval();
			
			return result;
		}
};

template<typename T>
class Multiply : virtual public Operation<T> {
	public:
		Multiply() = default;
		virtual T eval() {
			T result;
			
			if(this->left) result += this->left->eval();
			if(this->right) result *= this->right->eval();
			
			return result;
		}
};

template<typename T>
class Divide : virtual public Operation<T> {
	public:
		Divide() = default;
		virtual T eval() {
			T result;
			
			if(this->left) result += this->left->eval();
			if(this->right) result /= this->right->eval();
			
			return result;
		}
};

template<typename T>
class Constant : virtual public Operation<T> {
	public:
		Constant() = default;
		Constant(const T& value) {
			this->value = value;
		}
		Constant(T&& value) {
			this->value = std::move(value);
		}
		virtual T eval() {
			return this->value;
		}
};

template<typename T, typename U>
T Cast(U* p) {
	return static_cast<T>(p);
}

int main() {
	std::string a = "100 + 200 * (300 / 400) ";
	std::cout <<
		std::shared_ptr<Operation<double>>(
			Cast<Operation<double>*>(
				new Constant<double>(10)
			)
		)->eval()
	<< std::endl;
	return 0;
}
