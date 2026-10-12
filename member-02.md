# Individual Week 2 Report: 
Name: Karungi Mary Gorret (member-02)
Reg No: 25/U/0832
Branch: preprocessing`
Assigned part: Data preprocessing (input validation)
Pull request:https://github.com/alindamusiimenta/Group-14-Submissions/pull/3
## 1. What my part means
Data preprocessing is one stage in the LASSO pipeline. My part is the validator of this stage. It receives the feature matrix and the target vector, confirms they are well-formed, and either passes them on unchanged or stops the program with a clear error. Later steps (standardizing features, centering the target, coordinate descent) all assume the data has a consistent shape, so this check has to come first.

## 2. Files changed
`src/member02_preprocessing.cpp`

## 3. What I did
I added the function `check_preprocessing_input(const Matrix& features, const Vector& target)` in the `lasso` namespace. It checks three things:

1. `features` is not empty, and its number of rows equals the number of target values.
2. The first row contains at least one feature.
3. Every row has the same number of features as the first row.

If any check fails, it throws `std::invalid_argument` with a specific message. This stops a later calculation from failing mysteriously, for example through out-of-bounds access.

The empty check comes first, so `features[0]` in step 2 is always safe. The cost is O(n) in the number of rows.

## 4. Class structure of my part
**What class did you create?**
None. My part is one free function inside the `lasso` namespace. It uses two types from `week2.hpp`: `Matrix` (the feature table, one row per sample) and `Vector` (one row of features, or the target values).

**Why no class?**
The check is stateless. Data goes in, it is tested, and the function returns or throws.
**What functions operate on the data?**
Only `check_preprocessing_input`, which returns `void`.

## 5. Design choices
- **Fail early:** invalid shapes are caught at the entry point, not deep inside the solver.
- **Clear errors:** each failure has its own message, which makes debugging faster.
- **Efficiency and safety:** `const&` parameters avoid copies and prevent accidental changes.
- **Separation of concerns:** validation is separate from computation, so it can be tested on its own.

## 6. Limitations
-The function checks only shapes. It does not reject `NaN` or infinite values.
- Values in the target vector are not validated.

## 7. What I will add in Week 3
I will add clearer handling for missing values, including `NaN`/infinite checks with `std::isfinite`, and explain which rows are rejected and why.

## 8. References
The group consulted the course notes and Robert Tibshirani's paper, "Regression Shrinkage and Selection via the Lasso," *Journal of the Royal Statistical Society: Series B*, 1996. C++ syntax and standard-library behavior were checked with cppreference where needed. 