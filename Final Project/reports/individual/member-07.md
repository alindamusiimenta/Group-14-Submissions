# Individual Week 3 Report — Member 7

- **Name:** Alinda Larry Musiimenta
- **Student number:** 2500708684
- **Branch:** `member-07-soft-threshold`
- **Assigned part:** Soft-thresholding and feature selection

## What my part means

This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

## Files changed

`src/member07_soft_threshold.cpp and examples/member07_soft_threshold.cpp`

## What I added

I extended the soft-thresholding work with a feature-selection helper. It checks the absolute size of each final coefficient and returns the indexes whose values are larger than the chosen threshold. Small coefficients are treated as removed features.

## How it fits into the full pipeline

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

## Testing

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected result is:

```text
All LASSO Week 3 tests passed.
```

Before final submission, I will replace this with the exact command, commit hash, and pull-request result from my branch.

## Week 4/final plan

Add more tests around the threshold and print feature names as well as indexes.

## References

The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions. I will replace this with the exact sources I actually consulted.
