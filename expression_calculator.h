#ifndef EXPRESSION_CALCULATOR_H
#define EXPRESSION_CALCULATOR_H

#include <string>

struct CalculationResult {
    int value;
    bool success;
    std::string error_message;
};

class ExpressionCalculator {
public:
    ExpressionCalculator() = default;

    // Вычисляет значение выражения из строки
    CalculationResult calculate(const std::string& expression);

    // Загружает выражение из файла
    bool loadFromFile(const std::string& filename, std::string& expression);

    // Сохраняет результат в файл
    bool saveResultToFile(const std::string& filename, const CalculationResult& result) const;

private:
    // Рекурсивные функции (без циклов!)
    int parseTerm(const std::string& s, int& position);
    int parseExpression(const std::string& s, int& position);
    bool isDigit(char c) const;
    bool isOperator(char c) const;
};

#endif // EXPRESSION_CALCULATOR_H