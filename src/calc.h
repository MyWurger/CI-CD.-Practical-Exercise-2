/**
 * @file calc.h
 * @brief Заголовочный файл для калькулятора
 * @author Calculator Team
 */

#pragma once
#include <optional>
#include <string>

/**
 * @brief Пространство имён для функций калькулятора
 */
namespace calculator {

/**
 * @brief Сложение двух чисел
 * @param a Первое число
 * @param b Второе число
 * @return Результат сложения a + b
 */
double add(double a, double b);

/**
 * @brief Вычитание двух чисел
 * @param a Первое число
 * @param b Второе число
 * @return Результат вычитания a - b
 */
double sub(double a, double b);

/**
 * @brief Умножение двух чисел
 * @param a Первое число
 * @param b Второе число
 * @return Результат умножения a * b
 */
double mul(double a, double b);

/**
 * @brief Деление двух чисел
 * @param a Делимое
 * @param b Делитель
 * @return Результат деления a / b или std::nullopt при делении на 0
 */
std::optional<double> divi(double a, double b);

/**
 * @brief Остаток от деления
 * @param a Делимое
 * @param b Делитель
 * @return Остаток от деления a % b или std::nullopt при делении на 0
 */
std::optional<double> mod(double a, double b);

/**
 * @brief Возведение в степень
 * @param base Основание
 * @param exponent Показатель степени
 * @return Результат base^exponent или std::nullopt при недопустимом результате
 */
std::optional<double> powd(double base, double exponent);

/**
 * @brief Логарифм по произвольному основанию
 * @param value Значение для вычисления логарифма
 * @param base Основание логарифма
 * @return Логарифм value по основанию base или std::nullopt при value<=0, base<=0 или base==1
 */
std::optional<double> logb(double value, double base);

/**
 * @brief Квадратный корень
 * @param value Значение для извлечения корня
 * @return Квадратный корень из value или std::nullopt при value<0
 */
std::optional<double> square_root(double value);

/**
 * @brief Факториал числа
 * @param value Число для вычисления факториала
 * @return Факториал value или std::nullopt при value<0, нецелом числе или слишком большом значении
 */
std::optional<double> factorial(double value);

/**
 * @brief Разбор и вычисление математического выражения
 * @param line Строка с выражением вида "A <op> B", "sqrt A" или "factorial A"
 * @return Результат вычисления или std::nullopt при ошибке
 * 
 * Поддерживаемые операции:
 * - Бинарные: + - * / % ^ l (логарифм)
 * - Унарные: sqrt, factorial
 */
std::optional<double> eval_line(const std::string& line);

} // namespace calculator
