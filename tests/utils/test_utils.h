/**
 * @file test_utils.h
 * @brief Утилиты для тестирования калькулятора
 * @author Calculator Team
 * 
 * Этот файл содержит вспомогательные функции и классы для написания тестов:
 * 
 * - TestContext: контекст для выполнения тестов с подсчетом ошибок
 * - approx_equal: сравнение чисел с плавающей точкой с учетом погрешности
 * - Макрос RUN_TEST: упрощенный запуск тестов
 * 
 * Все функции тестирования используют русский язык для вывода сообщений.
 */

#pragma once
#include <cmath>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

/**
 * @brief Пространство имён для утилит тестирования
 */
namespace test_utils {

/**
 * @brief Сравнение чисел с плавающей точкой с учетом погрешности
 * @param a Первое число
 * @param b Второе число
 * @param eps Допустимая погрешность (по умолчанию 1e-9)
 * @return true если числа равны с учетом погрешности
 */
bool approx_equal(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) <= eps;
}

/**
 * @brief Контекст для выполнения тестов
 * 
 * Содержит информацию о текущем тесте и предоставляет методы
 * для проверки условий с автоматическим подсчетом ошибок.
 */
struct TestContext {
    const char* name;
    int& failures;
    int& checks;

    void report_failure(const std::string& message) {
        std::cerr << name << " FAILED: " << message << "\n";
        ++failures;
    }

    void check(bool condition, const std::string& message) {
        ++checks;
        if (!condition) {
            report_failure(message);
        }
    }

    void expect_equal(double actual, double expected, double eps = 1e-9) {
        std::ostringstream oss;
        oss << "ожидалось " << expected << ", получено " << actual;
        check(approx_equal(actual, expected, eps), oss.str());
    }

    void expect_optional_equal(const std::optional<double>& value, double expected, double eps = 1e-9) {
        if (!value) {
            report_failure("ожидалось значение, но получен nullopt");
            ++checks;
            return;
        }
        expect_equal(*value, expected, eps);
    }

    void expect_nullopt(const std::optional<double>& value) {
        ++checks;
        if (value) {
            std::ostringstream oss;
            oss << "ожидался nullopt, но получено " << *value;
            report_failure(oss.str());
        }
    }
};

// Макрос для запуска тестов
#define RUN_TEST(name, func) \
    do { \
        test_utils::TestContext ctx{name, failures, checks}; \
        func(ctx); \
    } while(0)

} // namespace test_utils
