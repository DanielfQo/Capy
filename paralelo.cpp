#include <iostream>
#include <sstream>
#include <stack>
#include <thread>
#include <vector>
#include <mutex>
#include <future>
#include <stdexcept>

std::mutex mtx;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: throw std::runtime_error("Invalid operator");
    }
}

int evaluateExpression(std::string tokens) {
    int i;
    std::stack<int> values;
    std::stack<char> ops;

    for (i = 0; i < tokens.length(); i++) {
        if (tokens[i] == ' ') continue;
        
        if (tokens[i] == '(') {
            ops.push(tokens[i]);
        } else if (isdigit(tokens[i])) {
            int val = 0;
            while (i < tokens.length() && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        } else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop();
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

void parallelEvaluate(std::vector<std::string> expressions, std::vector<int>& results, int index) {
    results[index] = evaluateExpression(expressions[index]);
}

int main() {
    std::vector<std::string> expressions = {
        "10 + 2 * 6",
        "100 * 2 + 12",
        "100 * ( 2 + 12 )",
        "100 * ( 2 + 12 ) / 14"
    };

    std::vector<int> results(expressions.size());
    std::vector<std::thread> threads;

    for (int i = 0; i < expressions.size(); i++) {
        threads.emplace_back(parallelEvaluate, expressions, std::ref(results), i);
    }

    for (auto& th : threads) {
        th.join();
    }

    for (int i = 0; i < results.size(); i++) {
        std::cout << "Resultado de \"" << expressions[i] << "\": " << results[i] << std::endl;
    }

    return 0;
}
