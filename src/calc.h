#pragma once
#include <optional>
#include <string>

double add(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
std::optional<double> divi(double a, double b); // nullopt при делении на 0
std::optional<double> mod(double a, double b); // nullopt при делении на 0
std::optional<double> powd(double base, double exponent); // nullopt при недопустимом результате
std::optional<double> logb(double value, double base); // nullopt при value<=0, base<=0 или base==1
std::optional<double> square_root(double value); // nullopt при value<0
std::optional<double> factorial(double value); // nullopt при value<0, нецелом числе или слишком большом

// Разбор строки вида "A <op> B", "sqrt A" или "factorial A", op: + - * / % ^ l s f
std::optional<double> eval_line(const std::string& line);
