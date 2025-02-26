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

std::vector<std::string> split_expression(const std::string& expression) {
    std::vector<std::string> result;
    std::string temp;
    for (char ch : expression) {
        if (ch == '+' || ch == '-') {
            if (!temp.empty()) {
                result.push_back(temp);
                temp.clear();
            }
            temp += ch;
        } else {
            temp += ch;
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
    }
    return result;
}

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
            pila.push(std::stod(token.c_str()));
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
// Mutex para la salida estándar
std::mutex output_mutex;

double evaluate_expression(const std::string& expression) {
    std::istringstream iss(expression);
    double result = 0.0;
    double number;
    char op = '+';
    while (iss >> number) {
        if (op == '+') {
            result += number;
        } else if (op == '-') {
            result -= number;
        } else if (op == '*') {
            result *= number;
        } else if (op == '/') {
            if (number == 0) {
                throw std::runtime_error("División por cero");
            }
            result /= number;
        }
        iss >> op;
    }
    return result;
}



void process_expression(std::vector<std::string> expressions, int index, double& sumaParalela) {
    const std::string& expression = expressions[index];
    try {
        double result = evaluate_expression(expression);
        sumaParalela += result;
        std::lock_guard<std::mutex> lock(output_mutex);
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(output_mutex);
    }
}

double evaluarPosfijaParalelo( std::string expressions) {
    std::vector<std::string> parts = split_expression(expressions);
    double sumaParalela = 0;

    std::vector<std::thread> threads;
    for (int i = 0; i < parts.size(); ++i) {
        threads.emplace_back(process_expression, std::cref(parts), i, std::ref(sumaParalela));
    }

    for (auto& thread : threads) {
        thread.join();
    }
    return sumaParalela;
}

/*
int main() {
    std::string infix_expression = "7+7+7+7+7+7+7+7"; 
    std::cout << "Expresión infija: " << infix_expression << std::endl;

    double result1 = evaluarPosfijaPila(infix_expression);
    double result2 = evaluarPosfijaParalelo(infix_expression);

    
    std::cout << "Resultado 1: " << result1 << std::endl;
    std::cout << "Resultado 2: " << result2 << std::endl;

    return 0;
}
*/
