# Individual final report member02

**Name: Karungi Mary Gorret*
**Reg No:25/U/0832*
**Branch: member-02-preprocessing*
**Assigned part: Data preprocessing and finite-value validation*

## 1. What my part means
This is the Week 4 continuation of my Week 3 module. In Week 2 I checked that the data has a valid shape. In Week 4 I check that the numbers themselves are usable. A fair LASSO experiment needs this, because one `NaN` or infinity makes means, standard deviations, predictions, and error metrics invalid for the whole dataset.

## 2. Files changed
`src/member02_preprocessing.cpp` (includes `lasso/week3.hpp`)

## 3. What I added
I added the function `bool all_finite(const Matrix& features, const Vector& target)` in the `lasso` namespace. It returns `true` only when every number in the feature matrix and in the target vector is finite.

How it works:
1. If the number of feature rows differs from the target size, it returns `false`.
2. It goes through the rows one by one.
3. For each row, it tests every feature value with `std::isfinite` (from `<cmath>`).
4. It then tests the matching target value with `std::isfinite`.
5. The first `NaN` or infinity found makes it return `false` immediately. If none is found, it returns `true`.
The function stops at the first bad value, so the cost is O(n x p) in the worst case (n rows, p features), and much less when bad data appears early.

## 4. structure of the code
**What functions operate on the data?**
- `check_preprocessing_input(features, target)` returns `void` and throws `std::invalid_argument` if the shape is wrong.
- `all_finite(features, target)` returns `bool` and reports whether all numbers are finite.

**How are they used by the rest of the program?**
1. The loader reads the data into a `Matrix` and a `Vector`.
2. `check_preprocessing_input` confirms the shape.
3. `all_finite` confirms the values.
4. Only then do standardizing, centering, and the LASSO solver run.
   
## 5. Classes
classes were not applicable for this part

## 6. How it fits into the full pipeline
My part receives the loaded data and gives a clear pass or fail result to the next stage. It keeps the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules as the rest of the group. If `all_finite` returns `false`, the caller must stop or report the problem before any numerical processing starts.

## 7. Design choices
- **Fail early:** bad numbers are caught before they spread through the calculations.
- **Early exit:** the function returns at the first bad value instead of scanning everything.
- **Safety:** `const&` parameters avoid copies and accidental changes.
- **Separation of concerns:** shape checking and value checking are two separate functions that can be tested alone.

## 8. Limitations
- `all_finite` returns only `true` or `false`. It does not say which row or column has the bad value.
- It does not check for an empty matrix or for rows of different lengths. It relies on `check_preprocessing_input` running first.

## 9. References
- Tibshirani, R. (1996). "Regression Shrinkage and Selection via the Lasso." *Journal of the Royal Statistical Society: Series B*, 58(1), 267-288.
- Course notes.
- cppreference.com, for `std::isfinite` and other standard-library functions.
