#include "../utils/test_utils.h"
#include "../../src/calc.h"
#include <iostream>
#include <cmath>

int main() {
    int failures = 0;
    int checks = 0;

    std::cout << "=== Интеграционные тесты: eval_line ===\n";

    // Тесты для корректных выражений
    RUN_TEST("eval_line_basic_operations", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line("3 + 4"), 7.0);
        ctx.expect_optional_equal(eval_line("10 - 3"), 7.0);
        ctx.expect_optional_equal(eval_line("2 * 5"), 10.0);
        ctx.expect_optional_equal(eval_line("15 / 3"), 5.0);
    });

    RUN_TEST("eval_line_advanced_operations", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line("5 % 2"), std::fmod(5.0, 2.0));
        ctx.expect_optional_equal(eval_line("2 ^ 3"), 8.0);
        ctx.expect_optional_equal(eval_line("16 l 2"), 4.0);
    });

    RUN_TEST("eval_line_sqrt_operations", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line("sqrt 4"), 2.0);
        ctx.expect_optional_equal(eval_line("sqrt 9"), 3.0);
        ctx.expect_optional_equal(eval_line("sqrt 16"), 4.0);
        ctx.expect_optional_equal(eval_line("sqrt 0"), 0.0);
        ctx.expect_optional_equal(eval_line("sqrt 2.25"), 1.5);
    });

    RUN_TEST("eval_line_factorial_operations", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line("factorial 0"), 1.0);   // 0! = 1
        ctx.expect_optional_equal(eval_line("factorial 1"), 1.0);   // 1! = 1
        ctx.expect_optional_equal(eval_line("factorial 3"), 6.0);   // 3! = 6
        ctx.expect_optional_equal(eval_line("factorial 5"), 120.0); // 5! = 120
        ctx.expect_optional_equal(eval_line("factorial 7"), 5040.0); // 7! = 5040
    });

    RUN_TEST("eval_line_negative_numbers", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line("-3 + 4"), 1.0);
        ctx.expect_optional_equal(eval_line("5 - -2"), 7.0);
        ctx.expect_optional_equal(eval_line("-2 * 3"), -6.0);
        ctx.expect_optional_equal(eval_line("-10 / 2"), -5.0);
    });

    RUN_TEST("eval_line_decimal_numbers", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line("1.5 + 2.5"), 4.0);
        ctx.expect_optional_equal(eval_line("3.14 * 2"), 6.28);
        ctx.expect_optional_equal(eval_line("7.5 / 2.5"), 3.0);
        ctx.expect_optional_equal(eval_line("2.5 ^ 2"), 6.25);
    });

    RUN_TEST("eval_line_complex_expressions", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line("0 + 0"), 0.0);
        ctx.expect_optional_equal(eval_line("1 * 0"), 0.0);
        ctx.expect_optional_equal(eval_line("0 / 1"), 0.0);
        ctx.expect_optional_equal(eval_line("1 ^ 0"), 1.0);
    });

    // Тесты для некорректных выражений
    RUN_TEST("eval_line_division_by_zero", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line("5 / 0"));
        ctx.expect_nullopt(eval_line("10 / 0"));
        ctx.expect_nullopt(eval_line("0 / 0"));
    });

    RUN_TEST("eval_line_invalid_operations", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line("3 & 4"));      // Неподдерживаемая операция
        ctx.expect_nullopt(eval_line("3 @ 4"));      // Неподдерживаемая операция
        ctx.expect_nullopt(eval_line("3 # 4"));      // Неподдерживаемая операция
    });

    RUN_TEST("eval_line_invalid_syntax", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line("foo"));        // Не числовое выражение
        ctx.expect_nullopt(eval_line("3 +"));        // Неполное выражение
        ctx.expect_nullopt(eval_line("+ 3"));        // Неполное выражение
        ctx.expect_nullopt(eval_line("3 + 4 extra")); // Лишние символы
        ctx.expect_nullopt(eval_line("3 + 4 + 5"));  // Слишком много операндов
    });

    RUN_TEST("eval_line_invalid_power", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line("-2 ^ 0.5"));   // Корень из отрицательного числа
        ctx.expect_nullopt(eval_line("-1 ^ 0.5"));   // Корень из отрицательного числа
    });

    RUN_TEST("eval_line_invalid_logarithm", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line("-1 l 10"));    // Логарифм отрицательного числа
        ctx.expect_nullopt(eval_line("8 l 1"));      // Логарифм по основанию 1
        ctx.expect_nullopt(eval_line("8 l 0"));      // Логарифм по основанию 0
        ctx.expect_nullopt(eval_line("0 l 10"));     // Логарифм нуля
    });

    RUN_TEST("eval_line_invalid_sqrt", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line("sqrt -1"));    // Корень из отрицательного числа
        ctx.expect_nullopt(eval_line("sqrt -4"));    // Корень из отрицательного числа
        ctx.expect_nullopt(eval_line("sqrt"));       // Нет значения после sqrt
        ctx.expect_nullopt(eval_line("sqrt 4 5"));   // Лишние символы после sqrt
    });

    RUN_TEST("eval_line_invalid_factorial", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line("factorial -1"));    // Факториал отрицательного числа
        ctx.expect_nullopt(eval_line("factorial 1.5"));   // Факториал нецелого числа
        ctx.expect_nullopt(eval_line("factorial"));       // Нет значения после factorial
        ctx.expect_nullopt(eval_line("factorial 5 6"));   // Лишние символы после factorial
        ctx.expect_nullopt(eval_line("factorial 200"));   // Слишком большое число
    });

    RUN_TEST("eval_line_nan_handling", [](test_utils::TestContext& ctx) {
        // Тестируем обработку NaN в различных операциях
        ctx.expect_nullopt(eval_line("nan + 1"));         // NaN в бинарных операциях
        ctx.expect_nullopt(eval_line("1 + nan"));         // NaN в бинарных операциях
        ctx.expect_nullopt(eval_line("sqrt nan"));        // NaN в унарных операциях
        ctx.expect_nullopt(eval_line("factorial nan"));   // NaN в унарных операциях
    });

    RUN_TEST("eval_line_edge_cases", [](test_utils::TestContext& ctx) {
        ctx.expect_nullopt(eval_line(""));           // Пустая строка
        ctx.expect_nullopt(eval_line("   "));        // Только пробелы
        ctx.expect_nullopt(eval_line("3.14.15 + 2")); // Некорректное число
        ctx.expect_nullopt(eval_line("3 + 4.5.6"));  // Некорректное число
    });

    RUN_TEST("eval_line_whitespace_handling", [](test_utils::TestContext& ctx) {
        ctx.expect_optional_equal(eval_line(" 3 + 4 "), 7.0);      // Пробелы вокруг
        ctx.expect_optional_equal(eval_line("3  +  4"), 7.0);     // Множественные пробелы
        ctx.expect_optional_equal(eval_line("\t3\t+\t4\t"), 7.0); // Табуляция
    });

    if (failures == 0) {
        std::cout << "✓ Все интеграционные тесты прошли: " << checks << " проверок\n";
    } else {
        std::cerr << "✗ " << failures << " проверок не прошли из " << checks << "\n";
    }

    return failures == 0 ? 0 : 1;
}
