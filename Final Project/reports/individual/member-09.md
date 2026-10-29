# Individual Final  Report  Member 09

Name:SSENABULYA SAMUEL
Student number: 25/U/24150
Branch: FINAL REPORT
Assigned part: Regression evaluation metrics
Pull request:Add the real pull-request link

## What my part means

This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

## Files changed

`src/member09_evaluation.cpp`

## What I added

I added MAE, MSE, RMSE, and R-squared. These metrics describe different parts of model performance: average error size, squared error, error in target units, and comparison with predicting the target mean.

## How it fits into the full pipeline

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

## Testing

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected result is:

## Week 4/final plan

Add tests for perfect predictions, constant targets, and a held-out test result.

## References

I used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions. I will replace this with the exact sources I actually consulted.
