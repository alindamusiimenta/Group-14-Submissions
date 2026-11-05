# Week 1 Report — Member 9: Model evaluation

- **Name:** SSENABULYA SAMUEL
- **Student number:** 25/U/24150
- **Branch:** `SAMUEL-WK-1`
- **Pull request:** Add the real pull-request link after opening it

## Foundation I built

I wrote `mean_squared_error`, which subtracts each prediction from the actual value, squares the difference, adds them up, and divides by the number of values. It rejects empty vectors and vectors of different sizes. I also defined the other measures for later: MAE is the average of the absolute errors, RMSE is the square root of MSE, and R-squared compares the model's error with the error of always predicting the mean. A model must be judged on rows it was not trained on.

## Files

`src/member09_evaluation.cpp`

## Why this comes first

I need one agreed way to measure error before it can compare the baseline and LASSO.

## How Week 2 continues this part

I will add mean absolute error, which is easier to read because it is in the same units as the target, and later RMSE and R-squared.

## Testing

`tests/test_week1.cpp` checks that actual `{1,2,3}` and predicted `{2,2,4}` give 2/3.  

## References

Robert Tibshirani, "Regression Shrinkage and Selection via the Lasso," *Journal of the Royal Statistical Society: Series B*, 1996, and cppreference.com for C++ library behavior. I will list only what I actually used.
