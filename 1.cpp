#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

// Node class for Linked List
class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    void push(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    int pop() {
        if (head == nullptr) throw std::runtime_error("Stack underflow");
        int data = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

// Stack class using Linked List
class Stack {
private:
    LinkedList list;
public:
    void push(int data) {
        list.push(data);
    }

    int pop() {
        return list.pop();
    }

    bool isEmpty() const {
        return list.isEmpty();
    }
};

// Binary number class
class BinaryNumber {
private:
    std::string binaryStr;

    // Convert decimal to binary
    std::string decToBin(int num) const {
        if (num == 0) return "0";
        std::string result = "";
        while (num > 0) {
            result = (num % 2 == 0 ? "0" : "1") + result;
            num /= 2;
        }
        return result;
    }

    // Convert binary to decimal
    int binToDec(const std::string& binStr) const {
        int result = 0;
        for (char c : binStr) {
            result = result * 2 + (c - '0');
        }
        return result;
    }

public:
    BinaryNumber(int decimalNum) {
        binaryStr = decToBin(decimalNum);
    }

    BinaryNumber(const std::string& binaryStr) : binaryStr(binaryStr) {}

    int toDecimal() const {
        return binToDec(binaryStr);
    }

    std::string toBinaryString() const {
        return binaryStr;
    }

    // Addition of two binary numbers
    BinaryNumber operator+(const BinaryNumber& other) const {
        int sum = this->toDecimal() + other.toDecimal();
        return BinaryNumber(sum);
    }

    // Subtraction of two binary numbers
    BinaryNumber operator-(const BinaryNumber& other) const {
        int diff = this->toDecimal() - other.toDecimal();
        return BinaryNumber(diff);
    }

    // Multiplication of two binary numbers
    BinaryNumber operator*(const BinaryNumber& other) const {
        int prod = this->toDecimal() * other.toDecimal();
        return BinaryNumber(prod);
    }
};

// Postfix Calculator class
class PostfixCalculator {
private:
    Stack stack;

public:
    void evaluate(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token) {
            if (isdigit(token[0])) {
                stack.push(std::stoi(token));
            } else if (token == "+" || token == "-" || token == "*") {
                if (stack.isEmpty()) throw std::runtime_error("Invalid expression");

                int operand2 = stack.pop();
                if (stack.isEmpty()) throw std::runtime_error("Invalid expression");

                int operand1 = stack.pop();

                BinaryNumber binOp1(operand1);
                BinaryNumber binOp2(operand2);
                BinaryNumber result(0);

                if (token == "+") {
                    result = binOp1 + binOp2;
                } else if (token == "-") {
                    result = binOp1 - binOp2;
                    } else if (token == "*") {
                    result = binOp1 * binOp2;
                }

                stack.push(result.toDecimal());
            } else {
                throw std::runtime_error("Invalid token in expression");
            }
        }

        if (!stack.isEmpty()) {
            int result = stack.pop();
            if (!stack.isEmpty()) throw std::runtime_error("Invalid expression");

            BinaryNumber finalResult(result);
            std::cout << "Result in binary: " << finalResult.toBinaryString() << "\\n";
            std::cout << "Result in decimal: " << finalResult.toDecimal() << "\\n";
        } else {
            throw std::runtime_error("Invalid expression");
        }
    }
};

int main() {
    try {
        PostfixCalculator calculator;
        std::string expression;

        std::cout << "Enter a postfix expression: ";
        std::getline(std::cin, expression);

        calculator.evaluate(expression);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\\n";
    }

    return 0;
}