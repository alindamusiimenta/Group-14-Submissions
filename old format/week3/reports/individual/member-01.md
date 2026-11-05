# Individual Week 3 Report — Member 1

- Name: NANTALE PAULINE
- Student number: 2500708611
- Registration number: 25/U/08611/PS
- Branch: `member-01-data`
- Assigned part: Dataset loading and train/test splitting
- Pull request: 

## What my part means

This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

## Files changed

`src/member01_data.cpp and data/input/member01_week3_training.csv`

## What I added

I extended the data part by adding a larger CSV and a reproducible split. The function shuffles row indexes with a fixed seed, then copies each row and its matching target into either the training or testing dataset. Keeping the row and target together prevents the labels from becoming incorrect.

## How it fits into the full pipeline

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

## Testing

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected result is:

```text
All LASSO Week 3 tests passed.
```

Before final submission, I will replace this with the exact command, commit hash, and pull-request result from my branch.

## Week 4/final plan

Add a CSV-loading demonstration and tests for invalid split fractions.

## References

The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions. 
