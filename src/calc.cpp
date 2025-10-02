/**
 * @file calc.cpp
 * @brief Реализация функций калькулятора
 * @author Calculator Team
 */

#include "calc.h"
#include <cmath>
#include <sstream>

namespace calculator {

double add(double a, double b){ 
    return a + b; 
}

double sub(double a, double b){ 
    return a - b; 
}

double mul(double a, double b){ 
    return a * b; 
}

std::optional<double> divi(double a, double b){ 
    if(b == 0.0) return std::nullopt; 
    return a / b; 
}

std::optional<double> mod(double a, double b){ 
    if(b == 0.0) return std::nullopt; 
    return std::fmod(a, b); 
}

std::optional<double> powd(double base, double exponent){
    double result = std::pow(base, exponent);
    if(!std::isfinite(result)) return std::nullopt;
    return result;
}

std::optional<double> logb(double value, double base){
    if(value <= 0.0 || base <= 0.0 || base == 1.0) return std::nullopt;
    double result = std::log(value) / std::log(base);
    if(!std::isfinite(result)) return std::nullopt;
    return result;
}

std::optional<double> square_root(double value){
    if(value < 0.0) return std::nullopt;
    double result = std::sqrt(value);
    if(!std::isfinite(result)) return std::nullopt;
    return result;
}

std::optional<double> factorial(double value){
    // Проверяем, что значение неотрицательное
    if(value < 0.0) return std::nullopt;
    
    // Проверяем, что значение близко к целому (с учетом погрешности для чисел с плавающей точкой)
    double rounded = std::round(value);
    if(std::abs(value - rounded) > 1e-6) return std::nullopt;
    
    // Проверяем, что значение не слишком большое (факториал растет очень быстро)
    if(value > 170.0) return std::nullopt; // 170! уже очень большое число
    
    // Вычисляем факториал
    double result = 1.0;
    int int_value = static_cast<int>(std::round(value)); // Используем round для корректного округления
    for(int i = 1; i <= int_value; ++i) {
        result *= i;
        // Проверяем на переполнение
        if(!std::isfinite(result)) return std::nullopt;
    }
    
    return result;
}

std::optional<double> eval_line(const std::string& line){
    std::istringstream is(line);
    
    // Проверяем на унарные операции sqrt и factorial
    std::string op_str;
    if(is >> op_str) {
        if(op_str == "sqrt") {
            double value;
            if(is >> value) {
                char extra = 0;
                if(is >> extra) return std::nullopt; // Лишние символы
                if(std::isnan(value)) return std::nullopt; // NaN недопустим
                return square_root(value);
            }
            return std::nullopt; // Нет значения после sqrt
        }
        if(op_str == "factorial") {
            double value;
            if(is >> value) {
                char extra = 0;
                if(is >> extra) return std::nullopt; // Лишние символы
                if(std::isnan(value)) return std::nullopt; // NaN недопустим
                return factorial(value);
            }
            return std::nullopt; // Нет значения после factorial
        }
    }
    
    // Возвращаемся к началу потока для бинарных операций
    is.clear();
    is.seekg(0);
    
    double a=0.0,b=0.0; char op=0;
    if(!(is>>a>>op>>b)) return std::nullopt;

    // Проверяем на NaN в операндах
    if(std::isnan(a) || std::isnan(b)) return std::nullopt;

    char extra=0;
    if(is>>extra) return std::nullopt;

    switch(op){
        case '+': return add(a,b);
        case '-': return sub(a,b);
        case '*': return mul(a,b);
        case '/': return divi(a,b);
        case '%': return mod(a,b);
        case '^': return powd(a,b);
        case 'l': return logb(a,b);
        default: return std::nullopt;
    }
}

} // namespace calculator
