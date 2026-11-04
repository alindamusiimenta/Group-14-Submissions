# LASSO Regression — Week 3

A compact C++17 educational project for understanding LASSO regression from first principles. The project walks through the core workflow: loading data, validating inputs, splitting data into train/test sets, fitting a scaler on training data only, applying LASSO coordinate descent, evaluating predictions, and identifying the most important features.

This implementation is intentionally beginner-friendly and avoids external machine-learning libraries. The focus is on learning the logic behind regularized linear regression rather than using a high-level framework.

## Why this project exists
LASSO regression adds an L1 penalty to ordinary least squares so that some coefficients shrink to zero. In practice, this means the model can discard weak features and keep only the most useful predictors.

The project demonstrates this by:
- splitting the dataset into train and test sets,
- standardizing features using training statistics only,
- comparing candidate lambda values,
- fitting a LASSO model with coordinate descent,
- reporting predictive metrics and selected features.

## Project goals
- Build a clear educational implementation of LASSO regression in C++.
- Keep the code readable and modular for student learning.
- Show how train/test leakage is avoided by fitting scaling parameters only on training data.
- Evaluate the model using regression metrics that are easy to interpret.

## What the project includes
- deterministic train/test splitting,
- finite-value validation,
- feature scaling with saved train statistics,
- batch prediction for multiple rows,
- soft-thresholding and feature selection,
- candidate lambda comparison,
- regression metrics: MAE, MSE, RMSE, and R-squared,
- a demo program and unit tests.

## Project structure

```text
.
├── CMakeLists.txt
├── README.md
├── data/
├── docs/
├── examples/
├── include/
│   └── lasso/
│       ├── lasso_regression.hpp
│       ├── week2.hpp
│       └── week3.hpp
├── reports/
├── src/
│   ├── lasso_regression.cpp
│   ├── member01_data.cpp
│   ├── member02_preprocessing.cpp
│   ├── member03_scaling.cpp
│   ├── member04_matrix.cpp
│   ├── member06_cost.cpp
│   ├── member07_soft_threshold.cpp
│   ├── member08_coordinate.cpp
│   └── member09_evaluation.cpp
├── tests/
│   ├── test_week2.cpp
│   └── test_week3.cpp
└── build/
```

## Main files and purpose

| File | Purpose |
| --- | --- |
| `include/lasso/week3.hpp` | Public Week 3 API for splitting, scaling, prediction, feature selection, and evaluation. |
| `src/member01_data.cpp` | Reproducible dataset splitting. |
| `src/member02_preprocessing.cpp` | Input validation for finite values. |
| `src/member03_scaling.cpp` | Training-only scaler and transformed feature outputs. |
| `src/member04_matrix.cpp` | Batch prediction for many feature rows. |
| `src/member06_cost.cpp` | Candidate lambda comparison. |
| `src/member07_soft_threshold.cpp` | Selection of non-zero coefficients. |
| `src/member08_coordinate.cpp` | Coordinate descent optimization. |
| `src/member09_evaluation.cpp` | MAE, MSE, RMSE, and R-squared metrics. |
| `examples/week3_demo.cpp` | Demonstration of the full workflow. |
| `tests/test_week3.cpp` | Regression and validation tests. |
| `CMakeLists.txt` | Builds the library, demo, and test executables. |

## Build and run

### Prerequisites
- C++17 compiler
- CMake 3.16 or newer

### Configure and build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

If you are using MinGW on Windows, use:

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

If you are using another toolchain, replace the generator with the one that matches your environment (for example Visual Studio or Ninja).

### Run tests

```bash
ctest --test-dir build --output-on-failure
```

### Run the demo

Linux/macOS:

```bash
./build/lasso_week3_demo
```

Windows:

```powershell
build\lasso_week3_demo.exe
```

## What the metrics mean

- MAE: average absolute prediction error; same units as the target variable.
- MSE: average squared error; penalizes large errors more strongly.
- RMSE: square root of MSE; easier to interpret in the original target scale.
- R-squared: measures how much better the model is than guessing the mean target value.

## Important interpretation note
This project is designed for learning and demonstration. The dataset is synthetic and intended to explain the workflow, not to represent real-world production data. The optimization is also an educational implementation rather than a production-grade ML pipeline.

## Workflow summary

```text
Load or create dataset
        ↓
Validate rows and values
        ↓
Shuffle and split into training/testing sets
        ↓
Fit scaler on training data only
        ↓
Transform both sets using saved statistics
        ↓
Try candidate lambda values
        ↓
Fit LASSO model with coordinate descent
        ↓
Predict on test rows
        ↓
Select non-zero coefficients
        ↓
Evaluate MAE, MSE, RMSE, and R-squared
```

## Notes
- The train/test rule is important: the test set must not influence preprocessing or model fitting.
- Scaling parameters are estimated from the training data only and then reused for test data.
- The project builds on the same library from earlier coursework and extends it with Week 3 functionality.

## License
This project is distributed under the repository license included in the project root.
