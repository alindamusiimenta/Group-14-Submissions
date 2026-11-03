#pragma once

#include "numerics/numeric_types.hpp"

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace numerics {

// A small beginner-friendly matrix that stores values of one numeric type.
template <typename T>
class Matrix {
    static_assert(is_numeric_v<T>, "Matrix<T> requires a numeric type");

public:
    using Row = std::vector<T>;

    Matrix() = default;

    Matrix(std::initializer_list<std::initializer_list<T>> rows) {
        values_.reserve(rows.size());
        for (const auto& row : rows) {
            values_.emplace_back(row);
        }
        check_rectangular();
    }

    explicit Matrix(std::vector<Row> rows) : values_(std::move(rows)) {
        check_rectangular();
    }

    std::size_t rows() const noexcept {
        return values_.size();
    }

    std::size_t columns() const noexcept {
        return values_.empty() ? 0 : values_[0].size();
    }

    Row& operator[](std::size_t row_index) {
        return values_.at(row_index);
    }

    const Row& operator[](std::size_t row_index) const {
        return values_.at(row_index);
    }

    const std::vector<Row>& values() const noexcept {
        return values_;
    }

    std::vector<std::vector<double>> to_double() const {
        return to_double_matrix(values_);
    }

    template <typename U>
    std::vector<double> multiply(const std::vector<U>& vector) const {
        static_assert(is_numeric_v<U>, "multiplier values must be numeric");
        if (columns() != vector.size()) {
            throw std::invalid_argument("matrix columns and vector size must match");
        }

        std::vector<double> result;
        result.reserve(rows());
        for (const Row& row : values_) {
            double total = 0.0;
            for (std::size_t column = 0; column < row.size(); ++column) {
                total += numerics::to_double(row[column]) * numerics::to_double(vector[column]);
            }
            result.push_back(total);
        }
        return result;
    }

    Matrix<T> transpose() const {
        if (values_.empty()) {
            return {};
        }

        std::vector<Row> transposed(columns(), Row(rows()));
        for (std::size_t row = 0; row < rows(); ++row) {
            for (std::size_t column = 0; column < columns(); ++column) {
                transposed[column][row] = values_[row][column];
            }
        }
        return Matrix<T>(std::move(transposed));
    }

private:
    void check_rectangular() const {
        if (values_.empty()) {
            return;
        }

        const std::size_t expected_columns = values_[0].size();
        for (const Row& row : values_) {
            if (row.size() != expected_columns) {
                throw std::invalid_argument("all matrix rows must have the same number of columns");
            }
        }
    }

    std::vector<Row> values_;
};

} // namespace numerics
