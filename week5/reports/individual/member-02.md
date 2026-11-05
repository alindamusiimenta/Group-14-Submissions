**Member 2 Final Report:* 
**Data Preprocessing and Validation*
**Karungi Mary Gorret·*
 **Reg No: 25/U/0832·* 
 **Group 14 · Branch member-02-preprocessing*
**Project: LASSO Regression From Scratch, a reusable C++17 library·* 
**Coverage: Weeks 1 to 5, combined report*

## 1.Task
• Assigned task: Member 2, data preprocessing and validation.
• Main file: src/member02_preprocessing.cpp (Weeks 1 to 4).
• Week 5 file: include/numerics/numeric_types.hpp (numeric conversion templates).
• One-line summary: my part makes the library refuse bad data and unsafe number conversions with a clear error, instead of producing a wrong answer.

## 2. Project overview
The group built a small C++17 library that implements  LASSO regression from first principles. LASSO is linear regression with an L1 penalty that shrinks unhelpful coefficients to exactly zero, so the model keeps only the features that matter.

LASSO cost = squared error / (2n) + lambda * (|b1| + |b2| + ... + |bk|)

# The pipeline, in order: load the CSV, validate the data (my part), split into train and test, choose lambda by cross-validation, scale the features using training rows only, train with coordinate descent and soft-thresholding, then predict and report MAE, MSE, RMSE and R-squared.

Why validation matters. LASSO does maths on every number. A missing row, a short row or one NaN does not crash the program. It silently spreads into the means, the coefficients and the final scores. Rejecting bad data first, with a clear message, is the purpose of my part.

## 3. Work done each week

## Week 1: foundation
I wrote two small functions that return true or false and never throw, so other members can use them in their own error handling.
• rows_match_target is true when there is at least one row and exactly one target value per row.
• rows_have_equal_width is true when every row has the same number of features as the first row.

## Week 2: one complete checker
I combined the checks into check_preprocessing_input(features, target), which returns void and throws std::invalid_argument with a different message for each problem:
Problem found
# Error message
No data, or number of rows differs from number of targets
features and target must have matching rows
The first row has zero columns
at least one feature is required
A row has a different width than the first row
feature rows must have equal sizes

## Week 3: finite-value validation
I added bool all_finite(const Matrix&, const Vector&). It returns false as soon as it finds NaN or infinity (std::isfinite) in any feature value or any target value, and true otherwise. One NaN would make the means, standard deviations, predictions and error metrics invalid for the whole dataset. I made it return a bool instead of throwing, so the calling code decides what to do.

## Week 4: stricter and more consistent
• The finite-value checks were moved inside check_preprocessing_input, so one call now validates the shape and the values together. It throws feature values must be finite or target values must be finite.
• all_finite was made safer. It now returns false for empty data, zero columns, uneven rows or mismatched counts before it tests the numbers.
• The code was tidied (row_index, column_count, braces on every branch).

## Week 5: safe numeric conversion with templates
I wrote numerics/numeric_types.hpp. It converts user data of any numeric type into the double values the LASSO code works with, and rejects bad values before they reach training. It is used by Matrix<T>, CsvDataProcessor<T>, TypedLinearRegression and TypedLassoRegression.
• is_numeric_v<T>: a type trait, true for arithmetic types except bool (const and volatile are ignored).
• checked_numeric_cast<To, From>(value): converts safely or throws.
• to_double<T>, to_double_vector<T>, to_double_matrix<T>: convert one value, a list and a table. The matrix version also rejects uneven rows.
checked_numeric_cast works in steps:
1. static_assert rejects non-numeric types at compile time.
2. The value is widened to long double so the checks cannot overflow.
3. NaN and infinity are rejected (std::invalid_argument).
4. For an integer destination, a fractional value is rejected (std::invalid_argument), then the range is checked (std::out_of_range).
5. For a floating-point destination, the range is checked against lowest() and max().
6. The conversion is done from the original value, and for floating-point targets the result is tested again, because narrowing (for example double to float) can round to infinity.

## 4. Template used (Week 5)
• Template names: numerics::checked_numeric_cast<To, From>, is_numeric_v<T>, to_double<T>, to_double_vector<T>, to_double_matrix<T>.
• Purpose: convert numeric data of any type into double, and reject bad values before training. check_preprocessing_input and all_finite then check that the feature matrix and target vector have matching rows, equal-length rows, at least one feature, and only finite values.
• Why a template helps: datasets can arrive as short, int, float, double or other types. One set of templates handles all of them, with no duplicated conversion code per type, and the same validation runs whatever the input type is.
• Supported types: any arithmetic type except bool (int, long, long long, unsigned types, float, double, long double). Other types, including bool, are rejected at compile time by static_assert.
• Types covered by my tests: short, int, float, long long and double, through Matrix<short>, Matrix<int>, TypedLinearRegression<short, float>, TypedLassoRegression<int, float> and CsvDataProcessor<short>.

# Conversion and precision limits
• NaN and infinity are rejected (std::invalid_argument).
• A fractional value cannot be converted to an integer type (std::invalid_argument).
• A value outside the destination type's range throws std::out_of_range.
• Integer range checks use an exclusive power-of-two upper bound (2^digits). On platforms where long double is no wider than double, converting the 64-bit integer maximum can round up, so a direct comparison with the maximum would be unsafe.
• Narrowing a floating-point value can round to infinity, so the result is checked again after the cast.
• Large integers converted to double can lose precision beyond 2^53. The range check does not catch this.

## 5.3 The full library working
Running the demos from the week5 folder (so data/input/sample.csv is found), the Week 4 demo reported:
• 9 training rows and 3 held-out test rows.
• Chosen lambda 0.0010, the lowest mean cross-validation RMSE, with a mean 4-fold validation RMSE of 0.0871.
• Held-out test MAE 0.0510, RMSE 0.0716 and R-squared 0.9977.
• 2 of 3 features kept; the third coefficient was shrunk to 0.0000.
The data is a small synthetic teaching dataset, so these scores demonstrate the method and are not a claim about real-world accuracy.

## 6. Tests and results
• Test cases covering this part: valid finite rectangular data; empty data; mismatched feature and target rows; uneven rows; NaN and infinity in the features and the target; a fractional value to an integer type; an out-of-range integer; and a type that is not allowed. Each bad case must throw an error (or return false for all_finite).
• Command: ctest --test-dir .\week5\build --output-on-failure
• Result: 100% tests passed out of 5 (Week 2, Week 3 and Week 4 LASSO, linear regression and numeric templates).
• Build: the project builds with CMake and MinGW GCC 16.2.0 with no errors.

## 7. Design questions
1. Why an exclusive power-of-two upper bound instead of numeric_limits<To>::max() for integer targets? The maximum of a 64-bit integer cannot always be represented exactly in long double (on some platforms it is no wider than double). It can round up to 2^63, which would let an out-of-range value pass a <= check. 2^digits is exactly representable, so a >= comparison against it is always correct.

2. Why both a throwing check (check_preprocessing_input) and a non-throwing one (all_finite)? The throwing version gives a specific message and stops the pipeline when invalid data should never get through. The bool version lets calling code test data without exceptions, for example to decide whether to skip or report a dataset.

3. Why exceptions and not assert? assert is removed in optimized release builds, so the protection would vanish exactly when the library is used for real. Exceptions always run and carry a message that tests can catch.

4. Why static_assert for the type check? It fails at build time, so a wrong type such as bool never reaches a running program.
5. Why validate at the start and not later? Failing early is cheaper, and the error points to the real cause. A NaN found at the end says nothing about where it came from.

6. What does my part not do? It does not detect outliers, fill in missing values or detect duplicate rows. all_finite also repeats some logic from check_preprocessing_input; a cleaner design would have it call the checker inside a try/catch.
## 8. UML
No classes are defined in my files. The work consists of function templates and free functions in two namespaces:

![alt text](<uml-member2-preprocessing.jpeg>)


namespace lasso
  check_preprocessing_input(const Matrix&, const Vector&) : void   (throws)
  all_finite(const Matrix&, const Vector&)                : bool

Calls:  to_double_matrix --> to_double_vector --> to_double --> checked_numeric_cast
## 9. Challenges and how I addressed them
Challenge
How it was handled
One bad value silently ruins the whole result
Validate before any calculation and throw a clear error.
Silent conversion bugs: static_cast<short>(40000) wraps around and static_cast<int>(3.5) drops the decimals
Wrote checked_numeric_cast, which throws instead of corrupting the value.
Range checks themselves can overflow or round
Widened to long double and used an exclusive power-of-two bound.
Ten members working in parallel
Used the shared Vector, Matrix and error rules so the modules fit together.
My compiler was too old: GCC 6.3 cannot build C++17
Installed GCC 16.2.0 through MSYS2 and put it first on the PATH.

## 10. Lessons learned
• Validate early. A clear error at the start is better than a wrong answer at the end.
• Silent conversions are dangerous. A checked conversion costs very little and prevents hidden bugs.
• Test the bad cases as carefully as the good ones.
• Throwing errors suits stopping the pipeline, and a bool result suits quick yes/no questions.
• Shared types and agreed error rules make teamwork possible.
• Tool versions matter. Check your compiler before you debug your code.
## 11. AI assistance
**Tool:** Claude (Anthropic)
**What it was used for:**
- Adding explanatory comments to my code (`member02_preprocessing.cpp` and `numeric_types.hpp`). The logic of my functions is my own work. I reviewed all generated comments and text against my code, to understand more how every function works.
Debugging the code (`member02_preprocessing.cpp` and `numeric_types.hpp`) and helping me find and fix errors.

**Why:** To make my code easier to read, to help me understand  and to save time on documentation.
To fix errors faster

## 12. References
Robert Tibshirani, "Regression Shrinkage and Selection via the Lasso," Journal of the Royal Statistical Society: Series B, 1996, and cppreference.com for C++ standard-library behavior. [Keep only what you actually used.]


