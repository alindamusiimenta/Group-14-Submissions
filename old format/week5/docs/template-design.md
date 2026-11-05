# Week 5: Template Design Notes

## Goal

The original regression functions store values as `double`. Week 5 adds beginner-friendly template interfaces so callers can store or pass common numeric types such as `short`, `int`, `float`, and `double`. The existing algorithms still calculate in `double`, which keeps the change focused and avoids copying the regression algorithms for every type.

## Templates used in the project

| Template | Purpose | Why it is useful here |
| --- | --- | --- |
| `numerics::Matrix<T>` | Stores a rectangular matrix of numeric values and provides row/column counts, transpose, and matrix-vector multiplication. | Matrix operations are shared by data processing and regression, and the stored type is selected by the caller. |
| `numerics::NumericDataset<T>` | Holds a typed feature matrix and matching typed target vector. | Keeps features and target together after loading or conversion. |
| `numerics::CsvDataProcessor<T>` | Loads the project's numeric CSV format and converts values to `T` with range and fractional-value checks. | Lets a caller choose an appropriate storage type while using the existing CSV parser. |
| `linreg::TypedLinearRegression<InputT, TargetT>` | Adapts typed one-feature input and target vectors to the existing linear-regression model. | Supports mixed input and target types without duplicating the fitting code. |
| `lasso::TypedLassoRegression<FeatureT, TargetT>` | Adapts a typed feature matrix and target vector to the existing LASSO model. | Gives the multi-feature model a typed interface while keeping the core algorithm reusable. |

The numeric trait in `numerics/numeric_types.hpp` uses C++17 type traits. It accepts arithmetic types other than `bool`. It is used in `static_assert` checks so invalid types produce a clear compile-time message. C++17 does not have the C++20 `concept` syntax, so a trait is the appropriate equivalent for this project.

These templates use composition and value types; they do not introduce inheritance or protected members. The UML shows the public (`+`) and private (`−`) members that exist in the implementation, without adding unused access sections or inheritance relationships.

## Conversion and precision

Typed regression adapters convert their input to `double` before fitting, and predictions are returned as `double`. This design means the adapters accept different numeric types, but it does not preserve arbitrary precision or values outside the range of `double`. When a CSV value is converted to an integral type, a fractional value or an out-of-range value is rejected instead of silently truncated. Non-finite numbers are also rejected.

The bundled CSV file contains whole-number values, so it can be loaded as `short` in the Week 5 demo. A real dataset with fractional measurements should normally be loaded as `float` or `double`.

## Design questions for discussion

1. Should the matrix store its values in the caller's type and return `double` results from multiplication, or should it also support a caller-selected result type?
2. Is conversion to `double` a good balance between simpler teaching code and precision, or should a later version preserve `long double` values?
3. Should converting a fractional CSV value to an integer always fail, or should the caller choose a rounding rule?
4. Should `NumericDataset<T>` validate that target count equals matrix row count when it is constructed?
5. Should the typed model templates eventually replace the double-only public API, or remain small adapters around it?
6. Which additional types are useful in this assignment, and should `bool`, character types, or user-defined numeric types be excluded explicitly?
7. How can tests show that type conversion does not change model results beyond a documented tolerance?

## Candidate template areas from the lecturer's note

Matrices, CSV processing, linear regression, LASSO, and numerical-computing helpers are represented in the current implementation. Logistic regression, GNNs, and CNNs are possible future template candidates from the lecturer's list; they are outside this LASSO project's current objectives and are not claimed as implemented.

## Chapter 18 exercises

The screenshots mention Chapter 18 exercises, but the textbook title and exercise text were not supplied. This report therefore does not claim completion of particular textbook exercises. As practice based on the lecturer's template brief, members can (a) write a small `Matrix<T>` test for `short` and `float`, (b) try a type that should fail the numeric static assertion, and (c) test whether converting fractional CSV values to integer storage is rejected. Add actual exercise numbers and questions after checking the assigned textbook.

## UML

The editable diagram source is `docs/diagrams/week5-template-uml.mmd`; the rendered class layout is `docs/figures/week5-template-uml.jpg`.
