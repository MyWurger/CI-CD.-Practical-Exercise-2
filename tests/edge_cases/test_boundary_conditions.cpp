#include "../utils/test_utils.h"
#include "../../src/calc.h"
#include <iostream>
#include <cmath>
#include <limits>

int main() {
    int failures = 0;
    int checks = 0;

    std::cout << "=== Тесты граничных случаев ===\n";

    // Тесты для очень больших чисел
    RUN_TEST("large_numbers", [](test_utils::TestContext& ctx) {
        const double large = 1e10;
        ctx.expect_equal(add(large, large), 2e10);
        ctx.expect_equal(sub(large, large), 0.0);
        ctx.expect_equal(mul(large, 2.0), 2e10);
        ctx.expect_optional_equal(divi(large, 2.0), 5e9);
    });

    // Тесты для очень маленьких чисел
    RUN_TEST("small_numbers", [](test_utils::TestContext& ctx) {
        const double small = 1e-10;
        ctx.expect_equal(add(small, small), 2e-10);
        ctx.expect_equal(sub(small, small), 0.0);
        ctx.expect_equal(mul(small, 2.0), 2e-10);
        ctx.expect_optional_equal(divi(small, 2.0), 5e-11);
    });

    // Тесты для чисел с максимальной точностью
    RUN_TEST("precision_limits", [](test_utils::TestContext& ctx) {
        const double eps = std::numeric_limits<double>::epsilon();
        ctx.expect_equal(add(1.0, eps), 1.0 + eps);
        ctx.expect_equal(sub(1.0, eps), 1.0 - eps);
        ctx.expect_equal(mul(1.0, eps), eps);
    });

    // Тесты для бесконечности и NaN
    RUN_TEST("infinity_nan", [](test_utils::TestContext& ctx) {
        const double inf = std::numeric_limits<double>::infinity();
        const double nan = std::numeric_limits<double>::quiet_NaN();
        
        // Проверяем, что операции с бесконечностью работают корректно
        ctx.check(std::isinf(add(inf, 1.0)), "add with infinity should return infinity");
        ctx.check(std::isinf(sub(inf, 1.0)), "sub with infinity should return infinity");
        ctx.check(std::isinf(mul(inf, 2.0)), "mul with infinity should return infinity");
        
        // Проверяем, что операции с NaN возвращают NaN
        ctx.check(std::isnan(add(nan, 1.0)), "add with NaN should return NaN");
        ctx.check(std::isnan(sub(nan, 1.0)), "sub with NaN should return NaN");
        ctx.check(std::isnan(mul(nan, 2.0)), "mul with NaN should return NaN");
    });

    // Тесты для граничных случаев деления
    RUN_TEST("division_edge_cases", [](test_utils::TestContext& ctx) {
        const double tiny = std::numeric_limits<double>::min();
        const double huge = std::numeric_limits<double>::max();
        
        auto result1 = divi(tiny, huge);
        ctx.check(result1.has_value(), "divi(tiny, huge) should succeed");
        if (result1.has_value()) {
            ctx.check(test_utils::approx_equal(*result1, tiny / huge), "divi(tiny, huge) should be approximately correct");
        }
        
        auto result2 = divi(huge, tiny);
        ctx.check(result2.has_value(), "divi(huge, tiny) should succeed");
        if (result2.has_value()) {
            ctx.check(std::isinf(*result2), "divi(huge, tiny) should return infinity");
        }
        
        ctx.expect_nullopt(divi(1.0, 0.0));
        ctx.expect_nullopt(divi(0.0, 0.0));
    });

    // Тесты для граничных случаев возведения в степень
    RUN_TEST("power_edge_cases", [](test_utils::TestContext& ctx) {
        const double huge = std::numeric_limits<double>::max();
        const double tiny = std::numeric_limits<double>::min();
        
        ctx.expect_optional_equal(powd(1.0, huge), 1.0);
        ctx.expect_optional_equal(powd(huge, 0.0), 1.0);
        ctx.expect_optional_equal(powd(tiny, 1.0), tiny);
        ctx.expect_nullopt(powd(-1.0, 0.5));  // Корень из отрицательного числа
    });

    // Тесты для граничных случаев логарифма
    RUN_TEST("logarithm_edge_cases", [](test_utils::TestContext& ctx) {
        const double huge = std::numeric_limits<double>::max();
        const double tiny = std::numeric_limits<double>::min();
        
        ctx.expect_optional_equal(logb(huge, huge), 1.0);
        ctx.expect_optional_equal(logb(tiny, tiny), 1.0);
        ctx.expect_nullopt(logb(0.0, 2.0));    // Логарифм нуля
        ctx.expect_nullopt(logb(1.0, 1.0));    // Логарифм по основанию 1
        ctx.expect_nullopt(logb(-1.0, 2.0));   // Логарифм отрицательного числа
    });

    // Тесты для граничных случаев модуло
    RUN_TEST("modulo_edge_cases", [](test_utils::TestContext& ctx) {
        const double huge = std::numeric_limits<double>::max();
        const double tiny = std::numeric_limits<double>::min();
        
        ctx.expect_optional_equal(mod(huge, 1.0), 0.0);
        ctx.expect_optional_equal(mod(tiny, 1.0), tiny);
        ctx.expect_nullopt(mod(1.0, 0.0));
        ctx.expect_nullopt(mod(0.0, 0.0));
    });

    // Тесты для строковых граничных случаев
    RUN_TEST("eval_line_edge_cases", [](test_utils::TestContext& ctx) {
        // Очень длинные числа
        ctx.expect_optional_equal(eval_line("1e10 + 1e10"), 2e10);
        ctx.expect_optional_equal(eval_line("1e-10 * 1e10"), 1.0);
        
        // Специальные значения
        ctx.expect_nullopt(eval_line("inf + 1"));
        ctx.expect_nullopt(eval_line("nan + 1"));
        
        // Граничные случаи форматирования
        ctx.expect_nullopt(eval_line("1.0.0 + 2"));  // Некорректное число
        ctx.expect_nullopt(eval_line("1e + 2"));     // Некорректная экспонента
        ctx.expect_nullopt(eval_line("1e- + 2"));    // Некорректная экспонента
    });

    // Тесты для производительности с большими числами
    RUN_TEST("performance_large_calculations", [](test_utils::TestContext& ctx) {
        const double base = 2.0;
        const double exp = 100.0;
        
        auto result = powd(base, exp);
        ctx.check(result.has_value(), "Large power calculation should succeed");
        if (result.has_value()) {
            ctx.check(std::isfinite(*result), "Result should be finite");
        }
    });

    // Тесты для точности вычислений
    RUN_TEST("calculation_precision", [](test_utils::TestContext& ctx) {
        // Тест на накопление ошибок округления
        double sum = 0.0;
        for (int i = 0; i < 1000; ++i) {
            sum = add(sum, 0.1);
        }
        ctx.check(test_utils::approx_equal(sum, 100.0, 1e-10), "Sum of 1000 * 0.1 should be approximately 100.0");
        
        // Тест на точность деления
        ctx.expect_optional_equal(divi(1.0, 3.0), 1.0/3.0, 1e-15);
    });

    if (failures == 0) {
        std::cout << "✓ Все тесты граничных случаев прошли: " << checks << " проверок\n";
    } else {
        std::cerr << "✗ " << failures << " проверок не прошли из " << checks << "\n";
    }

    return failures == 0 ? 0 : 1;
}
