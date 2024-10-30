#include<iostream>
#include<string>

using namespace std;
struct Node {
	int coefficient;
	int exponent;
	Node* next;
	Node(int coefficient, int exponent)
	{
		this->coefficient = coefficient;
		this->exponent = exponent; 
		next = nullptr;
	}
};
class Polynomial
{
private:
	Node* head = nullptr;
	int maxPow = 0;
public:
	void createPolynomial(int coeff, int exp) {
		Node* newNode = new Node(coeff, exp);

		if (head == nullptr || head->exponent < exp) {
			newNode->next = head;
			head = newNode;
			return;
		}

		Node* current = head;
		Node* prev = nullptr;

		while (current != nullptr && current->exponent >= exp) {
			if (current->exponent == exp) {
				current->coefficient += coeff;
				if (current->coefficient == 0) {
					if (prev) {
						prev->next = current->next; 
					}
					else {
						head = current->next;
					}
					delete current;
				}
				delete newNode; 
				return;
			}
			prev = current;
			current = current->next;
		}
		newNode->next = current;
		if (prev) {
			prev->next = newNode;
		}
	}
	void display() {
		if (head == nullptr) {
			cout << "Polynomial is Empty\n\n";
			return;
		}

		Node* current = head;
		bool isFirstTerm = true;

		while (current != nullptr) {
			if (current->coefficient != 0) { 
				if (isFirstTerm) {
					cout << current->coefficient << "x^" << current->exponent;
					isFirstTerm = false;
				}
				else {
					if (current->coefficient > 0) {
						cout << " + " << current->coefficient << "x^" << current->exponent;
					}
					else {
						cout << " - " << abs(current->coefficient) << "x^" << current->exponent;
					}
				}
			}
			current = current->next;
		}
		cout << endl;
	}


	bool isEmpty()
	{
		return (head == nullptr);
	}
	Polynomial operator*(const Polynomial& other)
	{
		Node* currentp1 = head;
		Polynomial result;

		if (currentp1 == nullptr || other.head == nullptr)
		{
			cout << "Polynomials are EMPTY!\n";
			cout << "Enter polynomials by selecting 1 for polynomial 1 and 2 for polynomial 2!";
			return result;
		}

		while (currentp1 != nullptr)
		{
			Node* currentp2 = other.head;

			while (currentp2 != nullptr)
			{
				int newCoeff = currentp1->coefficient * currentp2->coefficient;
				int newExp = currentp1->exponent + currentp2->exponent;

				result.createPolynomial(newCoeff, newExp); 

				currentp2 = currentp2->next;
			}

			currentp1 = currentp1->next;
		}

		return result;
	}


	Polynomial operator-(const Polynomial& other)
	{
		Node* currentp1 = head;
		Node* currentp2 = other.head;
		Polynomial result;

		if (currentp1 == nullptr || currentp2 == nullptr)
		{
			cout << "Polynomials are EMPTY!\n";
			cout << "Enter polynomials by selecting 1 for polynomial 1 and 2 for polynomial 2!";
			return result;
		}
		while (currentp1 != nullptr && currentp2 != nullptr)
		{
			if (currentp1->exponent == currentp2->exponent)
			{
				result.createPolynomial(currentp1->coefficient - currentp2->coefficient, currentp1->exponent);
				currentp1 = currentp1->next;
				currentp2 = currentp2->next;
				continue;
			}
			if (currentp1->exponent > currentp2->exponent)
			{
				result.createPolynomial(currentp1->coefficient, currentp1->exponent);
				currentp1 = currentp1->next;
				continue;
			}
			if (currentp1->exponent < currentp2->exponent)
			{
				result.createPolynomial(-currentp2->coefficient, currentp2->exponent);
				currentp2 = currentp2->next;
			}

		}
		while (currentp1 != nullptr)
		{

			result.createPolynomial(currentp1->coefficient, currentp1->exponent);
			currentp1 = currentp1->next;


		}
		while (currentp2 != nullptr)
		{

			result.createPolynomial(-currentp2->coefficient, currentp2->exponent);
			currentp2 = currentp2->next;


		}
		cout << "\n";
		return result;
	}
	Polynomial operator+(const Polynomial& other)
	{
		Node* currentp1 = head;
		Node* currentp2 = other.head;
		Polynomial result;

		if (currentp1==nullptr || currentp2==nullptr)
		{
			cout << "Polynomials are EMPTY!\n";
			cout << "Enter polynomials by selecting 1 for polynomial 1 and 2 for polynomial 2!";
			return result;
		}
		while (currentp1!= nullptr && currentp2 != nullptr)
		{
			if (currentp1->exponent == currentp2->exponent)
			{
				result.createPolynomial(currentp1->coefficient + currentp2->coefficient, currentp1->exponent);
				currentp1 = currentp1->next;
				currentp2 = currentp2->next;
				continue;
			}
			if (currentp1->exponent > currentp2->exponent)
			{
				result.createPolynomial(currentp1->coefficient, currentp1->exponent);
				currentp1 = currentp1->next;
				continue;
			}
			if (currentp1->exponent < currentp2->exponent)
			{
				result.createPolynomial(currentp2->coefficient, currentp2->exponent);
				currentp2 = currentp2->next;
			}
			
		}
		while (currentp1 != nullptr)
		{

			result.createPolynomial(currentp1->coefficient, currentp1->exponent);
			currentp1 = currentp1->next;
		}
		while (currentp2 != nullptr)
		{

			result.createPolynomial(currentp2->coefficient, currentp2->exponent);
				currentp2 = currentp2->next;
		}
		cout << "\n";
		return result;
	}
	float evaluatePolynomial(int x)
	{
		
		Node* current = head;
		float result= 0.0;
		while (current != nullptr)
		{
			result += current->coefficient * pow(x, current->exponent);
			current = current->next;
 		}
		return result;
	}
};
void clearScreen() {
#ifdef _WIN32
	system("cls"); 
#endif
}
int main()
{
	Polynomial p1, p2, AdditionResult, multiplicationResult, subtractionResult;
	string choice;
	int coeff = 0, exp = 0;
	cout << "******************Choose Options from the following****************\n";
	do
	{
		cout << "1. To insert a term for polynomial 1\n2. To insert a term for polynomial 2\n3. To Add both Polynomials\n4. To Multiply both Polynomials\n5. To Subtract both Polynomials\n6. To perform evaluation\nEnter exit to exit\n";
		cout << "\n-------------------------------------------------------------------------------------------------------\n";
		getline(cin, choice);
		if (choice == "1")
		{
			cout << "Enter Coefficient for polynomial 1: ";
			while (true)
			{
				if (cin >> coeff)
				{
					if (coeff != 0)
					{
						break;
					}
					if (coeff == 0)
					{
						cout << "Coefficient cant be zero\n";
					}
					else
					{
						cout << "Enter a valid integer\n ";
					}
				}
				else
				{
					cout << "Enter a valid integer!\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}
			cout << "Enter Exponent for polynomial 1: ";
			while (true)
			{
				if (cin >> exp)
				{
					if (exp > 0)
					{
						break;
					}
					if (exp == 0)
					{
						break;
					}
					else
					{
						cout << "Enter a positive integer\n ";
					}
				}
				else
				{
					cout << "Enter a integer!\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}
			p1.createPolynomial(coeff, exp);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

			cout << "\nPolynomial 1 is: ";
			p1.display();
			cout << "\nPolynomial 2 is: ";
			p2.display();
			cout << "if you want to add more terms for polynomial 1\nPress 1 Again \n";
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

		}
		else if (choice == "2")
		{
			cout << "Enter Coefficient for polynomial 2: ";
			while (true)
			{
				if (cin >> coeff)
				{
					if (coeff != 0)
					{
						break;
					}
					if (coeff == 0)
					{
						cout << "Coefficient cant be zero\n";
					}
					else
					{
						cout << "Enter a positive integer\n ";
					}
				}
				else
				{
					cout << "Enter a integer!\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}
			cout << "Enter Exponent for polynomial 2: ";
			while (true)
			{
				if (cin >> exp)
				{
					if (exp > 0)
					{
						break;
					}
					if (exp == 0)
					{
						break;
					}
					else
					{
						cout << "Enter a positive integer\n ";
					}
				}
				else
				{
					cout << "Enter a integer!\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}
			p2.createPolynomial(coeff, exp);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

			cout << "\nPolynomial 1 is: ";
			p1.display();
			cout << "\nPolynomial 2 is: ";
			p2.display();
			cout << "if you want to add more terms for polynomial 2\nPress 2 Again \n";
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

		}
		else if (choice == "3")
		{
			AdditionResult = p1.operator+(p2);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

			cout << "\nPolynomial 1 is: ";
			p1.display();
			cout << "\nPolynomial 2 is: ";
			p2.display();
			cout << endl;
			cout << "Result of Addition:  ";
			AdditionResult.display();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

		}
		else if (choice == "4")
		{
			multiplicationResult = p1.operator*(p2);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

			cout << "\nPolynomial 1 is: ";
			p1.display();
			cout << "\nPolynomial 2 is: ";
			p2.display();
			cout << "Result of Multiplication:  ";

			multiplicationResult.display();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

		}
		else if (choice == "5")
		{
			subtractionResult = p1.operator-(p2);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

			cout << "\nPolynomial 1 is: ";
			p1.display();
			cout << "\nPolynomial 2 is: ";
			p2.display();
			cout << "Result of Subtraction:  ";

			subtractionResult.display();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

		}
		else if (choice == "6")
		{
			float result;
			int x = 0;
			cout << "Enter a value for x: ";
			while (true)
			{
				if (cin >> x)
				{
					break;
				}
				else
				{
					cout << "Enter a valid integer for x: ";
					cin.clear();
					cin.ignore(1024, '\n');
				}
			}
			cout << "\nPress 1 to evaluate polynomial 1\t";
			cout << "Press 2 to evaluate polynomial 2: ";
			cin.ignore();
			getline(cin, choice);
			if (choice == "1")
			{
				if (p1.isEmpty())
				{
					cout << "\nPolynomial has no term to evaluate!\n";
					continue;
				}
				result = p1.evaluatePolynomial(x);
				clearScreen();
				cout << "\n-------------------------------------------------------------------------------------------------------\n";
				cout << "\nPolynomial 1 is: ";
				p1.display();
				cout << "\nPolynomial 2 is: ";
				p2.display();
				cout << "-------------------------------------------------------------------------------------------------------\n";
				cout << "Evaluated value of polynomial 1, when x =" << x << " is: " << result<<endl;
				cout << "\n-------------------------------------------------------------------------------------------------------\n";
				continue;
			}
			if (choice == "2")
			{
				if (p2.isEmpty())
				{
					cout << "\nPolynomial has no term to evaluate!\n";
					continue;
				}
				result = p2.evaluatePolynomial(x);
				clearScreen();
				cout << "\n-------------------------------------------------------------------------------------------------------\n";
				cout << "\nPolynomial 1 is: ";
				p1.display();
				cout << "\nPolynomial 2 is: ";
				p2.display();
				cout << "Evaluated value of polynomial 2, when x =" << x << " is: " << result;
				cout << "\n-------------------------------------------------------------------------------------------------------\n";

				continue;
			}
			else
			{
				cout << "\n-------------------------------------------------------------------------------------------------------\n";
				cout << "Invalid Choice!";
				cout << "\n-------------------------------------------------------------------------------------------------------\n";

			}
		}
		else
		{
			cout << "Invalid Choice Entered!\n";
			cin.ignore();
		}
		cin.ignore();
	} while (true);
}