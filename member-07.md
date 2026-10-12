# Individual Week 2 Report — Member 7

- Name: ALINDA LARRY MUSIIMENTA
- Registration number: 25/U/08684/PS
- Student number: 2500708684
- Branch: `member-07-soft-threshold`
- Assigned part: Soft-thresholding
- Pull request: https://github.com/alindamusiimenta/Group-14-Submissions/pull/1

## What my part means

Soft-thresholding is one stage in the LASSO pipeline. This report explains what the stage receives, what it does, and what it gives to the next stage.

## Files changed

`examples/member07_soft_threshold.cpp and the helper retained in src/lasso_regression.cpp`

## What I did

I demonstrated soft-thresholding for positive, negative, and small values. A large positive value is reduced, a large negative value moves toward zero, and a value inside the threshold becomes zero. This is the shrinkage step that helps LASSO remove features.

## How it fits into the full project

The output of this part is used by the next part of the pipeline. The group should not treat this module as an isolated program: it must use the same `Vector`, `Matrix`, feature order, target order, and error rules as the other members' modules.

## Testing

I compiled the integrated Week 2 sources and ran `tests/test_week2.cpp`. The expected result is `All LASSO Week 2 tests passed.` I will replace this sentence with the exact command, commit, and test result from my branch before final submission.

## What I will add in Week 3

I will add edge-case tests and connect the explanation directly to the coordinate-descent update.

## References

The group consulted the course notes and Robert Tibshirani's paper, “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996. C++ syntax and standard-library behavior were checked with cppreference where needed.
