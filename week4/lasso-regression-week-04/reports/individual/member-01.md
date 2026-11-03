# Individual Report — Member 1

- Name: NANTALE PAULINE
- Student number: 2500708611
- Registration number: 25/U/08611/PS
- Branch: `member-01-data`
- Assigned work: Dataset loading and train/test splitting
- Pull request: Not listed

## Overview

I continued my Week 2 data module by adding the train/test split needed to evaluate the LASSO model fairly. This builds on the existing work rather than introducing a separate component.

## Files changed

- `src/member01_data.cpp`
- `data/input/member01_week3_training.csv`

## Work completed

I added a larger CSV dataset and implemented a reproducible train/test split. The function shuffles the row indexes using a fixed seed, then places each row and its corresponding target in the same dataset. This keeps the features matched with the correct labels.

## How it fits into the project

This module prepares the data for the next stage of the LASSO pipeline. It follows the project's existing conventions for row and feature order, `Vector` and `Matrix` types, and error handling.

## Testing

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected test output is:

```text
All LASSO Week 3 tests passed.
```

The exact command, commit hash, and pull-request link are not recorded in this report.

## Next steps

I plan to add a CSV-loading demonstration and tests for invalid train/test split fractions.

## References

The work draws on the course notes, Robert Tibshirani's 1996 paper, “Regression Shrinkage and Selection via the Lasso,” published in the *Journal of the Royal Statistical Society: Series B*, and C++ reference material for standard-library functions.
