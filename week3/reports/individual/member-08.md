# Individual Week 3 Report — Member 8

- **Name:** Mutonyi Jesca Mercy
- **Student number:** 2500707950 
- **Registration number:** 25/U/07950/PS
- **Branch:** `member-08-coordinate`
- **Assigned part:** Coordinate descent review and tuning

## What my part means

This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

## Files changed

`examples/member08_tuning.cpp and existing coordinate-descent source`

## What I added

I added an example that sends several lambda values through the coordinate-descent trainer. The optimizer still starts coefficients at zero, updates one coordinate at a time, applies soft-thresholding, and stops using its tolerance or maximum-pass rule.

## How it fits into the full pipeline

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

## Testing

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected result is:

```text
All LASSO Week 3 tests passed.
```

## Week 4/final plan

Verify the update formula on hand-calculated data and improve convergence reporting.

## References

The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions. 