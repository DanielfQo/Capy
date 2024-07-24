#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <cctype>
#include <functional>
#include <queue>
#include <stdexcept>
#include <stdlib.h>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


std::string infixToPostfix(std::string infix) {
    std::stack<char> operators;
    std::ostringstream postfix;
    bool wasOperand = false;
    std::string number;

    for (size_t i = 0; i < infix.length(); ++i) {
        char token = infix[i];

        if (isspace(token)) {
            continue;
        } else if (isdigit(token)) {
            number += token;
            wasOperand = true;
        } else {
            if (wasOperand) {
                postfix << number << ' ';
                number.clear();
                wasOperand = false;
            }

            if (token == '(') {
                operators.push(token);
            } else if (token == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix << operators.top() << ' ';
                    operators.pop();
                }
                operators.pop();  
            } else {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    postfix << operators.top() << ' ';
                    operators.pop();
                }
                operators.push(token);
            }
        }
    }

    if (wasOperand) {
        postfix << number << ' ';
    }

    while (!operators.empty()) {
        postfix << operators.top() << ' ';
        operators.pop();
    }

    return postfix.str();
}

double evaluarPosfijaPila(const std::string& infija_expresion) {
    std::string expresion = infixToPostfix(infija_expresion);

    std::cout << "Expresion: " << expresion << std::endl;

    std::stack<double> pila;
    std::string token;
    std::istringstream stream(expresion);

    while (stream >> token) {

        // Verifica si el token es un número
        bool esNumero = true;
        for (char c : token) {
            if (!std::isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (esNumero) {
            pila.push(std::stoi(token.c_str()));
        } else {
            // Asegúrate de que haya al menos dos operandos en la pila
            if (pila.size() < 2) {
                throw std::runtime_error("Expresión inválida: no hay suficientes operandos");
            }

            int operando2 = pila.top(); pila.pop();
            int operando1 = pila.top(); pila.pop();
            int resultado;

            if (token == "+") {
                resultado = operando1 + operando2;
            } else if (token == "-") {
                resultado = operando1 - operando2;
            } else if (token == "*") {
                resultado = operando1 * operando2;
            } else if (token == "/") {
                if (operando2 != 0) {
                    resultado = operando1 / operando2;
                } else {
                    throw std::runtime_error("División por cero");
                }
            } else {
                throw std::runtime_error("Operador no reconocido");
            }

            pila.push(resultado);
        }
    }

    // Asegúrate de que la pila tenga solo un elemento al final
    if (pila.size() != 1) {
        throw std::runtime_error("Expresión inválida: la pila tiene más de un elemento");
    }

    return pila.top();
}

int main() {
    std::string infix_expression = "6*1*3-6+9"; 

    double result1 = evaluarPosfijaPila(infix_expression);

    
    std::cout << "Resultado 1: " << result1 << std::endl;

    return 0;
}