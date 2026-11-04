# Individual Week 2 Report — Member 9

Name: SSENABULYA SAMUEL
Student number: 25/U/24150
Branch:`SSENABULYA SAMUEL-MEMBER 09`
Assigned part: Model evaluation.
Pull request:#9
## What my part means
Model evaluation is one stage in the LASSO pipeline. This report explains what the stage receives, what it does, and what it gives to the next stage.

## Files changed

`src/member09_evaluation.cpp`

## What I did
I added mean absolute error. The code subtracts each prediction from the actual value, takes the absolute value, adds the errors, and divides by the number of observations. The result is in the same units as the target, so it is easy to explain.

## How it fits into the full project
The output of this part is used by the next part of the pipeline. and should not be treated as an isolated program: it must use the same `Vector`, `Matrix`, feature order, target order, and error rules as the other members' modules.

## Testing
I compiled the integrated Week 2 sources and ran `tests/test week2.cpp`. The expected result is `All LASSO Week 2 tests passed.` I will replace this sentence with the exact command, commit, and test result from my branch before final submission.

## What I will add in Week 3
I will add MSE, RMSE, and R-squared and calculate them on data not used for training.

 ## References
 I consulted the course notes and Robert Tibshirani's paper, “Regression Shrinkage and Selection via the Lasso,” Journal of the Royal Statistical Society: Series B, 1996. C++ syntax and standard-library behavior were checked with cppreference where needed.  