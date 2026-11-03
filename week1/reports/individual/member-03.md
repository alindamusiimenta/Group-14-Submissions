# Week 1 Report: Member 3, Feature Scaling

**Name:** Mawanda Hakim
**Student number:** 2500703446
**Reg no:** 25/U/03446/EVE
**Course:** BCCE
**Branch:** member-03-scaling

## 1. My part of the project
My part is feature scaling. Before LASSO is trained, every feature column has to be put on a comparable scale. This week I did the first step: the two statistics that scaling depends on, computed for a single column of numbers.

## 2. What I built
I wrote two functions in `src/member03_scaling.cpp`:
- **`mean(values)`** adds up all the values and divides by the number of values. If the list is empty it throws an error, because the mean of nothing is undefined and returning 0 would hide a bug.
- **`standard_deviation(values)`** works out the mean, takes each value's difference from it, squares the differences, averages them, and then takes the square root.
I divide by n, not n - 1 (the population standard deviation). I chose this because the scaler describes the training column we actually have; it is not estimating a bigger population. Both versions work for scaling, but our team must use the same one everywhere so results can be reproduced.

## 3. Why standardization
I chose standardization: `scaled = (value - mean) / standard_deviation`.

LASSO adds a penalty on the size of the coefficients, the sum of |β_j|, and it applies the same penalty strength (λ) to every coefficient. If the features are in different units, this is unfair. For example, attendance runs from about 60 to 90, while study hours run from 1 to 5. To have the same effect on the prediction, study hours needs a much larger coefficient, so LASSO penalizes it more heavily and may shrink it to zero even though it is useful. After standardization every column has mean 0 and standard deviation 1, so the penalty treats all features equally.

I preferred standardization over min-max scaling because min-max depends on only two values (the smallest and largest), so one outlier can squash the rest of the column into a tiny range. The mean and standard deviation use every value, so they are more stable.

**Worked example (by hand):** for the column 1, 2, 3, the mean is 2 and the standard deviation is √(2/3) ≈ 0.8165. The scaled values are about -1.2247, 0 and 1.2247.

## 4. Important rule: training data only

The mean and standard deviation must be calculated from the **training rows only**. The test rows are then scaled using those same training numbers. If the test data were included in the calculation, information from the test set would leak into training and the reported accuracy would look better than it really is. I have noted this so that Week 2 and the team's train/test split follow it.

## 5. Edge cases I considered

| Case | How I handle it |
| Empty list | `mean` rejects it with an error |
| One value | The standard deviation is 0 (handled in Week 2) |
| All values equal | The standard deviation is 0, so scaling would divide by zero (handled in Week 2) |
Both functions go through the data once, so they run in O(n) time.

## 6. Files
- `src/member03_scaling.cpp`: the implementation
- `tests/test_week1.cpp`: the tests

## 7. Testing
`tests/test_week1.cpp` checks three things:

1. The mean of 1, 2, 3 is 2.
2. The standard deviation of 2, 4, 4, 4, 5, 5, 7, 9 is 2. (Its mean is 5, the squared differences average to 4, and √4 = 2.)
3. The mean of an empty list is rejected.

## 8. Plan for Week 2

- Apply the mean and standard deviation to every column of the feature matrix.
- Return the scaled matrix together with the saved means and standard deviations, so the test data can be scaled with the same numbers.
- Handle a standard deviation of zero safely, so no column causes a division by zero.
- Agree with the team on the matrix format so my output fits the LASSO training code.

## 9. References

- R. Tibshirani, "Regression Shrinkage and Selection via the Lasso," *Journal of the Royal Statistical Society: Series B*, 58(1), 1996.
- cppreference.com, for C++ standard library behavior (`<cmath>`, `<stdexcept>`, `<vector>`).