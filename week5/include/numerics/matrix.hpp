#pragma once

#include "numerics/numeric_types.hpp"

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace numerics {

template <typename T>
class Matrix {
    static_assert(is_numeric_v<T>,
                  "Matrix elements must be numeric");

public:
    using Row = std::vector<T>;
    using Storage = std::vector<Row>;

    Matrix() = default;

    Matrix(std::initializer_list<Row> rows)
        : values_(rows) {
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

    std::size_t rows() const {
        return values_.size();
    }

    std::size_t columns() const {
        return columns_;
    }

    const Row& operator[](std::size_t index) const {
        return values_.at(index);
    }

    Row& operator[](std::size_t index) {
        return values_.at(index);
    }

    template <typename U>
    std::vector<double> multiply(
        const std::vector<U>& weights) const {

        static_assert(is_numeric_v<U>,
                      "Weights must be numeric");

        if (weights.size() != columns_) {
            throw std::invalid_argument(
                "Matrix columns must match weight count");
        }

        const std::vector<double> double_weights =
            to_double_vector(weights);

        std::vector<double> result;
        result.reserve(rows());

        for (const Row& row : values_) {
            double sum = 0.0;

            for (std::size_t column = 0;
                 column < columns_; ++column) {

                sum += numerics::to_double(row[column]) *
                       double_weights[column];
            }

            result.push_back(sum);
        }

        return result;
    }

    Matrix<T> transpose() const {
        Storage transposed(
            columns_, Row(rows()));

        for (std::size_t row = 0; row < rows(); ++row) {
            for (std::size_t column = 0;
                 column < columns_; ++column) {

                transposed[column][row] =
                    values_[row][column];
            }
        }

        return Matrix<T>(std::move(transposed));
    }

    std::vector<std::vector<double>> to_double() const {
        return to_double_matrix(values_);
    }

private:
    Storage values_;
    std::size_t columns_ = 0;

    void validate() {
        if (values_.empty()) {
            columns_ = 0;
            return;
        }

        columns_ = values_.front().size();

        for (const Row& row : values_) {
            if (row.size() != columns_) {
                throw std::invalid_argument(
                    "All matrix rows must have equal sizes");
            }
        }
    }
};

} // namespace numerics
