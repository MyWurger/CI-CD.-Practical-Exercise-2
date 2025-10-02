/**
 * @file test_advanced_operations.cpp
 * @brief Модульные тесты для продвинутых математических операций
 * @author Calculator Team
 * 
 * Этот файл содержит тесты для сложных математических операций:
 * - Деление (divi) с проверкой деления на ноль
 * - Остаток от деления (mod) с проверкой деления на ноль
 * - Возведение в степень (powd) с проверкой на бесконечность
 * - Логарифм (logb) с проверкой корректности аргументов
 * - Квадратный корень (square_root) с проверкой отрицательных значений
 * - Факториал (factorial) с проверкой целых чисел и переполнения
 * 
 * Тесты покрывают как успешные случаи, так и граничные условия.
 */

#include "../utils/test_utils.h"
#include "../../src/calc.h"
#include <iostream>
#include <cmath>

/**
 * @brief Главная функция для запуска тестов продвинутых операций
 * @return Количество неудачных тестов
 */
int main() {
    int failures = 0;
    int checks = 0;

    std::cout << "=== Модульные тесты: Продвинутые операции ===\n";

    // Тесты для функции divi
    RUN_TEST("divi_normal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::divi(10.0, 2.0), 5.0);
        ctx.expect_optional_equal(calculator::divi(15.0, 3.0), 5.0);
        ctx.expect_optional_equal(calculator::divi(7.0, 2.0), 3.5);
    });

    RUN_TEST("divi_negative", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::divi(-10.0, 2.0), -5.0);
        ctx.expect_optional_equal(calculator::divi(10.0, -2.0), -5.0);
        ctx.expect_optional_equal(calculator::divi(-10.0, -2.0), 5.0);
    });

    RUN_TEST("divi_by_zero", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(calculator::divi(5.0, 0.0));
        ctx.expect_nullopt(calculator::divi(-5.0, 0.0));
        ctx.expect_nullopt(calculator::divi(0.0, 0.0));
    });

    RUN_TEST("divi_decimal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::divi(1.0, 3.0), 1.0/3.0);
        ctx.expect_optional_equal(calculator::divi(0.5, 0.25), 2.0);
        ctx.expect_optional_equal(calculator::divi(0.1, 0.01), 10.0);
    });

    // Тесты для функции mod
    RUN_TEST("mod_normal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::mod(7.5, 2.0), 1.5);
        ctx.expect_optional_equal(calculator::mod(10.0, 3.0), 1.0);
        ctx.expect_optional_equal(calculator::mod(15.0, 4.0), 3.0);
    });

    RUN_TEST("mod_negative", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::mod(-7.5, 2.0), -1.5);
        ctx.expect_optional_equal(calculator::mod(7.5, -2.0), 1.5);
        ctx.expect_optional_equal(calculator::mod(-7.5, -2.0), -1.5);
    });

    RUN_TEST("mod_by_zero", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(calculator::mod(5.0, 0.0));
        ctx.expect_nullopt(calculator::mod(-5.0, 0.0));
        ctx.expect_nullopt(calculator::mod(0.0, 0.0));
    });

    RUN_TEST("mod_decimal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::mod(5.7, 2.1), std::fmod(5.7, 2.1));
        ctx.expect_optional_equal(calculator::mod(0.5, 0.3), std::fmod(0.5, 0.3));
    });

    // Тесты для функции powd
    RUN_TEST("powd_normal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::powd(2.0, 5.0), 32.0);
        ctx.expect_optional_equal(calculator::powd(3.0, 2.0), 9.0);
        ctx.expect_optional_equal(calculator::powd(4.0, 0.5), 2.0);
    });

    RUN_TEST("powd_fractional", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::powd(9.0, -0.5), 1.0 / 3.0);
        ctx.expect_optional_equal(calculator::powd(8.0, 1.0/3.0), 2.0);
        ctx.expect_optional_equal(calculator::powd(16.0, 0.25), 2.0);
    });

    RUN_TEST("powd_invalid", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(calculator::powd(-2.0, 0.5));  // Корень из отрицательного числа
        ctx.expect_nullopt(calculator::powd(0.0, -1.0));  // Деление на ноль
        ctx.expect_nullopt(calculator::powd(-1.0, 0.5));  // Корень из отрицательного числа
    });

    RUN_TEST("powd_zero", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::powd(0.0, 5.0), 0.0);
        ctx.expect_optional_equal(calculator::powd(5.0, 0.0), 1.0);
        ctx.expect_optional_equal(calculator::powd(0.0, 0.0), 1.0);
    });

    // Тесты для функции logb
    RUN_TEST("logb_normal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::logb(8.0, 2.0), 3.0);
        ctx.expect_optional_equal(calculator::logb(9.0, 3.0), 2.0);
        ctx.expect_optional_equal(calculator::logb(100.0, 10.0), 2.0);
    });

    RUN_TEST("logb_special", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::logb(1.0, 10.0), 0.0);
        ctx.expect_optional_equal(calculator::logb(2.0, 2.0), 1.0);
        ctx.expect_optional_equal(calculator::logb(0.5, 2.0), -1.0);
    });

    RUN_TEST("logb_invalid", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(calculator::logb(-1.0, 10.0));  // Отрицательное значение
        ctx.expect_nullopt(calculator::logb(8.0, 1.0));    // Основание равно 1
        ctx.expect_nullopt(calculator::logb(8.0, 0.0));    // Основание равно 0
        ctx.expect_nullopt(calculator::logb(8.0, -2.0));   // Отрицательное основание
        ctx.expect_nullopt(calculator::logb(0.0, 10.0));   // Значение равно 0
    });

    RUN_TEST("logb_decimal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::logb(2.0, 4.0), 0.5);
        ctx.expect_optional_equal(calculator::logb(0.25, 2.0), -2.0);
    });

    // Тесты для функции square_root
    RUN_TEST("square_root_normal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::square_root(4.0), 2.0);
        ctx.expect_optional_equal(calculator::square_root(9.0), 3.0);
        ctx.expect_optional_equal(calculator::square_root(16.0), 4.0);
        ctx.expect_optional_equal(calculator::square_root(0.0), 0.0);
    });

    RUN_TEST("square_root_decimal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::square_root(2.25), 1.5);
        ctx.expect_optional_equal(calculator::square_root(0.25), 0.5);
        ctx.expect_optional_equal(calculator::square_root(6.25), 2.5);
    });

    RUN_TEST("square_root_negative", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(calculator::square_root(-1.0));
        ctx.expect_nullopt(calculator::square_root(-4.0));
        ctx.expect_nullopt(calculator::square_root(-0.1));
    });

    RUN_TEST("square_root_large_numbers", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::square_root(1000000.0), 1000.0);
        ctx.expect_optional_equal(calculator::square_root(100.0), 10.0);
    });

    // Тесты для функции factorial
    RUN_TEST("factorial_normal", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::factorial(0.0), 1.0);   // 0! = 1
        ctx.expect_optional_equal(calculator::factorial(1.0), 1.0);   // 1! = 1
        ctx.expect_optional_equal(calculator::factorial(2.0), 2.0);    // 2! = 2
        ctx.expect_optional_equal(calculator::factorial(3.0), 6.0);    // 3! = 6
        ctx.expect_optional_equal(calculator::factorial(4.0), 24.0);   // 4! = 24
        ctx.expect_optional_equal(calculator::factorial(5.0), 120.0);  // 5! = 120
    });

    RUN_TEST("factorial_larger_numbers", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(calculator::factorial(6.0), 720.0);   // 6! = 720
        ctx.expect_optional_equal(calculator::factorial(7.0), 5040.0);  // 7! = 5040
        ctx.expect_optional_equal(calculator::factorial(8.0), 40320.0); // 8! = 40320
        ctx.expect_optional_equal(calculator::factorial(10.0), 3628800.0); // 10! = 3628800
    });

    RUN_TEST("factorial_invalid", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(calculator::factorial(-1.0));    // Отрицательное число
        ctx.expect_nullopt(calculator::factorial(-5.0));    // Отрицательное число
        ctx.expect_nullopt(calculator::factorial(1.5));     // Нецелое число
        ctx.expect_nullopt(calculator::factorial(3.7));     // Нецелое число
        ctx.expect_nullopt(calculator::factorial(0.1));      // Нецелое число
    });

    RUN_TEST("factorial_large_numbers", [](test_utils::TestContext& ctx) {
        // Тестируем граничные случаи
        ctx.expect_optional_equal(calculator::factorial(15.0), 1307674368000.0); // 15! = 1307674368000
        ctx.expect_nullopt(calculator::factorial(171.0));    // Слишком большое число
        ctx.expect_nullopt(calculator::factorial(200.0));    // Слишком большое число
    });

    RUN_TEST("factorial_precision", [](test_utils::TestContext& ctx) {
        // Тестируем точность для чисел с плавающей точкой
        ctx.expect_optional_equal(calculator::factorial(5.0), 120.0);      // Точно 5.0
        ctx.expect_optional_equal(calculator::factorial(5.0000001), 120.0); // Почти 5.0
        ctx.expect_optional_equal(calculator::factorial(4.9999999), 120.0); // Почти 5.0
        ctx.expect_nullopt(calculator::factorial(5.1));      // Слишком далеко от целого
        ctx.expect_nullopt(calculator::factorial(5.5));      // Половина
    });

    if (failures == 0) {
        std::cout << "✓ Все тесты продвинутых операций прошли: " << checks << " проверок\n";
    } else {
        std::cerr << "✗ " << failures << " проверок не прошли из " << checks << "\n";
    }

    return failures == 0 ? 0 : 1;
}