# Final Technical Report — LASSO Regression Library

**Report owner:** Member 10 (integration)  
**Package reviewed:** Group 14 LASSO Regression in C++  
**Record note:** Prepared from the supplied Week 1–4 ZIP archives and verified against the integrated code on 2026-10-28. The supplied project-instructions PDF gives the library goals and weekly-report format, but no separate week-by-week objectives/commit-plan PDF was available. This report does not claim a historical submission date, member commit, or pull request that was not provided.

## Abstract

The project is a reusable C++17 educational library for simple linear regression and multi-feature LASSO regression. It reads numeric CSV data, validates feature matrices, standardizes features, fits LASSO coefficients with coordinate descent, chooses a regularization parameter with k-fold cross-validation, predicts held-out rows, and calculates regression metrics. A separate one-feature linear-regression library provides a baseline. The final CMake build completed and all four registered CTest programs passed in the local Windows/GCC environment.

## Objectives and scope

The project demonstrates a reusable library interface, separation of headers and implementation, matrix/vector operations, input validation, examples, automated tests, and CMake/CTest. It uses synthetic values for learning and verification. It does not claim to use real Tesla or other proprietary data.

## Design

The project has two library targets:

- `linear_regression` contains `linreg::LinearRegression`, a one-feature model with closed-form least squares, batch gradient descent, and stochastic gradient descent.
- `lasso_regression` contains the multi-feature LASSO functions, preprocessing tools, evaluation metrics, and cross-validation API.

The public headers are under `include/`; implementations are under `src/`. `examples/` contains runnable programs, and `tests/` contains small CTest executables. `data/input/sample.csv` provides an eight-row synthetic input example. CMake install and export rules package both libraries and their public headers for use from another CMake project.

## Main workflow

1. Read or create a `Dataset` and check row dimensions and finite values.
2. Split data reproducibly into training and held-out test rows.
3. Compare candidate lambda values with deterministic k-fold cross-validation on the training rows.
4. Fit a scaler from training rows only and reuse it for test rows.
5. Fit coefficients with coordinate descent and soft-thresholding. The intercept is updated separately and is not penalized.
6. Predict the held-out rows and calculate MAE, MSE, RMSE, R-squared, and selected feature indexes.

The Week 3 `choose_lambda()` helper remains available as a simple training-cost demonstration. The final Week 4 example uses the cross-validation selector instead.

## Object-oriented design

`linreg::LinearRegression` demonstrates encapsulation: the intercept, slope, and fitted flag are private. Public methods fit a model, predict values, and return fitted parameters. `TrainTestSplit` contains `Dataset` values, which is a containment relationship.

There is no inheritance relationship, no protected data, and no virtual dispatch in the current code. These features are reported as absent rather than added artificially. The class and structure layouts are in the JPG diagrams in `docs/figures/` and in editable form in `docs/diagrams/class-diagram.mmd`.

## Build and test

From a clean project directory, run:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
cmake --install build --prefix install
```

The final local CTest run passed 4/4 tests: Week 2 LASSO, Week 3 LASSO, Week 4 cross-validation, and the linear-regression baseline. The install command was checked, then a separate CMake consumer found and built against both installed libraries. The Week 4 demo ran and reported held-out metrics. See `build-and-test-results-member-10.txt` for the recorded commands.

## Demonstration result and limitations

With the fixed seed and bundled synthetic dataset, the Week 4 demo split 12 rows into 9 training rows and 3 test rows. It selected lambda `0.0010` with a mean four-fold validation RMSE of `0.0871`; held-out test MAE was `0.0510`, RMSE was `0.0716`, and R-squared was `0.9977`. The dataset is too small and artificial to support claims about real-world accuracy.

The CSV reader supports simple numeric comma-separated values and does not handle quoted text fields. The one-feature baseline and multi-feature LASSO are separate APIs. Gradient-descent behavior depends on feature scale and learning rate. This code is for education, not safety-critical or production use.

## Group contribution evidence

The supplied files associate module numbers 01–10 with data handling, validation, scaling, matrix operations, a baseline, cost selection, thresholding, coordinate descent, metrics, and integration. The ZIP files did not include verified personal names, student numbers, commit hashes, branches, or pull-request links. Add those from the group's actual records before signing a personal contribution statement.

## AI-use statement

OpenAI Codex assisted with archive review, code readability and validation changes, CMake integration, report drafting, diagram creation, compilation, and CTest verification for this assembled package. See `ai-use-declaration-member-10.md`. Group members should inspect and understand the submitted implementation and revise the reports in their own words as appropriate.
