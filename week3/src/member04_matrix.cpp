#include "lasso/week2.hpp"
#include <stdexcept> //for std::invalid _argument

namespace lasso {
//Computes the matrix - vector product
Vector multiply_rows(const Matrix& matrix, const Vector& values) {
    Vector result;
    //process one row at a time
    for (const Vector& row : matrix) {
        //Dot product is only defined when lengths match 
        if (row.size() != values.size()) throw std::invalid_argument("matrix row and vector must match");
        //Dot product of this row with values
        double total = 0.0;
        for (std::size_t i = 0; i < row.size(); ++i) total += row[i] * values[i];
        result.push_back(total);// store this row's result
    }
    return result;
}

} // namespace lasso