# Group-14-Submissions
# LASSO Regression From Scratch — Week 2

## 1. What this project is solving

We are building a small C++ library that predicts a numerical target from several input features. For example, the target could be an examination score and the features could be study hours, attendance, and completed assignments.

The final model will be LASSO regression. LASSO is ordinary linear regression plus an L1 penalty. The penalty discourages unnecessary coefficients and can make some coefficients zero. A zero coefficient means that the related feature is not being used by the model.

This Week 2 version connects the foundation from Week 1 to a simple training process. It validates data, scales features, performs basic matrix calculations, calculates the LASSO cost, shrinks values with soft-thresholding, and updates coefficients with coordinate descent. It is an educational implementation, not a claim of production-level optimization.

## 2. How the program works from start to finish

The data starts in `data/input/member01_training.csv`:

```csv
target,study_hours,attendance,assignments
52,1,60,2
55,2,65,3
61,3,70,4
66,4,80,5
70,5,90,6
```

The first column is the target. The other columns are features. Each row must stay together: the feature row for score 52 must remain connected to score 52.

The program then follows this flow:

```text
read or create the feature matrix and target vector
        ↓
check that rows and targets match
        ↓
calculate feature means and standard deviations
        ↓
standardize each feature
        ↓
start every coefficient at zero
        ↓
update one coefficient at a time
        ↓
apply soft-thresholding for the L1 penalty
        ↓
calculate the final LASSO cost
        ↓
report coefficients and evaluation values
```

### Data validation

`check_preprocessing_input` checks that the feature matrix is not empty, that it has the same number of rows as the target vector, and that every row has the same number of columns. If the input is wrong, the function throws `std::invalid_argument` instead of calculating with unreliable data.

### Feature scaling

`standardize` calculates a mean and standard deviation for each feature. It changes each value using:

```text
scaled value = (value - mean) / standard deviation
```

The function returns the scaled matrix together with the means and standard deviations. Keeping these values is important because the same training transformation must be used later when new test data is scaled.

### Coordinate descent

`coordinate_descent` creates a coefficient vector containing zeros. It works on one column at a time instead of changing every coefficient at once. For the selected column, it calculates the current relationship between that feature and the remaining error, then applies soft-thresholding. It repeats the passes until the changes are smaller than the tolerance or the maximum number of passes is reached.

The current Week 2 function returns the coefficient vector, the LASSO cost, and the number of passes. Week 3 will improve the formula review, feature selection, lambda comparison, prediction, and test-set evaluation.

## 3. What each Week 2 file does

| File | Purpose |
|---|---|
| `include/lasso/lasso_regression.hpp` | Week 1 public types and functions such as `Vector`, `Matrix`, `lasso_cost`, and `soft_threshold`. |
| `include/lasso/week2.hpp` | Week 2 declarations for scaling, coordinate descent, and mean absolute error. |
| `src/lasso_regression.cpp` | Week 1 implementation retained and used by the Week 2 modules. |
| `src/member02_preprocessing.cpp` | Checks the shape of the feature matrix and target vector. |
| `src/member03_scaling.cpp` | Calculates means and standard deviations and returns standardized features. |
| `src/member04_matrix.cpp` | Multiplies every matrix row by a vector using a simple loop. |
| `src/member08_coordinate_descent.cpp` | Updates one LASSO coefficient at a time and stops when changes become small. |
| `src/member09_evaluation.cpp` | Calculates mean absolute error between actual and predicted values. |
| `examples/member05_baseline.cpp` | Demonstrates ordinary regression before regularization. |
| `examples/member06_cost.cpp` | Demonstrates prediction error plus the L1 penalty. |
| `examples/member07_soft_threshold.cpp` | Shows how positive, negative, and small values are shrunk. |
| `examples/week2_demo.cpp` | Runs the Week 2 scaling and coordinate-descent demonstration. |
| `tests/test_week2.cpp` | Tests means, scaling, optimizer output, evaluation, and invalid input. |
| `CMakeLists.txt` | Builds all integrated library sources, tests, and the main demo. |

## 4. The ten real repository contributions

The group now has 10 members. Each person has a branch and a file contribution that can be seen in GitHub. Replace the placeholders with real names and student numbers.

| Member | Branch | What the member is responsible for | Files |
|---|---|---|---|
| Member 1 | `member-01-data` | Supplies and explains the numerical training data. | `data/input/member01_training.csv` |
| Member 2 | `member-02-preprocessing` | Checks that input rows and targets are valid. | `src/member02_preprocessing.cpp` |
| Member 3 | `member-03-scaling` | Makes features comparable by standardizing them. | `src/member03_scaling.cpp` |
| Member 4 | `member-04-matrix` | Performs row-by-vector multiplication. | `src/member04_matrix.cpp` |
| Member 5 | `member-05-baseline` | Shows the ordinary regression comparison. | `examples/member05_baseline.cpp` |
| Member 6 | `member-06-cost` | Explains and demonstrates the LASSO cost and L1 penalty. | `examples/member06_cost.cpp` and existing cost code |
| Member 7 | `member-07-soft-threshold` | Explains the shrinkage step used by LASSO. | `examples/member07_soft_threshold.cpp` and existing helper |
| Member 8 | `member-08-coordinate` | Implements the first coordinate-descent training loop. | `src/member08_coordinate_descent.cpp` |
| Member 9 | `member-09-evaluation` | Adds an error measure for comparing predictions. | `src/member09_evaluation.cpp` |
| Member 10 | `member-10-build-integration` | Connects all files in CMake and supplies the integrated demo and tests. | `CMakeLists.txt`, `examples/week2_demo.cpp`, `tests/test_week2.cpp` |

Each member should commit their files from their own branch, open a pull request, respond to review comments, and continue the same part in Week 3.

## 5. How to build and run

Requirements are a C++17 compiler and CMake 3.16 or newer. The project does not use an external machine-learning library.

### CMake

Run these commands from the project root:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/lasso_week2_demo
```

The first command prepares the build directory. The second compiles the library and programs. The third runs the tests. The final command runs the integrated demonstration.


Expected test output:

```text
All LASSO Week 2 tests passed.
```


```


## 6. Reports and references

The main report is `reports/week-02.md`. The ten expanded individual reports are in `reports/individual/member-01.md` through `member-10.md`. The report template is in `reports/individual/README.md`. References are in `reports/references.md`.

## 7. What is still needed in Week 3

Week 3 should add a clearer lambda comparison, feature-selection output, prediction for one row and a batch of rows, MSE/RMSE/R², held-out test evaluation, stronger edge-case tests, and final documentation. The coordinate-descent implementation should be reviewed and explained by the group before it is described as final.
