# Week 2 Progress Report — Member 05

Report owner:ZZIWA AKRAM IBRAHIM
Record note: Reconstructed on 2026-10-28 from the supplied linear-regression Week 2 archive. This report describes its files and does not claim a historical completion date or unprovided commit activity.

## Completed

- Added a reusable `linreg::LinearRegression` class for one-feature prediction.
- Implemented closed-form least squares, batch gradient descent, and stochastic gradient descent.
- Added prediction, MSE, R-squared, correlation, and standard-error helpers.
- Added reproducible train/test splitting and tests for normal and invalid inputs.
- Integrated the library as a separate CMake target so it can serve as a simple baseline beside the multi-feature LASSO library.

## In Progress

- Comparing the simple baseline with multi-feature LASSO on the same target values.
- Checking how feature scale and learning-rate choices affect the gradient-descent methods.

## Challenges/Blockers

- Gradient descent is sensitive to input scale and learning rate.
- The baseline accepts one feature at a time; it is not a replacement for the multi-feature LASSO implementation.
- The supplied archive did not contain names, student numbers, branch links, or commit records.

## Next Week

- Add train/test evaluation around the LASSO workflow.
- Fit scaling parameters on training rows and reuse them for test rows.
- Add feature selection and additional regression metrics.

## AI Use

- Tool: OpenAI Codex.
- Purpose: Review the supplied Week 2 source, improve input checks and readability, integrate its target into CMake, and draft this report.
- Reason: To help make the baseline buildable and understandable beside the LASSO modules; the group should review and be able to explain all changes.
