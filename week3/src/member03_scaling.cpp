#include "lasso/week2.hpp"
#include <cmath>
#include <stdexcept>

namespace lasso {

ScaledData standardize(const Matrix& features) {
    if (features.empty() || features[0].empty()) throw std::invalid_argument("features cannot be empty");
    const std::size_t rows = features.size();
    const std::size_t columns = features[0].size();
    ScaledData result;
    result.features = features;
    result.means.assign(columns, 0.0);
    result.standard_deviations.assign(columns, 0.0);

    for (const Vector& row : features) if (row.size() != columns) throw std::invalid_argument("rows must have equal sizes");
    for (std::size_t column = 0; column < columns; ++column) {
        for (const Vector& row : features) result.means[column] += row[column];
        result.means[column] /= static_cast<double>(rows);
        for (const Vector& row : features) {
            const double difference = row[column] - result.means[column];
            result.standard_deviations[column] += difference * difference;
        }
        result.standard_deviations[column] = std::sqrt(result.standard_deviations[column] / rows);
        if (result.standard_deviations[column] == 0.0) result.standard_deviations[column] = 1.0;
    }
    for (Vector& row : result.features) for (std::size_t column = 0; column < columns; ++column)
        row[column] = (row[column] - result.means[column]) / result.standard_deviations[column];
    return result;
}

} // namespace lasso

