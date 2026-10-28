# Individual Week 3 Report — Member 4

Name: ASIIMWE MARY
Student number: 2500700823
Branch:`member-04-matrix`
Assigned part:Multiple-row prediction
Pull request:https://github.com/alindmusiimenta/Group-14-Submissions/pull40

This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

Files changed

`src/member04_matrix.cpp`

I added a function that receives many feature rows and one coefficient vector. It calculates one dot product per row and returns all predictions. It also rejects rows whose width does not match the number of coefficients.

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected result is:

All LASSO Week 3 tests passed.

Week 4 final plan

Add tests for empty rows, several coefficients, and prediction examples.

References

The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions. 
