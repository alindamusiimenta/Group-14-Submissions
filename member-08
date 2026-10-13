Name: Mutonyi Jesca Mercy
Student number: 2500707950
Registration number: 25/U/07950/PS
Branch: `member-08-coordinate`
Assigned part: Coordinate descent optimization
Pull request: Add the real pull-request link after opening it

What my part means
Coordinate descent optimization is one stage in the LASSO regression pipeline. It is the step that learns the coefficients: it updates one coefficient at a time and uses the soft threshold to shrink weak coefficients toward zero.

Files changed
src/member08_coordinate_descent.cpp

What I did
I added the first simple optimizer. It starts all coefficients at zero and updates them one at a time using the soft-threshold step. After each full pass it checks how much the coefficients changed, and it stops when the changes become small.

How it fits into the full project
The output of this part is used by the next part of the pipeline. The trained coefficients go to Member 9's evaluation, which measures the error of the predictions. My loop takes the standardized features from Member 3 and reuses the Week 1 soft_threshold helper.

Testing
I compiled the integrated Week 2 sources and ran tests/test_week2.cpp.

What I will add in Week 3
I will check the update formula on small hand-calculated examples and test different λ values to see how many coefficients shrink to zero.

## References

The group consulted the course notes and Robert Tibshirani's paper, “Regression Shrinkage and Selection via the Lasso,” Journal of the Royal Statistical Society: Series B\*, 1996. C++ syntax and standard-library behavior were checked with cppreference where needed.
