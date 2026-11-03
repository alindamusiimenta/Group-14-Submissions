# Week 3 Progress Report — LASSO Regression From Scratch

## Purpose of this week

Week 3 extends each member's Week 2 contribution instead of replacing it. The project now demonstrates the complete experimental flow: split data, fit preprocessing on training data, train the LASSO coefficients, make test predictions, identify selected features, compare lambda candidates, and calculate evaluation metrics.

The group still has 10 members. Each member owns a real branch and files in the repository. Each member should push their work, open a pull request, update their individual report, and help review the integrated build.

## How the new workflow works

The program stores features and targets in a `Dataset`. Member 1 shuffles the row indexes using a fixed seed and sends most rows to training and the remaining rows to testing. The fixed seed makes the split reproducible.

Member 2 checks that every feature and target is finite. Invalid values such as NaN or infinity should be rejected before training.

Member 3 fits a scaler using training features only. The scaler stores training means and standard deviations and then transforms both the training and test rows. This avoids test-data leakage.

Member 6 compares candidate lambda values. The candidate with the lowest current training cost is selected as a simple Week 3 demonstration. A stronger final experiment should use a validation set rather than selecting directly on the test set.

Member 8's coordinate-descent code trains coefficients. Member 7 then checks which coefficient indexes are larger than a small threshold. These are treated as selected features.

Member 4 multiplies each row by the learned coefficients to create predictions. Member 9 compares those predictions with the actual test targets using MAE, MSE, RMSE, and R-squared.

Member 10 integrates the source files in CMake and supplies the complete demo and tests.

## Ten-member continuation assignments

Replace the placeholders with real names and student numbers.

### Member 1 — Data split and expanded dataset

**Branch:** `member-01-data`

**Files:** `src/member01_data.cpp`, `data/input/member01_week3_training.csv`

The new split function creates an index for every row, shuffles the indexes with a seed, and copies rows into train and test datasets. It keeps each row's target attached to its features. The seed makes the same split happen again when the program is rerun. The expanded CSV provides enough rows for a meaningful small train/test example.

### Member 2 — Finite-value validation

**Branch:** `member-02-preprocessing`

**File:** ``

This extension checks every feature and target with `std::isfinite`. NaN and infinity can break means, standard deviations, and coefficient updates, so they must be rejected early. The function returns a simple boolean that can be checked before training.

### Member 3 — Training-only scaling

**Branch:** `member-03-scaling`

**File:** ``

This scaler is different from simply scaling one matrix. It learns means and deviations from the training matrix, saves them, and uses the same values to transform the test matrix. This is the correct direction for evaluation because test values should not change the preprocessing rules learned by the model.

### Member 4 — Multiple-row prediction

**Branch:** `member-04-matrix`

**File:** ``

The prediction helper accepts a matrix of rows and a coefficient vector. For each row it multiplies each feature by its coefficient and adds the results. It returns one prediction per row and checks that the row width matches the coefficient count.

### Member 5 — Week 3 baseline comparison

**Branch:** `member-05-baseline`

**File:** `examples/member05_baseline.cpp`

The example prints the ordinary regression intercept, slope, and MSE. This keeps the baseline visible while the group evaluates LASSO. In the final report, the baseline should be compared with LASSO using the same test data where possible.

### Member 6 — Lambda comparison

**Branch:** `member-06-cost`

**File:** `src/member06_cost.cpp`

The lambda helper receives a list of candidate penalty values. It trains a small fit for each candidate and keeps the candidate with the lowest returned cost. This demonstrates hyperparameter comparison. The group should explain that a final model should choose lambda with a validation set rather than using the test set to make the choice.

### Member 7 — Feature selection

**Branch:** `member-07-soft-threshold`

**Files:** `src/member07_soft_threshold.cpp`, `examples/member07_selection.cpp`

Soft-thresholding from Week 2 pushes small coefficients toward zero. This week the selection helper checks the final coefficients and returns the indexes whose absolute values are above a small threshold. These indexes represent features kept by the model. The threshold should be documented rather than chosen secretly.

### Member 8 — Coordinate-descent review and tuning

**Branch:** `member-08-coordinate`

**File:** `examples/member08_tuning.cpp`, existing coordinate-descent source

The optimizer remains the part that learns coefficients. The Week 3 example sends several lambda values through the training process. The member should review the stopping tolerance, maximum passes, and update formula on small data where the expected direction is understandable.

### Member 9 — Full evaluation metrics

**Branch:** `member-09-evaluation`

**File:** ``

The metrics function calculates four results. MAE averages absolute errors, MSE averages squared errors, RMSE takes the square root of MSE, and R-squared compares the model's error with the variation around the actual mean. These values help the group describe model quality rather than only printing coefficients.

### Member 10 — Final Week 3 integration

**Branch:** `member-10-build-integration`

**Files:** `CMakeLists.txt`, `tests/test_week3.cpp`, `examples/week3_demo.cpp`

The CMake file adds every new source file to the library. The test program checks splitting, train-only scaling, prediction, feature selection, lambda comparison, and metrics. The main demo runs the complete flow and prints the test size, chosen lambda, test errors, and selected-feature count.

## Completed this week

- Added a reproducible train/test split.
- Added finite-value validation.
- Added a scaler that can be fitted on training data and reused on test data.
- Added multiple-row prediction.
- Added a Week 3 baseline example.
- Added simple lambda comparison.
- Added selected-feature reporting.
- Added MAE, MSE, RMSE, and R-squared.
- Added integrated Week 3 tests and demonstration.
- Continued the 10-member branch and report structure.

## Limitations and honest interpretation

The current lambda comparison uses the training cost, so it is a teaching demonstration rather than a complete validation procedure. The coordinate-descent implementation is still simple and should be checked carefully. The multiple-feature optimizer now estimates an intercept separately from the penalized feature coefficients. Lambda selection remains training-cost based, so it is still a teaching demonstration rather than a complete validation procedure.

## Final submission preparation

Before the final week, the group should replace placeholders, add actual branch and pull-request links, check that all members have meaningful commits, run a clean build, verify the tests, select a final dataset, and agree on the final explanation of limitations.

## References

The group used the course notes, the Week 2 references, Robert Tibshirani's 1996 paper on LASSO, and C++ reference material for standard-library functions. The exact sources consulted by each member should be listed in the individual reports.

## AI use

- **Tool:** Manus AI assistant.
- **Purpose:** Help organize the Week 3 extension, create a branch-ready assignment structure, and review beginner-level documentation.
- **Reason:** To support planning and review while the group tests and understands the code.

The group must update this section if other AI tools were used and should only claim work that members have checked and understood.

## File organization decision

For this continuation, each member's Week 2 and Week 3 implementation is kept together in one member-owned source file. For example, Member 2's original shape checks and new finite-value checks are both in `src/member02_preprocessing.cpp`; Member 3's original standardization and training-only scaler are both in `src/member03_scaling.cpp`. This makes the continuation easier to follow without combining all ten members' work into one file.

## Object-oriented programming concepts

The Week 3 assignment also asks us to document inheritance, polymorphism, and encapsulation as they appear in our program. The current project uses one beginner-friendly class, `LassoModel`, and several simple `struct` data containers. It is important to describe what is actually implemented rather than claiming that a feature exists when it does not.

### Encapsulation implemented in `LassoModel`

Encapsulation means keeping an object's data and the functions that operate on that data together, while controlling which parts can be accessed from outside the class.

The class is declared in `include/lasso/lasso_regression.hpp`:

```cpp
class LassoModel {
public:
    void fit_baseline(const Vector& x, const Vector& y);
    double predict(double x) const;
    double intercept() const;
    double slope() const;

private:
    double intercept_ = 0.0;
    double slope_ = 0.0;
    bool fitted_ = false;
};
```

The class has three private data members:

- `intercept_` stores the intercept of the fitted line.
- `slope_` stores the slope of the fitted line.
- `fitted_` records whether the model has been trained.

Because these members are private, code outside the class cannot directly change them. For example, this is not allowed:

```cpp
model.slope_ = 10.0; // not allowed because slope_ is private
```

Instead, the object is used through its public member functions:

- `fit_baseline()` calculates and stores the model values.
- `predict()` uses the stored values to make a prediction.
- `intercept()` returns the stored intercept.
- `slope()` returns the stored slope.

This protects the internal state of the model. It also means that the class can later change its internal calculation without changing how users call it.

The `const` after `predict`, `intercept`, and `slope` means those functions promise not to change the object. A prediction should read the model values, not modify them.

### Simple class layout for the hand drawing

Draw the following box on paper:

```text
+-------------------------------------------+
|              LassoModel                   |
+-------------------------------------------+
| - intercept_: double                      |
| - slope_: double                           |
| - fitted_: bool                            |
+-------------------------------------------+
| + fit_baseline(x: Vector, y: Vector): void|
| + predict(x: double): double               |
| + intercept(): double                      |
| + slope(): double                          |
+-------------------------------------------+
```

Use the following notation:

- `+` means public.
- `-` means private.
- `#` means protected.

There are no protected members in the current `LassoModel` class, so no `#` member needs to be drawn inside this class.

### Encapsulation in the data structures

The project also uses simple `struct` types. For example:

```cpp
struct Dataset {
    Matrix features;
    Vector target;
};
```

and:

```cpp
struct LassoFit {
    Vector coefficients;
    double cost;
    int passes;
};
```

A `struct` is similar to a class, but its members are public by default. These structures are used as simple containers for related results. They do not hide their data in the same way that `LassoModel` does.

The Week 3 structures include:

```cpp
struct TrainTestSplit {
    Dataset train;
    Dataset test;
};

struct FittedScaler {
    Vector means;
    Vector standard_deviations;
    Matrix transform(const Matrix& features) const;
};

struct RegressionMetrics {
    double mae;
    double mse;
    double rmse;
    double r_squared;
};
```

For the hand drawing, these can be shown as separate boxes:

```text
+---------------------------+
| Dataset                   |
+---------------------------+
| + features: Matrix       |
| + target: Vector         |
+---------------------------+

+---------------------------+
| LassoFit                 |
+---------------------------+
| + coefficients: Vector   |
| + cost: double           |
| + passes: int            |
+---------------------------+

+---------------------------+
| TrainTestSplit           |
+---------------------------+
| + train: Dataset         |
| + test: Dataset          |
+---------------------------+

+----------------------------------+
| FittedScaler                     |
+----------------------------------+
| + means: Vector                  |
| + standard_deviations: Vector    |
+----------------------------------+
| + transform(features): Matrix    |
+----------------------------------+

+----------------------------------+
| RegressionMetrics                |
+----------------------------------+
| + mae: double                   |
| + mse: double                   |
| + rmse: double                 |
| + r_squared: double            |
+----------------------------------+
```

### Inheritance in the current project

Inheritance is a relationship where a child class receives data or functions from a parent class. It is usually written with a colon in C++:

```cpp
class Child : public Parent {
};
```

There is currently **no inheritance relationship** in this project. `LassoModel` does not inherit from another class, and none of the Week 3 structures inherit from one another.

Therefore, the hand drawing should not show an inheritance arrow. The class diagram should show the classes and structures as separate boxes.

This is a valid result to report. The project focuses on implementing LASSO calculations from scratch, so inheritance was not necessary for the current design. Adding inheritance only to appear in the diagram would make the design more complicated without improving the numerical model.

### Polymorphism in the current project

Polymorphism means that different classes can be used through a common interface while providing different implementations. In C++, this is commonly implemented with a base class and virtual functions:

```cpp
class Model {
public:
    virtual double predict(double x) const = 0;
    virtual ~Model() = default;
};
```

A child class could then override `predict()` with its own implementation.

There is currently **no runtime or compile-time polymorphism intentionally implemented** in the project. The program calls specific functions such as:

```cpp
coordinate_descent(...);
standardize(...);
evaluate_regression(...);
```

The `LassoModel` class has a `predict()` function, but it is not a virtual override and there is no parent model class. Therefore, it should be described as a normal public member function, not as polymorphism.

### Summary for the report

The object-oriented concepts in the current program can be summarized as follows:

| Concept | Status in this project | Evidence |
|---|---|---|
| Encapsulation | Implemented | `LassoModel` keeps `intercept_`, `slope_`, and `fitted_` private and exposes public functions. |
| Public access | Implemented | Public functions such as `fit_baseline()` and `predict()`. |
| Private access | Implemented | Private data members inside `LassoModel`. |
| Protected access | Not used | No protected members are required in the current design. |
| Inheritance | Not implemented | There is no parent-child class relationship. |
| Polymorphism | Not implemented | There are no virtual functions or overridden methods. |

### What to say when presenting the drawing

> Our project uses encapsulation in the `LassoModel` class. The model's intercept, slope, and fitted status are private, so outside code cannot change them directly. Public functions are provided for fitting the model, making predictions, and reading the results. The project currently does not use inheritance or polymorphism because it has no parent and child model classes and no virtual functions. The remaining structures are simple public data containers used to pass regression results between functions.

The handwritten diagram should show `LassoModel`, `Dataset`, `LassoFit`, `TrainTestSplit`, `FittedScaler`, and `RegressionMetrics`, including their data members, member functions, and access symbols. It should also include a short note: `No inheritance or polymorphism implemented in the current version.`
