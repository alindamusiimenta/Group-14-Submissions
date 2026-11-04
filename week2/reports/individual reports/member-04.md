# Individual Week 2 Report — Member 4

Name: ASIIMWE MARY
Student number: 2500700823
Branch:`member-04-matrix`
Assigned part: Matrix and vector operations
Pull request: 

Matrix and vector operations is one stage in the LASSO pipeline. This report explains what the stage receives, what it does, and what it gives to the next stage.


`src/member04_matrix.cpp`
I added a small helper that multiplies every matrix row by a vector. For each row it multiplies matching values and adds them. This is the same type of calculation used to create a prediction from feature values and coefficients. The function checks that each row has the correct length.

The output of this part is used by the next part of the pipeline. The group should not treat this module as an isolated program: it must use the same `Vector`, `Matrix`, feature order, target order, and error rules as the other members' modules.

I compiled the integrated Week 2 sources and ran `tests/test_week2.cpp`. The expected result is `All LASSO Week 2 tests passed.` 

Use of AI tools
I did not use AI tools this week.
s
## References

The group consulted the course notes and Robert Tibshirani's paper, “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996. C++ syntax and standard-library behavior were checked with cppreference where needed. 
