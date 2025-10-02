#include "calc.h"
#include <iostream>
#include <string>

int main(){
    std::cout << "Введите выражение в формате \"A <op> B\"\n";
    std::cout << "Поддерживаемые операции:\n";
    std::cout << "  +  сложение (A + B)\n";
    std::cout << "  -  вычитание (A - B)\n";
    std::cout << "  *  умножение (A * B)\n";
    std::cout << "  /  деление (A / B)\n";
    std::cout << "  %  остаток от деления (fmod)\n";
    std::cout << "  ^  возведение в степень (pow)\n";
    std::cout << "  l  логарифм по основанию B (log_B A)\n";
    std::cout << "Ограничения:\n";
    std::cout << "  для / и % требуется B != 0\n";
    std::cout << "  для ^ и l результат должен быть конечным\n";
    std::cout << "  для l дополнительно A > 0, B > 0 и B != 1\n";
    std::cout << "> " << std::flush;

    std::string line;
    if(!std::getline(std::cin, line)){
        std::cerr << "Ошибка чтения ввода\n";
        return 1;
    }

    auto res = eval_line(line);
    if(!res){
        std::cerr << "Ошибка: некорректное выражение или недопустимая операция\n";
        return 2;
    }

    std::cout << *res << "\n";
    return 0;
}
