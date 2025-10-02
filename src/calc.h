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

// Разбор строки вида "A <op> B", op: + - * / % ^ l
std::optional<double> eval_line(const std::string& line);
