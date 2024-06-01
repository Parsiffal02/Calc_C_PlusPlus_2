#include <iostream> // Подключение библиотеки для ввода-вывода
#include <string> // Подключение библиотеки для работы со строками
#include <sstream> // Подключение библиотеки для работы с потоками строк
#include <exception> // Подключение библиотеки для обработки исключений
#include <stdexcept> // Подключение библиотеки для стандартных исключений

// Узел связного списка
class Node {
public:
    int data; // Данные узла
    Node* next; // Указатель на следующий узел

    // Конструктор узла, инициализирующий данные и указатель на следующий узел
    Node(int value) : data(value), next(nullptr) {}
};

// Связный список для реализации стека
class LinkedList {
private:
    Node* head; // Голова списка

public:
    // Конструктор списка, инициализирующий голову как nullptr
    LinkedList() : head(nullptr) {}

    // Добавление элемента в начало списка (в стек)
    void push(int value) {
        Node* newNode = new Node(value); // Создание нового узла
        newNode->next = head; // Установка указателя нового узла на текущую голову
        head = newNode; // Обновление головы списка на новый узел
    }

    // Извлечение элемента из начала списка (из стека)
    int pop() {
        if (head == nullptr) { // Проверка, пуст ли список
            throw std::out_of_range("Stack underflow"); // Бросить исключение, если список пуст
        }
        Node* temp = head; // Сохранить текущую голову
        head = head->next; // Обновить голову на следующий узел
        int poppedValue = temp->data; // Сохранить значение извлеченного узла
        delete temp; // Удалить извлеченный узел
        return poppedValue; // Вернуть значение извлеченного узла
    }

    // Проверка, пуст ли стек
    bool isEmpty() const {
        return head == nullptr; // Возвращает true, если голова равна nullptr
    }

    // Деструктор для очистки памяти
   // ~LinkedList() {
   //     while (!isEmpty()) { // Пока список не пуст
    //        pop(); // Извлекать элементы из списка, освобождая память
  //      }
  //  }
};

// Стек на основе связного списка
class Stack {
private:
    LinkedList list; // Связный список для хранения элементов

public:
    // Добавление элемента в стек (использует метод push связного списка)
    void push(int value) {
        list.push(value);
    }

    // Извлечение элемента из стека (использует метод pop связного списка)
    int pop() {
        return list.pop();
    }

    // Проверка, пуст ли стек (использует метод isEmpty связного списка)
    bool isEmpty() const {
        return list.isEmpty();
    }
};

// Калькулятор для выполнения операций в постфиксной нотации
class Calculator {
private:
    Stack stack; // Стек для хранения операндов

    // Преобразование десятичного числа в двоичное
    std::string toBinary(int num) {
        if (num == 0) return "0"; // Если число равно 0, вернуть "0"
        std::string binary; // Строка для хранения двоичного представления числа
        while (num > 0) { // Пока число больше 0
            binary = (num % 2 == 0 ? "0" : "1") + binary; // Добавить остаток от деления на 2 в начало строки
            num /= 2; // Разделить число на 2
        }
        return binary; // Вернуть двоичное представление числа
    }

public:
    // Выполнение операции над двумя числами
    int performOperation(char operation, int operand1, int operand2) {
        switch (operation) { // Выбор операции по символу
            case '+': return operand1 + operand2; // Сложение
            case '-': return operand1 - operand2; // Вычитание
            case '*': return operand1 * operand2; // Умножение
            default: throw std::invalid_argument("Invalid operation"); // Бросить исключение для неизвестной операции
        }
    }

    // Обработка постфиксного выражения
    void evaluatePostfix(const std::string& expression) {
        std::istringstream iss(expression); // Создать поток строк из выражения
        std::string token; // Переменная для хранения текущего токена

        while (iss >> token) { // Чтение токенов из потока строк
            if (isdigit(token[0])) { // Если токен - число (первый символ - цифра)
                stack.push(std::stoi(token)); // Преобразовать токен в целое число и добавить в стек
            } else { // Если токен - оператор
                if (stack.isEmpty()) throw std::runtime_error("Invalid expression"); // Проверить, пуст ли стек и бросить исключение, если да
                int operand2 = stack.pop(); // Извлечь второй операнд из стека
                if (stack.isEmpty()) throw std::runtime_error("Invalid expression"); // Проверить, пуст ли стек и бросить исключение, если да
                int operand1 = stack.pop(); // Извлечь первый операнд из стека
                int result = performOperation(token[0], operand1, operand2); // Выполнить операцию над операндами
                stack.push(result); // Добавить результат операции в стек
            }
        }

        if (stack.isEmpty()) throw std::runtime_error("Invalid expression"); // Проверить, пуст ли стек и бросить исключение, если да
        int finalResult = stack.pop(); // Извлечь финальный результат из стека
        if (!stack.isEmpty()) throw std::runtime_error("Invalid expression"); // Проверить, пуст ли стек и бросить исключение, если нет

        std::cout << "Result in decimal: " << finalResult << std::endl; // Вывести результат в десятичной системе счисления
        std::cout << "Result in binary: " << toBinary(finalResult) << std::endl; // Вывести результат в двоичной системе счисления
    }
};

int main() { // Определение основной функции программы
    try { // Начало блока обработки исключений
        Calculator calculator; // Создание объекта калькулятора
        std::string expression; // Объявление строки для хранения постфиксного выражения

        std::cout << "Enter postfix expression: "; // Вывод приглашения для ввода постфиксного выражения
        std::getline(std::cin, expression); // Чтение всей строки с постфиксным выражением из стандартного ввода

        calculator.evaluatePostfix(expression); // Вызов метода для вычисления постфиксного выражения
    } catch (const std::exception& e) { // Ловля всех исключений типа std::exception и его производных
        std::cerr << "Error: " << e.what() << std::endl; // Вывод сообщения об ошибке в стандартный поток ошибок
    }

    return 0; // Возврат 0, указывающий на успешное завершение программы
}