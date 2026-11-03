# Change log

## Review and improvement pass

- Added `reports/technical-report.md` with verified project scope, mathematical objective, class inventory, OOP analysis, testing notes, limitations, and references.
- Added editable Mermaid sources for architecture, class relationships, main program flow, sequence interactions, and input-process-output.
- Registered the existing Week 2 test executable in CMake so CTest runs both Week 2 and Week 3 suites.
- Added validation for negative/non-finite feature-selection thresholds and invalid lambda candidates.
- Improved coordinate descent to estimate an unpenalized intercept and updated batch prediction to accept it; this substantially improved the bundled demo metrics.
- Tightened coordinate-descent validation for non-finite lambda and tolerance values.
- Added regression tests for invalid threshold and lambda inputs.
- Updated README links, file descriptions, build/test instructions, and OOP limitations.
- Preserved the original project concept, filenames, member-owned source layout, data, and individual report templates.

## Verified during review

- CMake configure and build completed with GNU C++ 14.2.0 in C++17 mode.
- Both Week 2 and Week 3 test suites passed via CTest after the changes.

## Real-life technology illustrations update (2026-10-22)
- Added `docs/figures/real_life_technology_applications.png`, a colour illustration of smart grids, sensor-based predictive maintenance, and renewable-energy forecasting.
- Expanded the technical report with current, cited technology examples and clear boundaries between existing features and proposed applications.
- Updated the README with the image location and interpretation notes.

## Technology case study update
- Added Section 16 on emerging technology directions associated with Tesla Optimus, Terafab, and SpaceX satellite infrastructure.
- Added source links and clearly distinguished real company developments from proposed LASSO use cases.
- Appended a visual technology case-study section to the technical PDF.
- Added a README note describing scope and limitations.


## Week 4 — validation and model improvement
- Added deterministic k-fold cross-validation for candidate LASSO lambda values.
- Added fold-level and mean validation RMSE reporting.
- Fit feature scaling on training folds only to avoid validation leakage.
- Added Week 4 demo, tests, report and coloured workflow figure.
- Preserved Week 2 and Week 3 implementation and test coverage.
