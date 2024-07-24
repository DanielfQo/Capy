#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "paralelo.cpp"

int main() {
    std::ifstream inputFile("expr1.txt");
    if (!inputFile.is_open()) {
        std::cout << "Error al abrir el archivo expr1.txt" << std::endl;
        return 1;
    }

    int n1 = 1;
    std::string expression;
    while (std::getline(inputFile, expression)) {
        auto start1 = std::chrono::high_resolution_clock::now();
        try {
            double  result = evaluarPosfijaPila(expression);
        } catch (const std::exception& e) {
            std::cout << "Error al evaluar la expresión (" << expression << "): " << e.what() << std::endl;
        }
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double > duration1 = end1 - start1;
        //std::cout << n1 << " " << duration1.count() << std::endl;
        n1++;
    }

    inputFile.clear(); 
    inputFile.seekg(0); 

    int n2 = 1;
    while (std::getline(inputFile, expression)) {
        auto start2 = std::chrono::high_resolution_clock::now();
        try {
            double result = evaluarPosfijaParalelo(expression);
        } catch (const std::exception& e) {
            std::cout << "Error al evaluar la expresión (" << expression << "): " << e.what() << std::endl;
        }
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double > duration2 = end2 - start2;
        std::cout << n2 << " " << duration2.count() << std::endl;
        n2++;
    }


    return 0;
}