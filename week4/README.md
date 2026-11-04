# LASSO Regression From Scratch — Week 4

## 1. What this project is about

This project is a small reusable C++ library for learning how **LASSO regression** works from the beginning. We are not using a ready-made machine-learning library. Instead, we build the important parts ourselves using the C++ ideas we have learned: vectors, simple classes, functions, loops, calculations, file input, and error handling.

The project uses LASSO to predict a numerical value from several input features. For example, it can predict an exam score from study hours, attendance, and assignment marks.

The Week 4 version completes the workflow. The library can now load data, check it, split it, scale it, fit a LASSO model, **choose lambda with cross-validation**, predict new rows, and measure how good the predictions are.

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

The value `lambda` controls the strength of the penalty. A value of zero gives ordinary regression. A larger value produces more shrinkage and may remove more features. In Week 1 we said that choosing `lambda` would be added in a later week. Week 4 adds it.

## 3. The problem we are solving in Week 4

If `lambda` is too small, the model keeps too many features and may only memorize the training data. If `lambda` is too large, the model throws away useful features. So we need a fair way to pick it.

We cannot judge `lambda` by how well the model fits the data it was trained on, because it will always look good there. Instead, we must test it on rows that the model has not seen.

Given a dataset containing a target and one or more features, the final project should:

1. Load the numerical data.
2. Check that the data is valid.
3. Split the rows into training rows and held-out test rows.
4. Choose `lambda` with k-fold cross-validation, using the training rows only.
5. Learn the scaling values from the training rows only.
6. Fit the LASSO coefficients with coordinate descent.
7. Predict the held-out test rows.
8. Measure the errors with MAE, MSE, RMSE, and R-squared.
9. Report which features LASSO kept.

Week 4 joins all of these steps together and adds step 4.

One mistake we must avoid is **data leakage**. If the scaler or the `lambda` search ever sees the test rows, the final test score looks better than it really is. The Week 4 code is written so that the test rows are never used for scaling or for choosing `lambda`.

## 4. What the current Week 4 code does

### 4.1 Vector, matrix, and dataset types

The header defines the simple types used everywhere in the project:

```cpp
using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

struct Dataset {
    Matrix features;
    Vector target;
};
```

A `Vector` is a list of decimal numbers. A `Matrix` is a list of vectors, so it can represent rows of numerical data. A `Dataset` keeps the feature rows and the target values together. Each target value must match the feature row at the same position.

### 4.2 Splitting the data

The function:

```cpp
TrainTestSplit split_dataset(const Dataset& data, double train_fraction, unsigned seed = 42);
```

shuffles the row numbers with a fixed seed and then puts the first part into the training set and the rest into the test set. The same seed always gives the same split, so the results can be repeated.

For example, with 12 rows and `train_fraction = 0.75`:

```text
training rows = 12 * 0.75 = 9
test rows     = 12 - 9    = 3
```

### 4.3 Scaling with training values only

Features such as study hours (1 to 8) and attendance (60 to 96) are on very different scales, so LASSO scales them first. The project stores the scaling values in a small structure:

```cpp
struct FittedScaler {
    Vector means;
    Vector standard_deviations;
    Matrix transform(const Matrix& features) const;
};
```

`fit_scaler()` learns the means and standard deviations from the **training rows only**. Then `transform()` applies those saved values to any rows. A value equal to the training mean becomes 0 after scaling.

The test rows are scaled with the training means, not with their own means. This is how leakage is avoided.

### 4.4 Predicting many rows

The function:

```cpp
Vector predict_rows(const Matrix& features, const Vector& coefficients, double intercept = 0.0);
```

makes one prediction for every feature row. For each row it multiplies every feature by its coefficient, adds the results, and then adds the intercept. For example:

```text
features     = [1, 2]
coefficients = [2, 3]
intercept    = 4

prediction = 1*2 + 2*3 + 4 = 12
```

If the number of values in a row does not match the number of coefficients, the function throws `std::invalid_argument`.

Cross-validation uses this function to predict the held-out rows of every fold.

### 4.5 The LASSO solver

The function `coordinate_descent()` learns the coefficients. It starts with all coefficients at zero and the intercept at the mean of the target. Then it repeats passes over the features. For each feature it calculates:

```text
average_residual = average of (feature * (target - prediction without this feature))
average_square   = average of (feature * feature)

coefficient = soft_threshold(average_residual, lambda) / average_square
```

After each pass the intercept is updated separately. The intercept is **not** penalized, as planned in Week 1. The solver stops when the largest change in a pass is smaller than the tolerance, or when the maximum number of passes is reached.

Soft-thresholding is the step that can make a coefficient exactly zero:

```text
soft_threshold(5, 2)  = 3
soft_threshold(-5, 2) = -3
soft_threshold(1, 2)  = 0
```

### 4.6 Measuring the error

The function `evaluate_regression()` compares actual values with predicted values and returns four numbers:

- **MAE**: the average size of the errors.
- **MSE**: the average of the squared errors.
- **RMSE**: the square root of the MSE. It is in the same units as the target.
- **R-squared**: how much of the variation in the target the model explains. A value close to 1 is good.

For example:

```text
actual    = [1, 2, 3]
predicted = [2, 2, 4]

errors         = 1, 0, 1
MAE            = (1 + 0 + 1) / 3 = 0.667
squared errors = 1, 0, 1
MSE            = 2 / 3 = 0.667
RMSE           = sqrt(0.667) = 0.816
```

Cross-validation uses RMSE to compare different `lambda` values.

### 4.7 K-fold cross-validation

This is the main new part of Week 4. The function:

```cpp
CrossValidationResult cross_validate_lambda(const Dataset& data, double lambda,
                                            int folds, unsigned seed);
```

tests **one** `lambda` value. The result is stored in:

```cpp
struct CrossValidationResult {
    double lambda;
    double mean_validation_rmse;
    std::vector<double> fold_rmse;
};
```

First the row numbers are shuffled with the seed. Then the row at shuffled position `p` is placed in fold `p % folds`. For example, with 8 rows and 4 folds:

```text
shuffled order:  5  2  7  0  3  6  1  4     (example order; the real order depends on the seed)
position:        0  1  2  3  4  5  6  7
position % 4:    0  1  2  3  0  1  2  3

fold 0 validates on rows 5 and 3
fold 1 validates on rows 2 and 6
fold 2 validates on rows 7 and 1
fold 3 validates on rows 0 and 4
```

For every fold, the function does these steps:

1. Put the fold's rows aside as the **validation rows**. All other rows are the **training rows**.
2. Fit a scaler on the training rows only.
3. Scale both the training rows and the validation rows with that scaler.
4. Fit LASSO on the scaled training rows.
5. Predict the validation rows with `predict_rows()`.
6. Calculate the RMSE between the predictions and the true validation targets.

At the end, the function averages the fold RMSE values. This average is `mean_validation_rmse`. A lower value is better.

Because the same seed always gives the same shuffle, the folds are the same every time the function runs.

### 4.8 Choosing the best lambda

The function:

```cpp
CrossValidationResult select_lambda_by_cross_validation(const Dataset& data,
                                                        const Vector& candidates,
                                                        int folds, unsigned seed);
```

tries every `lambda` in the candidate list. It uses the **same seed for every candidate**, so all candidates are compared on identical folds. It keeps the candidate with the lowest mean validation RMSE.

Imagine these numbers, used only to show the idea:

```text
lambda 0.001 -> mean RMSE 0.09   <- lowest, so it is chosen
lambda 0.010 -> mean RMSE 0.12
lambda 0.100 -> mean RMSE 0.31
```

The Week 3 helper `choose_lambda()` is still in the library. It picks the candidate with the lowest cost on the training data, so it is only a simple demonstration. The Week 4 model-selection step uses cross-validation instead.

### 4.9 Putting it together

The final workflow keeps the test rows completely separate:

```cpp
const lasso::Dataset data = lasso::load_csv("data/input/sample.csv");

// 1. Lock away the test rows.
const auto split = lasso::split_dataset(data, 0.75, 42);

// 2. Choose lambda using the training rows only.
const auto best = lasso::select_lambda_by_cross_validation(
                      split.train, {0.001, 0.01, 0.1}, 4, 42);

// 3. Scale using the training rows only, then fit the final model.
const auto scaler = lasso::fit_scaler(split.train.features);
const auto fit    = lasso::coordinate_descent(scaler.transform(split.train.features),
                                              split.train.target, best.lambda);

// 4. Predict and evaluate the test rows once.
const auto predictions = lasso::predict_rows(scaler.transform(split.test.features),
                                             fit.coefficients, fit.intercept);
const auto metrics  = lasso::evaluate_regression(split.test.target, predictions);
const auto selected = lasso::selected_features(fit.coefficients);
```

`selected_features()` returns the positions of the coefficients that are not (almost) zero. These are the features that LASSO decided to keep.

### 4.10 The one-feature baseline

The project also keeps a simple one-feature linear regression in the `linreg` namespace. It is used as a baseline to compare with LASSO. The class keeps its values private and gives functions for using them:

```cpp
class LinearRegression {
public:
    FitResult fit_closed_form(const std::vector<double>& x, const std::vector<double>& y);
    FitResult fit_gradient_descent(...);
    FitResult fit_stochastic_gradient_descent(...);
    double predict(double x) const;
    double intercept() const;
    double slope() const;
    ...
};
```

For the study-hours example:

```text
hours  = 1, 2, 3, 4, 5
scores = 52, 55, 61, 66, 70

y = 46.700 + 4.700*x
prediction for x = 6: 46.700 + 4.700 * 6 = 74.900
```

The baseline accepts one feature only, so it is not a replacement for the multi-feature LASSO.

### 4.11 Demo result

With the bundled synthetic data and the seed 42, the Week 4 demo used 9 training rows and 3 held-out test rows:

| What | Value |
|------|-------|
| Selected lambda | 0.0010 |
| Mean 4-fold validation RMSE | 0.0871 |
| Test MAE | 0.0510 |
| Test RMSE | 0.0716 |
| Test R-squared | 0.9977 |

The data is small and artificial. These numbers show that the workflow runs from start to finish. They do not show how accurate the model would be on real data.

## 5. How errors are handled

The program checks invalid input and throws an exception instead of continuing with an incorrect calculation. Examples include:

- Vectors with different sizes.
- Empty data, or a different number of feature rows and target values.
- A matrix with rows of different widths.
- Feature or target values that are NaN or infinity.
- A coefficient vector with the wrong size.
- A negative or non-finite `lambda`.
- An empty list of `lambda` candidates.
- A number of folds below 2, or larger than the number of rows.
- A train fraction that is not between 0 and 1.
- A negative feature-selection threshold.
- A CSV file that cannot be opened, or a CSV cell that is not numeric.
- Calling `predict` before fitting the baseline model.
- A baseline `x` that has only one distinct value.

For example:

```cpp
try {
    lasso::cross_validate_lambda(data, 0.1, 1, 42);   // only 1 fold
} catch (const std::invalid_argument& error) {
    std::cout << error.what();
}
```

The message is: `folds must be between two and the number of rows`.

This is part of making the library reusable and safe for another C++ programmer.

## 6. How to run the project

Requirements:

- A C++17 compiler such as GCC, Clang, or MSVC.
- CMake (the required version is set in `CMakeLists.txt`).
- No external machine-learning library is required.

The final check was done on Windows with GCC (MinGW), CMake, and Ninja.

### Recommended CMake method

From inside the project directory, run:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/lasso_week4_demo
```

The commands have these meanings:

- `cmake -S . -B build` reads `CMakeLists.txt` and prepares a build directory.
- `cmake --build build` compiles both libraries, the tests, and the examples.
- `ctest --test-dir build --output-on-failure` runs the automated tests.
- `./build/lasso_week4_demo` runs the Week 4 demonstration program.

To install the libraries and headers so that another CMake project can use them:

```bash
cmake --install build --prefix install
```

### Expected result

`ctest` should report that all 4 tests passed. The demo should report approximately the values in section 4.11.

## 7. What the tests check

There are four test programs. Run the commands from the project folder, because some tests read `data/input/sample.csv`.

### `tests/test_week2.cpp`

- Good data passes the validation check.
- Standardizing the sample features gives the means 3 and 73.
- Coordinate descent returns two coefficients, a finite cost, and uses at most 500 passes.
- `soft_threshold(5, 2)` returns 3.
- The LASSO cost for a small example equals 0.5.
- Rows of different widths are rejected.
- A negative `lambda` is rejected.

### `tests/test_week3.cpp`

- The sample CSV loads with 8 rows and 3 features, all finite.
- The split gives 6 training rows and 2 test rows, and the same seed gives the same split.
- The scaler keeps the number of rows.
- `predict_rows` returns 8 without an intercept and 12 with an intercept of 4.
- Feature selection ignores a tiny coefficient.
- MAE equals 2/3 and RMSE equals the square root of 2/3 for the small example.
- A bad threshold, a bad train fraction, and a NaN value are all detected.

### `tests/test_week4.cpp`

- Cross-validation with 4 folds returns 4 fold scores.
- The mean validation RMSE is finite.
- Running it twice with the same seed gives the same result.
- Selecting the best `lambda` from three candidates works.
- Only 1 fold is rejected.
- A negative `lambda` is rejected.

### `tests/test_linear_regression.cpp`

- Predicting before fitting throws an error.
- The closed-form method recovers `y = 1 + 2x`.
- Gradient descent and stochastic gradient descent get close to a slope of 2.
- The correlation of perfectly linear data is 1.
- The train/test split has the right sizes, repeats with the same seed, and always keeps a training row.
- A train/test fraction of 1.0 is rejected.
- A constant `x` is rejected.

Tests are important because successful compilation alone does not prove that numerical calculations are correct.

## 8. Project folders

- `include/`: public header files that users include (`lasso/` and `linreg/`).
- `src/`: implementation files containing the calculations, one file per member.
- `tests/`: automated tests for expected and invalid behavior.
- `examples/`: small programs showing how to use the library.
- `data/input/`: sample input data.
- `docs/`: class-layout diagrams.
- `reports/`: weekly progress reports and the final report.
- `CMakeLists.txt`: build instructions for CMake.

## 9. Development plan

### Week 1: Foundation

The group set up the project structure, defined the data format, wrote the vector and matrix operations, the linear-regression baseline, the LASSO cost, soft-thresholding, simple error handling, and the first tests.

### Week 2: The main LASSO algorithm

The group added input validation, feature scaling, coordinate descent with soft-thresholding, and a reusable baseline.

### Week 3: Prepare and evaluate

The group added the train/test split, the fitted scaler, row predictions, feature selection, the regression metrics, and a simple `lambda` helper.

### Week 4: Choose lambda and finish

The group added k-fold cross-validation, `lambda` selection by validation RMSE, the final demo that keeps the test rows separate, and the CMake and CTest packaging.

### Final submission week

The group will test the project from a clean environment, review the reports together, confirm all member contributions and GitHub commits, and package the final source code, headers, tests, examples, data, reports, and build files.

## 10. The 10 member assignments

| Member | Topic | Main file(s) |
|--------|-------|--------------|
| 01 | Dataset loading and the train/test split | `member01_data.cpp`, `member01_training.csv`, `member01_week3_training.csv` |
| 02 | Data preprocessing and validation | `member02_preprocessing.cpp` |
| 03 | Feature scaling | scaling module (`fit_scaler`, `transform`) |
| 04 | Matrix and vector operations, and row predictions | `member04_matrix.cpp` |
| 05 | Linear-regression baseline | `linear_regression.hpp`, `linear_regression.cpp`, `member05_baseline.cpp` |
| 06 | LASSO cost and lambda comparison | `member06_cost.cpp` |
| 07 | Soft-thresholding and feature selection | `member07_soft_thresholding.cpp` (`selected_features`); `soft_threshold` itself is in `lasso_regression.cpp` |
| 08 | Coordinate descent and tuning | `member08_coordinate.cpp`, `member08_tuning.cpp` |
| 09 | Model evaluation | `member09_evaluation.cpp` |
| 10 | Cross-validation and integration | `member10_cross_validation.cpp` 

The shared core (`dot`, `matrix_vector_product`, `soft_threshold`, `lasso_cost`, and `load_csv`) is in `lasso_regression.cpp`.

## 11. Scope decisions

SMOTE is not included because it is primarily an imbalanced-classification technique and is not automatically appropriate for a continuous LASSO-regression problem.

The code is intentionally simple. It uses loops and straightforward functions rather than advanced templates, external packages, or complicated numerical libraries, so that the group can build and explain every part.

The design uses encapsulation (the private values inside `LinearRegression`) and composition (a `TrainTestSplit` contains two `Dataset` values). It does not use inheritance, protected members, or virtual functions, because the numerical workflow does not need them and adding them only for show would not be honest.

## 12. Week 4 limitations

- The data is small and made up, so the scores only demonstrate the workflow.
- The cross-validation and test scores can change if the data or the seed changes.
- The CSV reader supports plain numbers separated by commas. It does not support quoted text, and a row cannot end with a comma.
- The one-feature baseline and the multi-feature LASSO are separate parts of the library.
- Gradient descent depends on the scale of the features and on the learning rate.
- This is a learning project. It is not meant for production or safety-critical use.

## 13. AI use

The tools used by each member are recorded in `ai-use-declaration-member-10.md`. 