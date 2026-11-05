# LASSO Regression From Scratch — Week 1

## 1. What this project is about

This project is a small reusable C++ library for learning how **LASSO regression** works from the beginning. We are not using a ready-made machine-learning library. Instead, we are building the important parts ourselves using the C++ ideas we have learned: vectors, simple classes, functions, loops, calculations, file input, and error handling.

The project will eventually use LASSO to predict a numerical value from several input features. For example, it could predict an exam score from study hours, attendance, and assignment marks, or predict a house price from house size, bedrooms, and location-related measurements.

The Week 1 version is the foundation. It does not yet contain the complete coordinate-descent LASSO training algorithm. It prepares the data structures, calculations, baseline model, LASSO cost function, soft-thresholding function, tests, and project structure that will be extended in Weeks 2 and 3.

## 2. What LASSO means

LASSO stands for **Least Absolute Shrinkage and Selection Operator**. It is a form of linear regression with an additional penalty.

Ordinary linear regression tries to find coefficients that make predictions close to the actual target values:

```text
y_hat = b0 + b1*x1 + b2*x2 + ... + bk*xk
```

LASSO adds a penalty based on the absolute values of the coefficients:

```text
LASSO cost = prediction error + lambda * sum of absolute coefficients
```

The penalty encourages unnecessary coefficients to become zero. When a coefficient becomes zero, the corresponding feature is not used by the model. This is why LASSO can perform **feature selection** as well as prediction.

The value `lambda` controls the strength of the penalty. A value of zero gives ordinary regression. A larger value produces more shrinkage and may remove more features. Choosing `lambda` will be added in a later week.

## 3. The problem we are solving

Given a dataset containing a target and one or more features, the final project should:

1. Load the numerical data.
2. Check that the data is valid.
3. Preprocess and scale the features.
4. Start with a linear-regression baseline.
5. Calculate the LASSO cost.
6. Use L1 regularization and coordinate descent to learn coefficients.
7. Use soft-thresholding to shrink coefficients.
8. Identify features whose coefficients become zero.
9. Tune `lambda` and evaluate the model.
10. Use the final coefficients to make predictions.

The current Week 1 program completes the foundation for these steps. The later weeks will add the complete optimizer and final evaluation process.

## 4. What the current Week 1 code does

### 4.1 Vector and matrix types

The header defines two simple type names:

```cpp
using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;
```

A `Vector` is a list of decimal numbers. A `Matrix` is a list of vectors, so it can represent rows and columns of numerical data.

For example:

lasso::Vector values{1, 2, 3};
lasso::Matrix data{{1, 2}, {3, 4}};

The matrix contains two rows:

1  2
3  4

### 4.2 The `Dataset` structure

The `Dataset` structure stores two related pieces of information:

```cpp
struct Dataset {
    Matrix features;
    Vector target;
};
```

`features` contains the input columns. `target` contains the value that we want to predict. Each target value must match the feature row at the same position.

For example:

features row 0 -> target 0
features row 1 -> target 1
features row 2 -> target 2

Keeping the rows and targets aligned is important. If they are mixed up, the model learns the wrong relationship.

### 4.3 The `LassoModel` class

The project includes a beginner-level class:

```cpp
class LassoModel {
public:
    void fit_baseline(const Vector& x, const Vector& y);
    double predict(double x) const;
    double intercept() const;
    double slope() const;
};
```

The class stores the intercept, the slope, and whether the model has been fitted. This introduces encapsulation: the model keeps its learned values inside the object and provides functions for using them.

In Week 1, the class stores a simple one-feature linear-regression baseline. In a later week, it can be extended or joined with a multiple-feature LASSO model.

### 4.4 Fitting the baseline

The example creates a model object:

```cpp
lasso::LassoModel model;

Then it fits the baseline using input and target vectors:

```cpp
model.fit_baseline(
    {1, 2, 3, 4, 5},
    {52, 55, 61, 66, 70}
);
```

The program calculates the best straight line for the data:

```text
y = intercept + slope*x
```

For this example, the calculated line is approximately:

```text
y = 46.700 + 4.700*x
```

The values are calculated using means, differences from the means, a numerator, and a denominator. The code uses simple loops so the calculation can be followed by a beginner.

### 4.5 Making a prediction

After fitting, the program can predict a value:

```cpp
double answer = model.predict(6.0);
```

The calculation is:

46.700 + 4.700 * 6 = 74.900

The example prints:

```text
prediction for x=6 = 74.900
```

### 4.6 The dot-product function

The dot product multiplies values in matching positions and adds the results:

```text
[1, 2, 3] dot [4, 5, 6]
= 1*4 + 2*5 + 3*6
= 32
```

The function is:

```cpp
double dot(const Vector& left, const Vector& right);
```

This operation is important because a prediction from several features is normally calculated by multiplying each feature by its coefficient and adding the results.

### 4.7 Matrix-vector multiplication

The matrix-vector function applies the dot product to every row of a matrix. For example:

```text
matrix = [[1, 2],
          [3, 4]]
vector = [2, 1]
```

The result is:

```text
row 1: 1*2 + 2*1 = 4
row 2: 3*2 + 4*1 = 10
result = [4, 10]
```

This is a simple introduction to the matrix operations that future multiple-feature LASSO code will need.

### 4.8 The LASSO cost function

The function:

```cpp
double lasso_cost(
    const Matrix& features,
    const Vector& target,
    const Vector& coefficients,
    double lambda
);
```

calculates two parts:

1. The squared prediction error.
2. The L1 penalty, which is `lambda` multiplied by the sum of the absolute coefficient values.

The formula used is:

```text
cost = squared_error / (2*n) + lambda * sum(abs(coefficients))
```

For Week 1, this function evaluates a set of coefficients supplied by the caller. It does not yet search for the best coefficients. Coordinate descent will repeatedly change the coefficients and call a similar calculation in Week 2.

The future optimizer should normally keep the intercept outside the penalty, because LASSO generally penalizes feature coefficients but not the intercept. This convention will be made explicit when the full model is added.

### 4.9 Soft-thresholding

The function:

```cpp
double soft_threshold(double value, double threshold);
```

shrinks a value toward zero:

```text
soft_threshold(5, 2) = 3
soft_threshold(-5, 2) = -3
soft_threshold(1, 2) = 0
```

It is implemented with simple `if` statements. If the value is larger than the threshold, the threshold is subtracted. If the value is smaller than the negative threshold, the threshold is added. Otherwise, the result is zero.

This function is one of the main ideas behind LASSO feature selection. Small coefficients can become exactly zero.

### 4.10 CSV loading

The function:

```cpp
Dataset load_csv(const std::string& path, bool has_header = true);
```

opens a CSV file, optionally skips the header row, reads each line, converts the cells to numbers, and stores the first value as the target. The remaining values become the feature row.

The sample file is:

```csv
target,feature_1,feature_2
5,1,2
4,2,1
7,3,2
```

The first row after the header is interpreted as:

```text
target = 5
features = [1, 2]
```

The current loader is intentionally simple. More complete preprocessing, missing-value handling, and feature scaling will be developed by the assigned group members.

## 5. How errors are handled

The program checks invalid input and throws an exception instead of continuing with an incorrect calculation. Examples include:

- Vectors with different sizes.
- Too few observations.
- A matrix with rows of different widths.
- A coefficient vector with the wrong size.
- A negative LASSO `lambda`.
- A negative soft-threshold value.
- A CSV file that cannot be opened.
- A CSV cell that is not numeric.
- Calling `predict` before fitting the model.

For example:

```cpp
try {
    lasso::dot({1}, {1, 2});
} catch (const std::invalid_argument& error) {
    std::cout << error.what();
}
```

This is part of making the library reusable and safe for another C++ programmer.

## 6. How to run the project

Requirements:

- A C++17 compiler such as GCC, Clang, or MSVC.
- CMake 4.4.4 or newer for the recommended build method.
- No external machine-learning library is required.

### Recommended CMake method

From inside the project directory, run:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/lasso_week1_demo
```

The commands have these meanings:

- `cmake -S . -B build` reads `CMakeLists.txt` and prepares a build directory.
- `cmake --build build` compiles the library, tests, and example.
- `ctest --test-dir build --output-on-failure` runs the automated tests.
- `./build/lasso_week1_demo` runs the demonstration program.

### Direct `g++` method

If CMake is not installed, compile the tests directly:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    -Iinclude \
    src/member*.cpp \
    tests/test_week1.cpp \
    -o lasso_tests
```

Run the tests:

```bash
./lasso_tests
```

Compile the example:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    -Iinclude \
    src/member*.cpp \
    examples/week1_demo.cpp \
    -o lasso_example
```

Run it:

```bash
./lasso_example
```

The expected output is approximately:

```text
All LASSO Week 1 tests passed.
baseline: y = 46.700 + 4.700x
prediction for x=6 = 74.900
soft threshold(5, 2) = 3.000
```

## 7. What the tests check

`tests/test_week1.cpp` checks the normal and invalid cases of the Week 1 foundation.

The tests verify that:

- The dot product returns 32 for `[1,2,3]` and `[4,5,6]`.
- Matrix-vector multiplication returns `[4,10]` for the sample matrix.
- Soft-thresholding shrinks positive and negative values correctly.
- Values inside the threshold become zero.
- The LASSO cost includes the L1 penalty.
- The baseline regression recovers the relationship `y = 1 + 2x`.
- The `LassoModel` class predicts correctly after fitting.
- Invalid vector sizes produce `std::invalid_argument`.

Tests are important because successful compilation alone does not prove that numerical calculations are correct.

## 8. Project folders

- `include/`: public header files that users include.
- `src/`: implementation files containing the calculations, one file per member.
- `tests/`: automated tests for expected and invalid behavior.
- `examples/`: small programs showing how to use the library.
- `data/input/`: sample input data.
- `data/output/`: reserved for generated output in later weeks.
- `reports/`: weekly progress reports and assignment information.
- `CMakeLists.txt`: build instructions for CMake.

## 9. Three-week development plan

### Week 1: Foundation

The group establishes the project structure, defines the data format, implements simple vector and matrix operations, creates the linear-regression baseline, calculates the LASSO cost, implements soft-thresholding, adds simple error handling, and writes initial tests.

### Week 2: Complete the main LASSO algorithm

The group will add preprocessing and feature scaling, make the baseline reusable, connect L1 regularization to the model, implement coordinate descent, use soft-thresholding in each coordinate update, add convergence checks, and report selected features.

### Week 3: Tune and evaluate

The group will add lambda tuning, model evaluation, prediction for one row and many rows, train/validation/test comparisons, final examples, and more edge-case tests. The code and documentation will then be integrated for final submission.

### Final submission week

The group will test the project from a clean environment, complete the README and final report, confirm all member contributions and GitHub commits, update the AI-use declaration, prepare the presentation, and package the final source code, headers, tests, examples, data, reports, and build files.

## 10. The 10 member assignments

The detailed assignment table is in `reports/week-01.md`. The assigned topics are dataset loading, data preprocessing, feature scaling, matrix and vector operations, linear-regression baseline, LASSO cost function, L1 regularization, coordinate descent optimization, soft-thresholding, feature selection, hyperparameter tuning, model evaluation, and prediction.

## 11. Scope decisions

SMOTE is not included because it is primarily an imbalanced-classification technique and is not automatically appropriate for a continuous LASSO-regression problem. It should only be added if the course gives a separate requirement and the group can justify it.

The Week 1 code is intentionally simple. It uses loops and straightforward functions rather than advanced templates, external packages, or complicated numerical libraries. Advanced optimization is planned for the next week so that the group can build and explain it gradually.

## 12. Week 1 limitation

This is not yet a complete LASSO trainer. The current code evaluates the LASSO cost and demonstrates soft-thresholding, but it does not yet use coordinate descent to learn the best coefficients. That is intentional: Week 1 establishes the foundation, and Week 2 will add the optimizer.

## Arranged continuation structure

- Member 1: `data/input/member01_training.csv` and the dataset-loading section in `src/lasso_regression.cpp`
- Members 2, 3, 4, 8, and 9: implementation files in `src/`
- Members 5, 6, and 7: implementation files in `src/` with demonstrations in `examples/`
- Member 10: `CMakeLists.txt`, `tests/test_week1.cpp`, and `examples/week1_demo.cpp`
- Individual reports: `reports/individual/`

The implementation remains Week 1 foundation work. The folder arrangement is changed for continuity, not to add Week 2, Week 3, or Week 4 algorithms. See `ARRANGEMENT-NOTES.md` for the exact mapping.
