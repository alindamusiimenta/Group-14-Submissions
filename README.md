# Group-14-Submissions
# LASSO Regression From Scratch in C++ — Final Project

**Group:** Group 14
**Project:** LASSO Regression in C++, built from scratch
**Course context:** C++ programming and software development, Makerere University

## 1. What this project is about

This project is a small, reusable C++17 library for learning how **LASSO regression** works from the beginning. We did not use a ready-made machine-learning library. Instead, we built every important part ourselves using the C++ ideas taught in the course: vectors, classes, functions, loops, file input, error handling, and finally templates.

The library predicts a numerical value from several input features. For example, it can predict an exam score from study hours, attendance, and completed assignments.

LASSO stands for **Least Absolute Shrinkage and Selection Operator**. It is linear regression with an extra penalty:

```text
y_hat      = b0 + b1*x1 + b2*x2 + ... + bk*xk
LASSO cost = squared_error / (2*n) + lambda * sum(abs(coefficients))
```

The penalty pushes unnecessary coefficients to exactly zero. When a coefficient is zero, that feature is not used by the model, so LASSO performs **feature selection** as well as prediction. The value `lambda` controls how strong the penalty is: zero gives ordinary regression, and larger values remove more features.

## 2. Goals and objectives

### Main goal

Build a complete, tested, beginner-readable LASSO regression workflow in C++ that a student can read, run, and explain, and then make it flexible by using C++ templates where they are appropriate.

### Objectives

1. Load numerical data from a CSV file and check that it is valid.
2. Split the data into training rows and held-out test rows.
3. Scale features using values learned from the training rows only.
4. Build a linear-regression baseline to compare against.
5. Calculate the LASSO cost, including the L1 penalty.
6. Implement soft-thresholding to shrink coefficients.
7. Learn the coefficients with coordinate descent.
8. Identify which features LASSO kept.
9. Choose `lambda` fairly using k-fold cross-validation.
10. Measure prediction quality with MAE, MSE, RMSE, and R-squared.
11. Use templates so the code can work with `short`, `int`, `float`, and `double`.
12. Package the project with CMake and CTest so that it builds and tests the same way on every machine.

## 3. The problem we solved

If `lambda` is too small, the model keeps too many features and may memorize the training data. If `lambda` is too large, it throws away useful features. We also cannot judge a model by the data it was trained on, because it will always look good there.

The biggest risk is **data leakage**: if the scaler or the `lambda` search ever sees the test rows, the final score looks better than it really is. The final workflow is designed so that the test rows are never used for scaling or for choosing `lambda`.

## 4. How the program works from start to finish

```text
Load the CSV data
        ↓
Validate rows, widths, and finite values
        ↓
Split into training rows and test rows (fixed seed)
        ↓
Choose lambda by k-fold cross-validation (training rows only)
        ↓
Fit the scaler on the training rows only
        ↓
Fit LASSO with coordinate descent + soft-thresholding
        ↓
Predict the test rows once
        ↓
Select non-zero coefficients
        ↓
Evaluate MAE, MSE, RMSE, and R-squared
```

The sample data uses the first column as the target and the other columns as features:

```csv
target,study_hours,attendance,assignments
52,1,60,2
55,2,65,3
61,3,70,4
66,4,80,5
70,5,90,6
```

## 5. How everything was achieved: week by week

### Week 1: Foundation

We set up the project structure and defined the data format. We wrote the `Vector`, `Matrix`, and `Dataset` types, the dot product, matrix-vector multiplication, a one-feature linear-regression baseline, the LASSO cost function, soft-thresholding, simple error handling, and the first tests.

For the baseline example, the fitted line was `y = 46.700 + 4.700*x`, giving a prediction of 74.900 for `x = 6`.

### Week 2: The main LASSO algorithm

We added input validation, feature standardization, and the first version of **coordinate descent**. Coordinate descent starts every coefficient at zero and updates one coefficient at a time. Each update uses soft-thresholding, and the passes repeat until the changes are smaller than a tolerance or the maximum number of passes is reached. The intercept is not penalized.

### Week 3: Prepare and evaluate

We added the deterministic train/test split, the fitted scaler that remembers training means and standard deviations, prediction for many rows, feature selection, a simple `lambda` comparison helper, and the regression metrics (MAE, MSE, RMSE, R-squared).

### Week 4: Choose lambda and finish the workflow

We added **k-fold cross-validation**. For each fold, the program sets that fold's rows aside for validation, fits a scaler on the remaining rows only, fits LASSO, predicts the validation rows, and records the RMSE. The average RMSE across folds is used to compare candidate `lambda` values, and every candidate is tested on identical folds. The final demo keeps the test rows completely separate.

Demo result with the bundled synthetic data and seed 42 (9 training rows, 3 test rows):

| What | Value |
|------|-------|
| Selected lambda | 0.0010 |
| Mean 4-fold validation RMSE | 0.0871 |
| Test MAE | 0.0510 |
| Test RMSE | 0.0716 |
| Test R-squared | 0.9977 |

### Week 5: Templates and final project

Following the lecturer's instructions, we used C++ templates where they were appropriate. A template lets us write code once and use it with different data types.

- A reusable **Matrix template** for storing and working with numerical values.
- Templates for **reading CSV files** and organizing input features and target values.
- **Typed interfaces** for the Linear Regression and LASSO Regression models, so they accept different number types while using `double` for the main calculations.
- A Week 5 example and tests to check that the templates work.
- Notes on our template design, questions for the group, and a class diagram.
- Updated CMake build files and project reports.

When values are converted to integer types, the program rejects decimal values and values outside the supported range instead of silently changing them.

## 6. Main parts of the library

| Part | What it does |
|------|--------------|
| `load_csv` | Reads numeric CSV data into a `Dataset` (target first, then features). |
| Validation | Rejects empty data, mismatched sizes, ragged rows, and NaN or infinite values. |
| `split_dataset` | Shuffles with a fixed seed and splits into training and test sets. |
| `fit_scaler` / `transform` | Learns means and standard deviations from training rows and applies them to any rows. |
| `dot`, `matrix_vector_product` | Core vector and matrix operations. |
| `predict_rows` | Predicts every row of a feature matrix. |
| `lasso_cost` | Squared error plus the L1 penalty. |
| `soft_threshold` | Shrinks a value toward zero, and can make it exactly zero. |
| `coordinate_descent` | Learns the LASSO coefficients and intercept. |
| `selected_features` | Returns the positions of the coefficients that were kept. |
| `cross_validate_lambda` | Tests one `lambda` with k-fold cross-validation. |
| `select_lambda_by_cross_validation` | Tries every candidate and keeps the lowest mean validation RMSE. |
| `evaluate_regression` | Returns MAE, MSE, RMSE, and R-squared. |
| `LinearRegression` | One-feature baseline (closed form, gradient descent, stochastic gradient descent). |
| Week 5 templates | Typed Matrix, CSV reading, and typed model interfaces. |

## 7. How errors are handled

The program throws `std::invalid_argument` or a similar exception instead of continuing with an incorrect calculation. Examples include:

- Vectors with different sizes, or empty data.
- A matrix with rows of different widths.
- Feature or target values that are NaN or infinity.
- A negative or non-finite `lambda`, or an empty list of candidates.
- Fewer than two folds, or more folds than rows.
- A train fraction that is not between 0 and 1.
- A CSV file that cannot be opened, or a CSV cell that is not numeric.
- Calling `predict` before fitting the baseline model.
- Decimal values or out-of-range values when converting to an integer type.

## 8. How to run the project

Requirements:

- A C++17 compiler such as GCC, Clang, or MSVC.
- CMake (the required version is set in `CMakeLists.txt`).
- No external machine-learning library is required.

From inside the project directory:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/lasso_week4_demo
```

On Windows with MinGW you may need `cmake -S . -B build -G "MinGW Makefiles"`. Run the commands from the project folder, because some tests read `data/input/sample.csv`.

To install the libraries and headers so another CMake project can use them:

```bash
cmake --install build --prefix install
```

## 9. What the tests check

All five test programs pass:

1. **Week 2 LASSO:** validation, standardization, coordinate descent output, soft-thresholding, and the LASSO cost.
2. **Week 3 LASSO:** CSV loading, train/test splitting, scaling, row prediction, feature selection, and metrics.
3. **Week 4 validation:** cross-validation fold counts, finite and repeatable RMSE, `lambda` selection, and bad folds or `lambda` being rejected.
4. **Linear Regression:** predicting before fitting fails, closed-form and gradient-descent fits, correlation, and the train/test split.
5. **Numeric templates:** the typed Matrix, CSV reading, and typed model interfaces.

The Week 5 example reads 8 rows with 3 input features from the CSV file. It also multiplies an integer matrix by float values. Both the typed Linear Regression and typed LASSO models predict 11 for an input value of 5.

We also tested installation: after installing the project, we built a separate CMake example that used the installed header files, and it ran successfully.

Tests matter because successful compilation alone does not prove that numerical calculations are correct.

## 10. Project folders

- `include/`: public header files (`lasso/` and `linreg/`).
- `src/`: implementation files, one per member.
- `tests/`: automated tests for expected and invalid behavior.
- `examples/`: small programs showing how to use the library.
- `data/input/`: sample input data.
- `docs/`: class diagrams and template design notes.
- `reports/`: weekly progress reports and the final report.
- `CMakeLists.txt`: build instructions for CMake.

## 11. Team contributions

| Member | Topic |
|--------|-------|
| 01 | Dataset loading and the train/test split |
| 02 | Data preprocessing and validation |
| 03 | Feature scaling |
| 04 | Matrix and vector operations, and row predictions |
| 05 | Linear-regression baseline |
| 06 | LASSO cost and lambda comparison |
| 07 | Soft-thresholding and feature selection |
| 08 | Coordinate descent and tuning |
| 09 | Model evaluation |
| 10 | Cross-validation, build integration, and tests |

Each member has an individual report in `reports/individual/` describing the work they actually performed.

## 12. Scope decisions

- **SMOTE is not included.** It is mainly an imbalanced-classification technique and is not automatically appropriate for continuous LASSO regression.
- **Logistic Regression, GNNs, and CNNs** were considered as examples of template use but are outside the scope of this LASSO project.
- **No inheritance or virtual functions.** The design uses encapsulation (private values inside `LinearRegression`) and composition (a `TrainTestSplit` contains two `Dataset` values), because the numerical workflow does not need inheritance and adding it only for show would not be honest.
- The code is intentionally simple: loops and straightforward functions rather than advanced numerical libraries, so every part can be explained.

## 13. Limitations

- The sample dataset is small and artificial, so the scores only demonstrate that the workflow runs. They do not show how accurate the model would be on real data.
- Cross-validation and test scores can change if the data or the seed changes.
- Model calculations use `double`, which cannot represent every numerical value exactly.
- The CSV reader supports plain numbers separated by commas. It does not support quoted text, and a row cannot end with a comma.
- The one-feature baseline and the multi-feature LASSO are separate parts of the library.
- Gradient descent depends on feature scale and learning rate.
- The lecturer mentioned Chapter 18 exercises, but we did not have the textbook or the exercise questions. These still need to be checked and included.
- This is a learning project, not meant for production or safety-critical use.

## 14. Work remaining before submission

- Every member completes their individual report and describes the work they actually performed.
- Check the Chapter 18 exercises in the assigned textbook and include the relevant exercise numbers or questions.
- Test the project from a clean environment and confirm all member contributions and GitHub commits.
- Make sure every member understands the code, the concepts, and the test results well enough to explain their contribution in the presentation.

## 15. Use of AI tools

We used AI tools, including OpenAI Codex, to support parts of the project. They helped us review and improve code, work on C++ templates and tests, prepare diagrams, and organize our reports. The tools used by each member are recorded in the AI-use declarations.

We reviewed the generated work and used it to support our understanding of the project. As a group, we remain responsible for the final code, reports, and explanations in our submission.
