INDIVIDUAL WEEK 2 REPORT

Name: BUKENYA IVAN LUBEGA
Registration number : 25/U/08705/PS
Student number: 2500708705

Assigned part:LASSO cost function and L1 regularization
Pull request:Add the real pull-request link after opening it

What this part means

LASSO cost function and L1 regularization is one stage in the LASSO pipeline. This report explains what the stage receives, what it does, and what it gives to the next stage.

Files changed

examples/member06_cost.cpp and the cost code retained in src/lasso_regression.cpp

What I did

I added a runnable cost example. The cost has a prediction-error part and an L1 part:lambda * sum(abs(coefficients)). Increasing lambda makes large coefficients more expensive, which encourages a simpler model.

How it fits into the full project

The output of this part is used by the next part of the pipeline. 

Testing

I compiled the integrated Week 2 sources and ran tests/test_week2.cpp. The expected result is All LASSO Week 2 tests passed. 

References
The group consulted the course notes and Robert Tibshirani's paper, “Regression Shrinkage and Selection via the Lasso,” Journal of the Royal Statistical Society: Series B, 1996. C++ syntax and standard-library behavior were checked with cppreference where needed.