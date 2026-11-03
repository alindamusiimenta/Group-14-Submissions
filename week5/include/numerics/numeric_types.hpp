#pragma once

#include <cmath>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace numerics
{
    // C++17 has no concepts, so use a trait to allow arithmetic types except bool.
    template <typename T>
    inline constexpr bool is_numeric_v =
        std::is_arithmetic_v<std::remove_cv_t<T>> &&
        !std::is_same_v<std::remove_cv_t<T>, bool>;
    // True for int, float, double, etc. (const/volatile ignored), false for bool.
    template <typename To, typename From>
    To checked_numeric_cast(From value)
    {
        static_assert(is_numeric_v<To>, "destination type must be numeric");
        static_assert(is_numeric_v<From>, "source type must be numeric");
        // Compile-time check: both types must be numeric.

        const long double wide_value = static_cast<long double>(value);
        // Widen so the checks below don't overflow or lose precision.
        if (!std::isfinite(wide_value))
        {
            // Rejects NaN and +/- infinity.
            throw std::invalid_argument("numeric values must be finite");
        }
        if constexpr (std::is_integral_v<To>)
        {
            // Integer targets only.
            if (std::trunc(wide_value) != wide_value)
            {
                // Value has a fractional part (e.g. 3.5).
                throw std::invalid_argument("cannot convert a fractional value to an integer type");
            }
            // Use an exclusive power-of-two upper bound.
            const int digits = std::numeric_limits<To>::digits;
            // Number of value bits (excludes the sign bit).
            const long double upper_exclusive = std::ldexp(1.0L, digits);
            // 2^digits = one past the max value.
            const long double lowest = std::is_signed_v<To> ? -upper_exclusive : 0.0L;
            // Signed min is -2^digits; unsigned min is 0.
            if (wide_value < lowest || wide_value >= upper_exclusive)
            {
                // Lower bound inclusive, upper bound exclusive.
                throw std::out_of_range("numeric value is outside the destination type's range");
            }
        }
        else
        {
            // Floating-point targets.
            const long double lowest = static_cast<long double>(std::numeric_limits<To>::lowest());
            // Most negative finite value (not min(), which is the smallest positive).
            const long double highest = static_cast<long double>(std::numeric_limits<To>::max());
            // Largest finite value.
            if (wide_value < lowest || wide_value > highest)
            {
                throw std::out_of_range("numeric value is outside the destination type's range");
            }
        }
        const To converted = static_cast<To>(value);
        // Convert from the original value, not wide_value.
        if constexpr (std::is_floating_point_v<To>)
        {
            if (!std::isfinite(converted))
            {
                // Narrowing (e.g. double -> float) can round up to infinity.
                throw std::out_of_range("numeric conversion produced a non-finite value");
            }
        }
        return converted;
    }
    template <typename T>
    double to_double(T value)
    {
        return checked_numeric_cast<double>(value);
        // Checked conversion of one value to double.
    }
    template <typename T>
    std::vector<double> to_double_vector(const std::vector<T> &values)
    {
        static_assert(is_numeric_v<T>, "vector values must be numeric");

        std::vector<double> converted;
        converted.reserve(values.size());
        // Pre-allocate to avoid reallocations.
        for (T value : values)
        {
            converted.push_back(to_double(value));
            // Throws if any element is invalid.
        }
        return converted;
    }
    template <typename T>
    std::vector<std::vector<double>> to_double_matrix(
        const std::vector<std::vector<T>> &values)
    {
        static_assert(is_numeric_v<T>, "matrix values must be numeric");

        std::vector<std::vector<double>> converted;
        converted.reserve(values.size());

        std::size_t expected_columns = 0;
        // Column count of the first row; every other row must match.
        for (std::size_t row_index = 0; row_index < values.size(); ++row_index)
        {
            const std::vector<T> &row = values[row_index];
            if (row_index == 0)
            {
                expected_columns = row.size();
            }
            else if (row.size() != expected_columns)
            {
                // Rejects ragged matrices.
                throw std::invalid_argument("all matrix rows must have the same number of columns");
            }
            converted.push_back(to_double_vector(row));
            // Validates and converts each element in the row.
        }
        return converted;
    }

}