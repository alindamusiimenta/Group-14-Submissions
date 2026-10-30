# Week 4 Progress Report — Final LASSO Validation

**Report owner:** Member 10 (integration and validation)  
**Record note:** Final report assembled on 2026-10-28 from the supplied Week 4 package and the integrated project. It reports the current build and test run; it does not invent earlier completion dates or Git activity.

## Completed

- Implemented deterministic k-fold cross-validation for candidate LASSO lambda values.
- Selected lambda by mean validation RMSE.
- Fit each fold's scaler only on that fold's training rows.
- Updated the demonstration to keep an outer test split out of both cross-validation and scaling.
- Added CMake targets for the LASSO and one-feature linear-regression libraries, all examples, and four test executables.
- Ran the full build and CTest suite; all four tests passed.

## In Progress

- The software package is assembled. The group should add real member names and student numbers to its cover material if required by the course.
- The GitHub repository and member commit/PR evidence must be supplied from the group's own account; those records were not in the uploaded archives.

## Challenges/Blockers

- The included data are synthetic and small, so the reported scores demonstrate the workflow rather than establish real-world model performance.
- Cross-validation and test metrics can vary if the data or seed changes.
- Inheritance and polymorphism are not used in the current design; the project demonstrates encapsulation and composition instead.

## Final demo result

With the bundled synthetic data and seed 42, the example used 9 training rows and 3 held-out test rows. Cross-validation selected lambda `0.0010`; the mean four-fold validation RMSE was `0.0871`. Held-out test results were MAE `0.0510`, RMSE `0.0716`, and R-squared `0.9977`. These results apply only to this small demonstration dataset.

## Next Week

- Review the reports and code as a group and replace member identifiers with verified names if needed.
- Push the finished package to the required GitHub repository and preserve genuine contribution evidence.
- Prepare each member to explain the fitting, scaling, validation, and test workflow.

## AI Use

- **Tool:** OpenAI Codex.
- **Purpose:** Review and refine the implementation, integrate CMake targets, run the build and tests, and prepare the final reports and diagrams.
- **Reason:** To support debugging and documentation; group members should verify the results and be able to explain the code.
