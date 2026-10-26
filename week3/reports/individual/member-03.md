# Individual Week 3 Report — Member 3
- **Name:** my name is MAWANDA HAKIM
- **Student number:** 2500703446
- **Branch:** `member-03-scaling`
- **Assigned part https://github.com/alindamusiimenta/Group-14-Submissions/pull/31

## What my part means
This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

## Files changed
`src/member03_scaling.cpp`

## What I added
I added a scaler that learns means and standard deviations from training features only. It saves those values and reuses them to transform both training and test data. This is important because test data must not teach the model how to preprocess itself.

## How it fits into the full pipeline
My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group

## Week 4/final plan
Add a small test proving that test transformation uses the training statistics.

## References
The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions.