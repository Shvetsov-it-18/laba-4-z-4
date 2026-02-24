//FIX_ME: Неинформативные имена функций
//старый код: int NumRead(string& s, int& symb, int currentNumber = 0)
//           int CalculateTerm(string& s, int& symb)
//           int CalculateS(string& s, int& symb)
новый код : int ReadNumber(const string& expression, int& position, int currentNumber = 0)
int EvaluateTerm(const string& expression, int& position)
int EvaluateExpression(const string& expression, int& position)

//FIX_ME: Неинформативные имена переменных
//старый код: int symb; char znak; string S; int bebe;
новый код : int position; char operation; string expression; int result;

//FIX_ME: Отсутствие const для параметров, которые не изменяются
//старый код: int NumRead(string& s, int& symb, int currentNumber = 0)
новый код : int ReadNumber(const string& expression, int& position, int currentNumber = 0)

//FIX_ME: Использование Windows-специфичных функций
//старый код: SetConsoleCP(1251); SetConsoleOutputCP(1251);
новый код : setlocale(LC_ALL, "ru_RU.UTF-8"); // кроссплатформенное решение

//FIX_ME: Использование exit(1) внутри функции (плохая практика)
//старый код: if (number == 0) { cout << "Ошибка..."; exit(1); }
новый код : if (number == 0) {
    throw runtime_error("Ошибка: деление на ноль!");
}

//FIX_ME: Отсутствие обработки исключений в main
//старый код: int result = CalculateS(S, symb);
новый код : try {
    int result = EvaluateExpression(expression, position);
    cout << "Результат -> " << result << endl;
}
catch (const exception& e) {
    cerr << "Ошибка: " << e.what() << endl;
    return 1;
}

//FIX_ME: Нарушение условия задачи (использование цикла while)
//старый код: while (symb < s.length() && (s[symb] == '*' || s[symb] == '/'))
//           while (symb < s.length() && (s[symb] == '+' || s[symb] == '-'))
новый код :
int EvaluateTerm(const string & expression, int& position) {
    int value = ReadNumber(expression, position);

    if (position < expression.length() &&
        (expression[position] == '*' || expression[position] == '/')) {
        char operation = expression[position];
        position++;
        int number = ReadNumber(expression, position);

        if (operation == '*') {
            value = value * number;
        }
        else {
            if (number == 0) {
                throw runtime_error("Деление на ноль");
            }
            value = value / number;
        }

        // Рекурсивный вызов для обработки следующих операций
        if (position < expression.length() &&
            (expression[position] == '*' || expression[position] == '/')) {
            value = EvaluateTerm(expression, position); // хвостовая рекурсия
        }
    }
    return value;
}

int EvaluateExpression(const string & expression, int& position) {
    int value = EvaluateTerm(expression, position);

    if (position < expression.length() &&
        (expression[position] == '+' || expression[position] == '-')) {
        char operation = expression[position];
        position++;
        int term = EvaluateTerm(expression, position);

        if (operation == '+') {
            value = value + term;
        }
        else {
            value = value - term;
        }

        // Рекурсивный вызов для обработки следующих операций
        if (position < expression.length() &&
            (expression[position] == '+' || expression[position] == '-')) {
            value = EvaluateExpression(expression, position); // хвостовая рекурсия
        }
    }
    return value;
}

//FIX_ME: Отсутствие проверки корректности выражения
//старый код: нет проверок
новый код :
int ReadNumber(const string & expression, int& position, int currentNumber = 0) {
    if (position >= expression.length()) {
        throw runtime_error("Неожиданный конец выражения");
    }
    if (!isdigit(expression[position])) {
        throw runtime_error("Ожидалась цифра, получен символ: " + string(1, expression[position]));
    }

    currentNumber = currentNumber * 10 + (expression[position] - '0');
    position++;

    // Рекурсивный вызов для многозначных чисел
    if (position < expression.length() && isdigit(expression[position])) {
        return ReadNumber(expression, position, currentNumber);
    }
    return currentNumber;
}

//FIX_ME: Отсутствие проверки на переполнение
//старый код: value *= number; value += term;
новый код :
if (value > numeric_limits<int>::max() / number) {
    throw runtime_error("Переполнение при умножении");
}
value = value * number;

if (value > numeric_limits<int>::max() - term) {
    throw runtime_error("Переполнение при сложении");
}
value = value + term;

//FIX_ME: Использование using namespace std (плохая практика)
//старый код: using namespace std;
новый код : using std::cout; using std::cin; using std::string; using std::cerr;
// или явно указывать std:: перед каждым использованием

//FIX_ME: Отсутствие проверки пустой строки
//старый код: getline(cin, S);
новый код :
getline(cin, expression);
if (expression.empty()) {
    cerr << "Ошибка: строка пуста" << endl;
    return 1;
}

//FIX_ME: Неправильный формат вывода
//старый код: cout << "Введите выражение -> ";
новый код : cout << "Введите выражение: ";

//FIX_ME: Отсутствие проверки, что все символы обработаны
//старый код: int result = CalculateS(S, symb);
новый код :
int result = EvaluateExpression(expression, position);
if (position < expression.length()) {
    cerr << "Предупреждение: не все символы были обработаны. Остаток: "
        << expression.substr(position) << endl;
}