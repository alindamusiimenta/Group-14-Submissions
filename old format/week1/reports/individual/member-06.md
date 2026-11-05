Week 1 Report — Member 6: LASSO cost function and L1 regularization

- Name: Bukenya Ivan Lubega
- Student number: 2500708705
- Registration number: 25/U/08705/PS
- Branch: `week1/member-06-cost`

Foundation I built

I wrote lasso_cost. It has two parts: the squared prediction error divided by 2n, and the L1 penalty, which is lambda times the sum of the absolute values of the coefficients. The formula is cost = squared_error / (2n) + lambda * sum(abs(coefficients)). It checks the data shape with Member 2's functions, and rejects a coefficient vector of the wrong length and a negative or non-finite lambda. A larger lambda makes large coefficients more expensive, which is why LASSO prefers simpler models.

Files

src/lasso_regression.cpp (cost section); examples/member06_cost.cpp

Why this comes first

This is the quantity LASSO tries to make small. The optimizer needs it to measure progress.

How Week 2 continues this part

I will add a cost example, keep the cost consistent with the optimizer, and check that the intercept is not penalized in the final model.

Testing

tests/test_week1.cpp checks that features {{1,2},{2,1}}, target {5,4}, coefficients {1,2} and lambda 0.5 give 1.5. I will replace this with the exact command, commit, and result from my branch before submission.

References

Robert Tibshirani, "Regression Shrinkage and Selection via the Lasso," *Journal of the Royal Statistical Society: Series B*, 1996, and cppreference.com for C++ library behavior.