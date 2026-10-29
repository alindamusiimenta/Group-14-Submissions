[week-01-member-01.md](https://github.com/user-attachments/files/34128999/week-01-member-01.md)[Uploading wee# Week 1 Progress Report — LASSO Regression

Report owner: Member 01 (data and CSV foundations)  
Record note: This report summarizes the supplied Week 1 project files. It is reconstructed from the archive and does not claim a historical date or commit.

## Purpose of this week

Set the project topic and create a small C++ foundation for learning how LASSO regression works.

## Completed

- Chose LASSO regression as the project topic.
- Set up folders for headers, source code, examples, tests, and input data.
- Added basic `Vector`, `Matrix`, and `Dataset` types.
- Added functions for reading a simple CSV, calculating a dot product and LASSO cost, and applying soft-thresholding.
- Added a small synthetic CSV, a simple example, and basic tests.

## How the Week 1 program works

The CSV stores the target value in its first column and feature values in the remaining columns. The LASSO cost combines prediction error with a penalty on coefficient size. Soft-thresholding moves a coefficient toward zero; this is the basic operation used later to shrink less useful features.

Week 1 lays out these ideas but does not yet train a complete multi-feature LASSO model. The code uses functions and simple data structures; the separate `LinearRegression` class is part of the later baseline work.

## In Progress

- Build a complete model that learns coefficients from several features.
- Improve input checks and make error messages clearer.

## Challenges/Blockers

- Choosing a suitable regularization value needs more than looking at the training data.
- The small sample is synthetic and is only useful for learning and testing.

## Next Week

- Add a one-feature linear-regression baseline.
- Add feature standardization and coordinate descent for LASSO fitting.
- Expand tests to cover invalid inputs.

## Individual reports

Each group member will add their own verified report in `reports/individual/`. This group progress report does not replace those individual reports.

## AI Use

- Tool: OpenAI Codex.
- Purpose: Review the supplied Week 1 files and help write this report in the Week 3 format.
- Reason: To support code review and documentation. Group members should check the report and understand the code before submission.
k-01-member-01.md…]()
