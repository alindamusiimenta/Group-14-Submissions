# Individual Week 4 Report — Member 4

Name: ASIIMWE MARY
Student number: 2500700823
Branch: `member-04-matrix`
Assigned part: Multiple-row prediction
Pull request:

## What my part means

This is the Week 4 continuation of my Week 3 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

Files changed

`src/member04_matrix.cpp`

## How the code works
it creates an empty result vectorand loops oer each row of the matrix. It checks that the row length is equal to the vlues size otherwise sends  an invalid argument. it computes the dot product with an inner loop, calculates the total result and returns the result after the last row. lastly, it creates a predictions vector, loops over each sample,checks the number of features and starts the predictions. At the end of it all itt returns all the predictions. 

## How it fits into the full pipeline

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

## Testing

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected result is:


All LASSO Week 3 tests passed.


## References

Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996
C++ reference material for standard-library functions.
