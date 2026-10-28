Individual Week 4 Report — Member 6

- Name: BUKENYA IVAN LUBEGA
- Student number: 2500708705
- Branch: `member-06-cost`
- Assigned part: LASSO cost and lambda comparison
- Pull request: https://github.com/alindamusiimenta/Group-14-Submissions/pull/42#issue-6083021171

What my part means

This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

Files changed

`src/member06_cost.cpp`

What I added

I added a helper that tries several lambda candidates, trains a small fit for each one, and keeps the candidate with the lowest returned cost. This demonstrates that lambda is a model setting that must be compared rather than guessed.

How it fits into the full pipeline

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

Testing

I compiled the integrated Week 3 sources and ran `tests/test_week4.cpp`. The expected result is:

All LASSO Week 4 tests passed.

Before final submission, I will replace this with the exact command, commit hash, and pull-request result from my branch. 

References

The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” 
*Journal of the Royal Statistical Society: Series B*, 1996, and 
C++ reference material for standard-library functions.