#pragma once
#include <optional>
#include <string>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
std::optional<int> divi(int a, int b); // nullopt при делении на 0
std::optional<int> mod(int a, int b); // nullopt при делении на 0
std::optional<int> powi(int base, int exponent); // nullopt при отрицательном показателе

// Разбор строки вида "A <op> B", op: + - * / % ^
std::optional<int> eval_line(const std::string& line);
