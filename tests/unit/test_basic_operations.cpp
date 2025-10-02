/**
 * @file test_basic_operations.cpp
 * @brief Модульные тесты для базовых арифметических операций
 * @author Calculator Team
 * 
 * Этот файл содержит тесты для основных математических операций:
 * - Сложение (add)
 * - Вычитание (sub) 
 * - Умножение (mul)
 * 
 * Тесты проверяют корректность вычислений с различными входными данными.
 */

#include "../utils/test_utils.h"
#include "../../src/calc.h"
#include <iostream>

/**
 * @brief Главная функция для запуска тестов базовых операций
 * @return Количество неудачных тестов
 */
int main() {
    int failures = 0;
    int checks = 0;

    std::cout << "=== Модульные тесты: Базовые операции ===\n";

    // Тесты для функции add
    RUN_TEST("add_positive", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::1.5, 2.5), 4.0);
        ctx.expect_equal(calculator::0.0, 5.0), 5.0);
        ctx.expect_equal(calculator::100.0, 200.0), 300.0);
    });

    RUN_TEST("add_negative", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::-3.0, 3.0), 0.0);
        ctx.expect_equal(calculator::-5.0, -2.0), -7.0);
        ctx.expect_equal(calculator::-10.0, 15.0), 5.0);
    });

    RUN_TEST("add_decimal", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::0.1, 0.2), 0.3);
        ctx.expect_equal(calculator::1.1, 2.2), 3.3);
        ctx.expect_equal(calculator::0.0001, 0.0002), 0.0003);
    });

    // Тесты для функции sub
    RUN_TEST("sub_positive", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::5.0, 2.0), 3.0);
        ctx.expect_equal(calculator::10.0, 3.0), 7.0);
        ctx.expect_equal(calculator::100.0, 50.0), 50.0);
    });

    RUN_TEST("sub_negative", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::-2.0, -3.0), 1.0);
        ctx.expect_equal(calculator::-5.0, 2.0), -7.0);
        ctx.expect_equal(calculator::3.0, -2.0), 5.0);
    });

    RUN_TEST("sub_zero", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::5.0, 0.0), 5.0);
        ctx.expect_equal(calculator::0.0, 5.0), -5.0);
        ctx.expect_equal(calculator::0.0, 0.0), 0.0);
    });

    // Тесты для функции mul
    RUN_TEST("mul_positive", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::3.0, 4.0), 12.0);
        ctx.expect_equal(calculator::5.0, 6.0), 30.0);
        ctx.expect_equal(calculator::10.0, 10.0), 100.0);
    });

    RUN_TEST("mul_negative", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::-2.0, 5.0), -10.0);
        ctx.expect_equal(calculator::3.0, -4.0), -12.0);
        ctx.expect_equal(calculator::-3.0, -4.0), 12.0);
    });

    RUN_TEST("mul_zero", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::0.0, 5.0), 0.0);
        ctx.expect_equal(calculator::5.0, 0.0), 0.0);
        ctx.expect_equal(calculator::0.0, 0.0), 0.0);
    });

    RUN_TEST("mul_decimal", [](test_utils::TestContext& ctx) {
        ctx.expect_equal(calculator::0.5, 4.0), 2.0);
        ctx.expect_equal(calculator::2.5, 2.0), 5.0);
        ctx.expect_equal(calculator::0.1, 0.1), 0.01);
    });

    if (failures == 0) {
        std::cout << "✓ Все тесты базовых операций прошли: " << checks << " проверок\n";
    } else {
        std::cerr << "✗ " << failures << " проверок не прошли из " << checks << "\n";
    }

    return failures == 0 ? 0 : 1;
}
