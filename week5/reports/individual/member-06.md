Individual Week 5 Report — Member-06
- Name: BUKENYA IVAN LUBEGA
- Student number: 2500708705
- Registration number: 25/U/08705/PS
- Branch: `week5/member-06-cost`
- Assigned part: LASSO cost and lambda comparison (`choose_lambda`)

What my part means

LASSO needs a lambda value that sets how strongly large coefficients are penalized. My function tries several candidates and returns the one with the lowest cost.

Files changed

src/member06_cost.cpp

What I did

The logic is the same as Week 4. In Week 5 I cleaned up the file with consistent indentation, wrapped long lines and added comments. The function works in these steps:
1. It checks the data with Member 2's check_preprocessing_input.
2. It throws `std::invalid_argument` if the candidate list is empty, or if any lambda is negative or not finite.
3. It starts with the first candidate as best and the best cost set to infinity.
4. For each candidate it runs Member 8's `coordinate_descent` (up to 500 iterations) and keeps the lambda whose `fit.cost` is lowest. A tie keeps the earlier candidate.
5. It returns the best lambda.

How it fits into the full project

It reuses the group's Matrix and Vector types and error rules. It is used in `examples/week3_demo.cpp` and `examples/member08_tuning.cpp` with candidates {0.01, 0.10, 0.50}. It is a demonstration helper, and Member 10's cross-validation is the proper selector.

Testing

`tests/test_week5.cpp` checks that a negative lambda is rejected and that the result is one of the candidates. The expected output is All LASSO Week 5 tests passed. Before final submission, I will replace this with the exact command, commit hash and pull-request result from my branch.

References

The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions.
