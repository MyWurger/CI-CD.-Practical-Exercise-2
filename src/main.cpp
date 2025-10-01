#include "calc.h"
#include <iostream>
#include <string>

int main(){
    std::cout << "Введите выражение в формате \"A <op> B\"\n";
    std::cout << "Поддерживаемые операции:\n";
    std::cout << "  +  сложение (A + B)\n";
    std::cout << "  -  вычитание (A - B)\n";
    std::cout << "  *  умножение (A * B)\n";
    std::cout << "  /  целочисленное деление (A / B)\n";
    std::cout << "  %  остаток от деления (A % B)\n";
    std::cout << "  ^  целочисленная степень (B >= 0)\n";
    std::cout << "Ограничения: делитель для / и % должен быть != 0, показатель степени неотрицательный\n";
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
