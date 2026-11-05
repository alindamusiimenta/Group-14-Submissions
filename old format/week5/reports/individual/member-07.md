# Individual Week 5 Report — Member 7

- **Name:** Alinda Larry Musiimenta
- **Student number:** 2500708684
- **Branch:** `member-07-soft-threshold`
- **Assigned part:** Soft-thresholding demonstration and feature selection

## What my part means

My part demonstrates how LASSO can shrink coefficient values toward zero and how the resulting coefficients can be used to identify selected features. The implementation returns the indexes of coefficients whose absolute values are greater than a chosen threshold.

## Files covered

`src/member07_soft_threshold copy.cpp` and `examples/member07_soft_threshold.cpp`

## What I added

The feature-selection helper first checks that the threshold is finite and non-negative. It then checks that each coefficient is finite, compares the coefficient's absolute value with the threshold, and stores the index when the magnitude is strictly greater. Invalid thresholds or non-finite coefficients cause an `std::invalid_argument` exception instead of producing a misleading selection.

The example demonstrates soft-thresholding with positive, negative, and small values. It also calls `selected_features` with `{2.4, 0.0000001, -1.1}`. With the default threshold of `0.000001`, the expected selected indexes are `0` and `2`: the middle coefficient is too small, while the first and third coefficients exceed the threshold in magnitude.

## How it fits into the full pipeline

After a LASSO model has produced coefficients, feature selection can use their magnitudes to report which features remain above a chosen cutoff. Returning indexes preserves the original feature ordering and lets later code associate selected coefficients with the corresponding input columns.

## Testing

The example's expected output for the soft-thresholding calls is `3`, `-3`, and `0`; the selected feature indexes are `0` and `2`. I have not run the build or test suite for this report, so these are expected results based on the code rather than recorded test results.

## Week 5/final plan

Run the Week 5 build and tests, and add or confirm tests for invalid thresholds, non-finite coefficients, and coefficients exactly at the selection threshold.

## References

The project headers and the Week 4 individual report were used to follow the existing LASSO interfaces and report format.
