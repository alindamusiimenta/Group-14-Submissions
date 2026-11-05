
# Individual Final  Report  Member 09

Name:SSENABULYA SAMUEL
Student number: 25/U/24150
Branch: FINAL REPORT
Assigned part: Regression evaluation metrics
Pull request:Add the real pull-request link

## 1. What it does

The function mean_absolute_error tells us, on average, how far a model's predictions are from the real values. A smaller number means better predictions. A result of 0 means every prediction was exactly right.

MAE is easy to read because it is in the same units as the data. If we are predicting prices in dollars and the MAE is 5, our predictions are off by about 5 dollars on average.

## 2. How it works

The function takes two lists of numbers: the actual values and the predicted values. It does not do the work itself. It passes both lists to evaluate_regression, which calculates all the regression metrics, and then returns only the MAE part.

Inside, the steps are:

1. Check that the two lists are valid.
2. Go through the lists one pair at a time and find how far each prediction is from the real value, ignoring whether it was too high or too low.
3. Add all those distances together.
4. Divide the total by the number of values to get the average.

## 3. Input checks

The function stops and throws an invalid_argument error if:

- either list is empty,
- the two lists are not the same length, or
- any value is not a real number (NaN or infinity).

This protects the result from bad data and makes mistakes easy to spot.

## 4. Simple example

Suppose the actual values are 3, 5 and 7, and the model predicts 2.5, 5 and 8.

| Sample | Actual | Predicted | Distance off |
| ------ | ------ | --------- | ------------ |
| 1      | 3      | 2.5       | 0.5          |
| 2      | 5      | 5         | 0            |
| 3      | 7      | 8         | 1            |

The distances add up to 1.5. Dividing by 3 samples gives an MAE of 0.5, so the model is off by half a unit on average.

## 5. Things to know

- **All errors count equally.** One big miss does not stand out more than several small ones. This makes MAE less sensitive to outliers than squared-error metrics.
- **It does not show direction.** MAE cannot tell us whether the model tends to guess too high or too low.
- **Extra work.** Because it calls evaluate_regression, it also computes MSE, RMSE and R-squared and then throws them away. This is correct, just slightly wasteful.

## 6. Suggested tests

- Perfect predictions should give an MAE of 0.
- The example above should give 0.5.
- Empty lists should throw an error.
- Lists of different lengths should throw an error.
- A list containing NaN should throw an error.

## 7. Summary

mean_absolute_error is a short, clear function that gives the average size of a model's mistakes. It checks its input carefully and reuses the shared evaluation code, so it stays consistent with the other metrics. The only improvement worth considering is a dedicated version that skips the unused calculations.
