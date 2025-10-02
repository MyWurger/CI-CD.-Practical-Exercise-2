/**
 * @file main.cpp
 * @brief Главная функция калькулятора
 * @author Calculator Team
 */

#include "calc.h"
#include <iostream>
#include <string>

/**
 * @brief Главная функция программы
 * @return Код возврата: 0 - успех, 1 - ошибка ввода, 2 - ошибка вычисления
 * 
 * Программа принимает математическое выражение от пользователя и выводит результат.
 * Поддерживает бинарные операции (+, -, *, /, %, ^, l) и унарные (sqrt, factorial).
 */
int main(){
    std::cout << "Введите выражение в формате \"A <op> B\", \"sqrt A\" или \"factorial A\"\n";
    std::cout << "Поддерживаемые операции:\n";
    std::cout << "  +  сложение (A + B)\n";
    std::cout << "  -  вычитание (A - B)\n";
    std::cout << "  *  умножение (A * B)\n";
    std::cout << "  /  деление (A / B)\n";
    std::cout << "  %  остаток от деления (fmod)\n";
    std::cout << "  ^  возведение в степень (pow)\n";
    std::cout << "  l  логарифм по основанию B (log_B A)\n";
    std::cout << "  sqrt  квадратный корень (sqrt A)\n";
    std::cout << "  factorial  факториал (factorial A)\n";
    std::cout << "Ограничения:\n";
    std::cout << "  для / и % требуется B != 0\n";
    std::cout << "  для ^ и l результат должен быть конечным\n";
    std::cout << "  для l дополнительно A > 0, B > 0 и B != 1\n";
    std::cout << "  для sqrt требуется A >= 0\n";
    std::cout << "  для factorial требуется A >= 0, целое число и A <= 170\n";
    std::cout << "> " << std::flush;

    std::string line;
    if(!std::getline(std::cin, line)){
        std::cerr << "Ошибка чтения ввода\n";
        return 1;
    }

    auto res = calculator::eval_line(line);
    if(!res){
        std::cerr << "Ошибка: некорректное выражение или недопустимая операция\n";
        return 2;
    }

    std::cout << *res << "\n";
    return 0;
}
