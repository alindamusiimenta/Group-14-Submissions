Individual Week 2 Report — Member 6

- Name: BUKENYA IVAN LUBEGA
- Student number: 2500708705
- Registration number: 25/U/08705/PS
- Branch: `week2/member-06-cost`
- Assigned part: LASSO cost function and L1 regularization
- Pull request: 
What my part means

LASSO cost function and L1 regularization is one stage in the LASSO pipeline. This report explains what the stage receives, what it does, and what it gives to the next stage.

Files changed

`examples/member06_cost.cpp and the cost code retained in src/lasso_regression.cpp`

What I did

I added a runnable cost example. The cost has a prediction-error part and an L1 part: `lambda * sum(abs(coefficients))`. Increasing lambda makes large coefficients more expensive, which encourages a simpler model.

How it fits into the full project

The output of this part is used by the next part of the pipeline. The group should not treat this module as an isolated program: it must use the same Vector, Matrix, feature order, target order, and error rules as the other members' modules.

Testing

I compiled the integrated Week 2 sources and ran tests/test_week2.cpp. The expected result is All LASSO Week 2 tests passed. I will replace this sentence with the exact command, commit, and test result from my branch before final submission.

What I will add in Week 3

I will check that the intercept is kept separate and is not accidentally penalized in the final model.