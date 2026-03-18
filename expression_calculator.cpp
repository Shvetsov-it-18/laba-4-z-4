#include "expression_calculator.h"
#include <fstream>
#include <iostream>
#include <cctype>  // для isdigit

bool ExpressionCalculator::isDigit(char c) const {
    return (c >= '0' && c <= '9');
}

bool ExpressionCalculator::isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*');
}

// Рекурсивный парсинг терма (цифра или терм * цифра)
int ExpressionCalculator::parseTerm(const std::string& s, int& position) {
    // Базовый случай: конец строки или не цифра
    if (position >= s.length() || !isDigit(s[position])) {
        return 0;
    }

    // Читаем текущую цифру
    int current_value = s[position] - '0';
    position++;

    // Если следующий символ - '*', рекурсивно умножаем
    if (position < s.length() && s[position] == '*') {
        position++;  // пропускаем '*'
        return current_value * parseTerm(s, position);
    }

    // Иначе возвращаем просто цифру
    return current_value;
}

// Рекурсивный парсинг выражения (терм или выражение + терм / выражение - терм)
int ExpressionCalculator::parseExpression(const std::string& s, int& position) {
    // Базовый случай: конец строки
    if (position >= s.length()) {
        return 0;
    }

    // Парсим первый терм
    int value = parseTerm(s, position);

    // Если дошли до конца, возвращаем значение
    if (position >= s.length()) {
        return value;
    }

    // Проверяем операцию
    char operation = s[position];
    if (operation == '+' || operation == '-') {
        position++;  // пропускаем операцию
        int next_value = parseExpression(s, position);

        if (operation == '+') {
            return value + next_value;
        }
        else {  // '-'
            return value - next_value;
        }
    }

    // Если нет операции, возвращаем текущее значение
    return value;
}

CalculationResult ExpressionCalculator::calculate(const std::string& expression) {
    CalculationResult result;
    result.success = false;
    result.value = 0;

    // Проверка на пустую строку
    if (expression.empty()) {
        result.error_message = "Пустая строка выражения";
        return result;
    }

    // Проверка на недопустимые символы (только цифры, +, -, *)
    for (char c : expression) {
        if (!isDigit(c) && !isOperator(c)) {
            result.error_message = "Недопустимый символ в выражении: ";
            result.error_message += c;
            return result;
        }
    }

    int position = 0;
    result.value = parseExpression(expression, position);

    // Проверка, что разобрали всю строку
    if (position != expression.length()) {
        result.error_message = "Некорректное выражение (не все символы обработаны)";
        return result;
    }

    result.success = true;
    return result;
}

bool ExpressionCalculator::loadFromFile(const std::string& filename, std::string& expression) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Ошибка! Не удалось открыть " << filename << std::endl;
        return false;
    }

    std::getline(input_file, expression);

    // Удаляем возможные пробелы в начале и конце
    if (!expression.empty()) {
        expression.erase(0, expression.find_first_not_of(" \t\r\n"));
        expression.erase(expression.find_last_not_of(" \t\r\n") + 1);
    }

    return !expression.empty();
}

bool ExpressionCalculator::saveResultToFile(const std::string& filename,
    const CalculationResult& result) const {
    std::ofstream output_file(filename);
    if (!output_file.is_open()) {
        std::cerr << "Ошибка! Не удалось создать " << filename << std::endl;
        return false;
    }

    if (result.success) {
        output_file << "Результат: " << result.value << std::endl;
    }
    else {
        output_file << "Ошибка: " << result.error_message << std::endl;
    }

    return output_file.good();
}