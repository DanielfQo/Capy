#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <map>
#include <stack>
#include <algorithm>

std::map<std::string, std::function<double(double, double)>> operations = {
    {"+", std::plus<double>()},
    {"-", std::minus<double>()},
    {"*", std::multiplies<double>()},
    {"/", std::divides<double>()}
};

std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::istringstream iss(expression);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

double evaluate(const std::string& op, double a, double b) {
    return operations[op](a, b);
}

double evaluate_expression(const std::vector<std::string>& tokens);

double evaluate_subexpression(const std::string& expression) {
    auto tokens = tokenize(expression);
    return evaluate_expression(tokens);
}

double evaluate_expression(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<std::string> operators;

    // Algoritmo Shunting-yard para manejar paréntesis y precedencia de operadores
    for (const auto& token : tokens) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            output.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && operators.top() != "(" &&
                   (token == "+" || token == "-" ||
                    (token == "*" || token == "/" && operators.top() != "+" && operators.top() != "-"))) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    // Evaluar expresión en notación polaca inversa (RPN)
    std::stack<double> values;
    for (const auto& token : output) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            values.push(std::stod(token));
        } else {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(evaluate(token, a, b));
        }
    }

    return values.top();
}

double evaluate_expression(const std::string& expression) {
    auto tokens = tokenize(expression);

    // Evaluar multiplicación y división en paralelo
    std::vector<std::future<void>> futures;
    for (size_t i = 1; i < tokens.size() - 1; i += 2) {
        if (tokens[i] == "*" || tokens[i] == "/") {
            futures.push_back(std::async(std::launch::async, [&tokens, i]() {
                double a = std::stod(tokens[i - 1]);
                double b = std::stod(tokens[i + 1]);
                double result = evaluate(tokens[i], a, b);
                tokens[i - 1] = std::to_string(result);
                tokens[i] = tokens[i + 1] = ""; // Marcar como evaluados
            }));
        }
    }

    // Esperar a que todas las evaluaciones paralelas terminen
    for (auto& future : futures) {
        future.get();
    }

    // Eliminar tokens vacíos
    tokens.erase(std::remove(tokens.begin(), tokens.end(), ""), tokens.end());

    // Evaluar suma y resta secuencialmente
    while (tokens.size() > 1) {
        double a = std::stod(tokens[0]);
        std::string op = tokens[1];
        double b = std::stod(tokens[2]);
        double result = evaluate(op, a, b);
        tokens[0] = std::to_string(result);
        tokens.erase(tokens.begin() + 1, tokens.begin() + 3);
    }

    return std::stod(tokens[0]);
}

int main() {
    std::string expression = "3 + (5 * 2) - (8 / 4)";
    double result = evaluate_expression(expression);
    std::cout << "El resultado de la expresión '" << expression << "' es: " << result << std::endl;
    return 0;
}

