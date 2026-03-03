// Ошибка: использование Windows.h привязывает код к Windows
// #include <Windows.h>
// (просто удаляем эту строку)

// Ошибка: использование using namespace std; запрещено Google Style
// using namespace std;
// (просто удаляем эту строку)

// Ошибка: функция NumRead не нужна, так как терм состоит только из одной цифры по условию
// int NumRead(string& s, int& symb, int currentNumber = 0) {
//     if (symb >= s.length() || !isdigit(s[symb])) {
//         return currentNumber;
//     }
//     currentNumber = currentNumber * 10 + (s[symb] - '0');
//     symb++;
//     return NumRead(s, symb, currentNumber);
// }
// (функция полностью удалена)

// Ошибка: функция CalculateTerm использует цикл while, что запрещено условием
// int CalculateTerm(string& s, int& symb) {
//     int value = NumRead(s, symb);
//     while (symb < s.length() && (s[symb] == '*' || s[symb] == '/')) {
//         char znak = s[symb];
//         symb++;
//         int number = NumRead(s, symb);
//         if (znak == '*') {
//             value *= number;
//         } else {
//             if (number == 0) {
//                 cout << "Ошибка при делении на ноль!" << endl;
//                 exit(1);
//             }
//             value /= number;
//         }
//     }
//     return value;
// }
int CalculateTerm(const std::string& s, int& symb) {
  if (symb >= s.length()) {
    return 0;
  }
  if (!isdigit(s[symb])) {
    return 0;
  }
  int current_value = s[symb] - '0';
  symb++;
  if (symb < s.length() && s[symb] == '*') {
    symb++;
    return current_value * CalculateTerm(s, symb);
  }
  return current_value;
}

// Ошибка: функция CalculateS использует цикл while, что запрещено условием
// int CalculateS(string& s, int& symb) {
//     int value = CalculateTerm(s, symb);
//     while (symb < s.length() && (s[symb] == '+' || s[symb] == '-')) {
//         char znak = s[symb];
//         symb++;
//         int term = CalculateTerm(s, symb);
//         if (znak == '+') {
//             value += term;
//         } else {
//             value -= term;
//         }
//     }
//     return value;
// }
int CalculateExpression(const std::string& s, int& symb) {
  if (symb >= s.length()) {
    return 0;
  }
  int value = CalculateTerm(s, symb);
  if (symb >= s.length()) {
    return value;
  }
  char operation = s[symb];
  if (operation == '+' || operation == '-') {
    symb++;
    int next_value = CalculateExpression(s, symb);
    if (operation == '+') {
      return value + next_value;
    } else {
      return value - next_value;
    }
  }
  return value;
}

// Ошибка: неверное имя функции в вызове
// int result = CalculateS(s, symb);
  int result = CalculateExpression(s, symb);

// Ошибка: SetConsoleCP и SetConsoleOutputCP специфичны для Windows
// SetConsoleCP(1251);
// SetConsoleOutputCP(1251);
  std::setlocale(LC_ALL, "Russian");

// Ошибка: отсутствует std:: перед cout, cin, endl
// cout << "Введите выражение -> "; getline(cin, S);
  std::cout << "Введите выражение -> ";
  std::getline(std::cin, s);

// cout << "Результат -> " << result << endl;
  std::cout << "Результат -> " << result << std::endl;
