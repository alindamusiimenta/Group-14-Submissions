# Individual Week 2 Report — Member 5

- Name: Zziwa Akram Ibrahim
- Student Number: 2400701442
- Branch: `member-05-baseline`
- Assigned Part: Linear Regression Baseline
- Pull Request: https://github.com/alindamusiimenta/Group-14-Submissions/pull/2

1. What My Part Means

The linear regression baseline is the first model used for comparison in the LASSO pipeline. It provides a reference point for evaluating how well LASSO performs.

2. Files Changed

- `examples/member05_baseline.cpp`

3. What I Did

I added an example of ordinary linear regression before applying LASSO. This gives the group a basic model whose performance can be compared with that of LASSO.

The comparison will help us determine the difference in prediction error and the number of features used by each model.

 4. How My Part Fits into the Full Project

My part provides a baseline model for the wider LASSO pipeline. To work correctly with the other modules, it must use the same `Vector` and `Matrix` data structures, feature order, target order, and error calculation methods.

This ensures that the results from the baseline and LASSO models can be compared fairly.

5. Testing

The planned testing involves compiling the integrated Week 2 source files and running `tests/test_week2.cpp`.

The expected success message is `All LASSO Week 2 tests passed.` However, the exact command and test result must be verified and recorded before the final submission.

6. Plans for Week 3

I plan to help develop a comparison between ordinary linear regression and LASSO. This will include comparing their prediction errors and the number of features used by each model.

7. References

The group consulted the course notes and Robert Tibshirani's 1996 paper, *Regression Shrinkage and Selection via the Lasso*, published in the *Journal of the Royal Statistical Society: Series B*.

C++ syntax and standard-library behavior were also checked using cppreference where necessary.


