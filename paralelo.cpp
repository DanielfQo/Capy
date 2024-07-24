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

// Función para convertir una expresión infija a postfija
std::string infixToPostfix(const std::string& infix) {
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
                operators.pop();  // Pop the '('
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
// Función para evaluar una expresión postfija secuencialmente
int evaluarPosfijaPila(const std::string& expresion) {
    std::stack<int> pila;
    std::string token;
    
    std::istringstream stream(expresion);
    
    while (stream >> token) {
        // Verifica si el token es un número entero
        bool esNumero = true;
        for (char c : token) {
            if (!std::isdigit(c) && c != '-') {
                esNumero = false;
                break;
            }
        }
        
        if (esNumero) {
            pila.push(std::stoi(token));
        } else {
            // De lo contrario, se asume que es un operador
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
            }
            
            pila.push(resultado);
        }
    }
    
    return pila.top();
}
// Mutex para la salida estándar
std::mutex output_mutex;

// Función para evaluar una expresión aritmética simple
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

double sumaParalela = 0;

// Función que ejecuta la evaluación y muestra el resultado
void process_expression(const std::vector<std::string>& expressions, int index) {
    const std::string& expression = expressions[index];
    try {
        double result = evaluate_expression(expression);
        sumaParalela += result;
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Resultado de la expresión " << index << " (" << expression << "): " << result << std::endl;
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Error al evaluar la expresión " << index << " (" << expression << "): " << e.what() << std::endl;
    }
}

// Función para evaluar expresiones en paralelo
void evaluarPosfijaParalelo(const std::vector<std::string>& expressions) {
    std::vector<std::thread> threads;
    for (int i = 0; i < expressions.size(); ++i) {
        threads.emplace_back(process_expression, std::cref(expressions), i);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    std::string infix_expression = "15+2*4*5+4+8 "; // Ejemplo de expresión en notación infija
    std::string postfix_expression = infixToPostfix(infix_expression);
    std::cout << "Expresión infija: " << infix_expression << std::endl;
    std::cout << "Expresión postfija: " << postfix_expression << std::endl;

    double result1 = evaluarPosfijaPila(postfix_expression);

    
    std::vector<std::string> parts = split_expression(infix_expression);
    
    evaluarPosfijaParalelo(parts);

    
    std::cout << "Resultado 1: " << result1 << std::endl;
    std::cout << "Resultado 2: " << sumaParalela << std::endl;

    return 0;
}
