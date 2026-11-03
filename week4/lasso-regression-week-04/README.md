# LASSO Regression — Week 4 Extension

This archive continues the Week 3 C++17 educational project. Week 4 focuses on **k-fold cross-validation, λ selection by mean validation RMSE, reproducibility, and evaluation discipline**.

## Quick start
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/lasso_week4_demo
```
On Windows, run `build\lasso_week4_demo.exe`.

## New Week 4 files
- `include/lasso/week4.hpp` — cross-validation API.
- `src/member10_cross_validation.cpp` — implementation.
- `examples/week4_demo.cpp` — complete demonstration.
- `tests/test_week4.cpp` — focused regression tests.
- `reports/week-04.md` and `reports/week-04.pdf` — report.
- `docs/figures/week4_cross_validation_workflow.png` — coloured workflow diagram.

## What it does
For each candidate λ, the program performs deterministic k-fold validation. In each fold, feature scaling is fitted on the training portion only, preventing information leakage from validation rows. It selects the λ with the lowest mean validation RMSE.

## Important interpretation
The bundled data are synthetic educational examples, not proprietary or measured Tesla data. The demonstration's final fit metrics are training-fit diagnostics, not independent test performance. This is an academic regression project, not a vehicle or robot controller.

## Project lineage
The Week 2 and Week 3 source files, tests, diagrams, and reports are retained as project history. See `reports/week-04.md` for method, limitations, and next steps.
