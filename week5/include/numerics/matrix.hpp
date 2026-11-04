#pragma once

#include "numerics/numeric_types.hpp"

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace numerics {

// Matrix stores values of one numeric type.
template <typename T>
class Matrix {
    static_assert(is_numeric_v<T>,
                  "Matrix elements must be numeric");

public:
    using Row = std::vector<T>;
    using Storage = std::vector<Row>;

    Matrix() = default;

    Matrix(std::initializer_list<std::initializer_list<T>> rows) {
        values_.reserve(rows.size());

        for (const auto& row : rows) {
            values_.emplace_back(row);
        }

        validate();
    }

    explicit Matrix(const Storage& values)
        : values_(values) {
        validate();
    }

    explicit Matrix(Storage&& values)
        : values_(std::move(values)) {
        validate();
    }

    std::size_t rows() const noexcept {
        return values_.size();
    }

    std::size_t columns() const noexcept {
        return values_.empty() ? 0 : values_[0].size();
    }

    Row& operator[](std::size_t index) {
        return values_.at(index);
    }

    const Row& operator[](std::size_t index) const {
        return values_.at(index);
    }

    const Storage& values() const noexcept {
        return values_;
    }

    template <typename U>
    std::vector<double> multiply(
        const std::vector<U>& weights) const {

        static_assert(is_numeric_v<U>,
                      "Weights must be numeric");

        if (weights.size() != columns()) {
            throw std::invalid_argument(
                "Matrix columns must match weight count");
        }

        std::vector<double> result;
        result.reserve(rows());

        for (const Row& row : values_) {
            double sum = 0.0;

            for (std::size_t column = 0;
                 column < columns(); ++column) {

                sum += numerics::to_double(row[column]) *
                       numerics::to_double(weights[column]);
            }

            result.push_back(sum);
        }

        return result;
    }

    Matrix<T> transpose() const {
        if (values_.empty()) {
            return {};
        }

        Storage transposed(columns(), Row(rows()));

        for (std::size_t row = 0; row < rows(); ++row) {
            for (std::size_t column = 0;
                 column < columns(); ++column) {

                transposed[column][row] = values_[row][column];
            }
        }

        return Matrix<T>(std::move(transposed));
    }

    std::vector<std::vector<double>> to_double() const {
        return to_double_matrix(values_);
    }

private:
    Storage values_;

    void validate() const {
        if (values_.empty()) {
            return;
        }

        const std::size_t expected_columns = values_[0].size();

        for (const Row& row : values_) {
            if (row.size() != expected_columns) {
                throw std::invalid_argument(
                    "All matrix rows must have equal sizes");
            }
        }
    }
};

} // namespace numerics