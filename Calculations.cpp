#include <iostream>
#include <memory>
#include <functional>
#include "Calculations.h" 
#include <string>
#include <fstream>
#include <vector>

class Number : public Node
{
public:
	Number(double value) :value(value)
	{
	}

	double Calculate() const override
	{
		return (value);
	}
	virtual void Print(std::ostream& os, unsigned int indent = 0) const override
	{
		os << std::string(indent, ' ') << "Number(" << std::to_string(value) << ")" << std::endl;
	}
	
private:
	double value = 0;
};

class BinaryOperation : public Node
{
public:
	BinaryOperation(Node* lvalue, Node* rvalue, std::function <double(Node*, Node*)> op, std::string Name) :lvalue(lvalue), rvalue(rvalue), op(op), Name(Name)
	{
	}
	double Calculate() const override
	{
		return op(lvalue.get(), rvalue.get());
	}

	virtual void Print(std::ostream& os, unsigned int indent = 0) const override
	{
		os << std::string(indent, ' ') << Name << std::endl;
		indent+=2;
		lvalue->Print(os,indent);
		rvalue->Print(os,indent);
	}

	
protected:
	std::string Name = "BASE";
	std::function <double(Node*, Node*)> op;
	std::unique_ptr<Node> lvalue{};
	std::unique_ptr<Node> rvalue{};
};

class Addition : public BinaryOperation
{
public:
	Addition(Node* lvalue, Node* rvalue) : BinaryOperation(lvalue, rvalue, [](Node* lvalue, Node* rvalue) {return (lvalue->Calculate() + rvalue->Calculate()); }, "Addition")
	{
	}
};

class Subtraction : public BinaryOperation
{
public:
	Subtraction(Node* lvalue, Node* rvalue) : BinaryOperation(lvalue, rvalue, [](Node* lvalue, Node* rvalue) {return (lvalue->Calculate() - rvalue->Calculate()); }, "Subtraction")
	{
	}
};

class Multiplication : public BinaryOperation
{
public:
	Multiplication(Node* lvalue, Node* rvalue) : BinaryOperation(lvalue, rvalue, [](Node* lvalue, Node* rvalue) {return (lvalue->Calculate() * rvalue->Calculate()); }, "Multiplication")
	{
	}
};

class Division : public BinaryOperation
{
public:
	Division(Node* lvalue, Node* rvalue) : BinaryOperation(lvalue, rvalue, [](Node* lvalue, Node* rvalue) {return (lvalue->Calculate() / rvalue->Calculate()); }, "Division")
	{
	}
};


// для тестов
Node* CreateNumber(double value)
{
	return new Number(value);
}
Node* OpDivision(Node* lvalue, Node* rvalue)
{
	return new Division(lvalue, rvalue);
}
Node* OpMultiplication(Node* lvalue, Node* rvalue)
{
	return new Multiplication(lvalue, rvalue);
}
Node* OpSubtraction(Node* lvalue, Node* rvalue)
{
	return new Subtraction(lvalue, rvalue);
}
Node* OpAddition(Node* lvalue, Node* rvalue)
{
	return new Addition(lvalue, rvalue);
}


void WriteInFile(Node* p) {
	std::ofstream out;         
	out.open("OperationsResult.txt");     
	if (out.is_open())
	{
		p->Print(out,0);
	}
	out.close();
	std::cout << "\nFile has been written" << std::endl;
}


int CheckMain()
{
	std::cout << "\nAdditional main test result:\n";
	std::unique_ptr<Node> p{ new Division(new Addition(new Multiplication(new Number(5),new Number(2)),new Division(new Number(0),new Number(1))), new Subtraction(new Number(3),new Number(1))) };
    p->Print(std::cout,0);
	std::cout << p->Calculate();
	WriteInFile(p.get());
	p = nullptr;
	return 0;
} 


