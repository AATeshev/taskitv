class Node
{
public:
	virtual double Calculate() const = 0;
	virtual void Print(std::ostream& os, unsigned int indent) const = 0;
	virtual ~Node() = default;
};

Node* CreateNumber(double value);

Node* OpDivision(Node* lvalue, Node* rvalue);

Node* OpMultiplication(Node* lvalue, Node* rvalue);

Node* OpSubtraction(Node* lvalue, Node* rvalue);

Node* OpAddition(Node* lvalue, Node* rvalue);

int CheckMain();
