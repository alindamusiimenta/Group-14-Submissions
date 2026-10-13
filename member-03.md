# Individual Week 2 Report — Member 3

Name: MAWANDA HAKIM
Student number: 2500703446
Branch: member-03-scaling
Assigned part: Feature scaling
Pull request: 

# What my part means
Feature scaling is one stage in the LASSO pipeline. This report explains what the stage receives, what it does, and what it gives to the next stage.

# Files changed
src/member03_scaling.cpp

# What I did
I added standardization. For each feature column, the code calculates the mean and standard deviation, then changes each value using `(value - mean) / standard deviation`. This puts features on a comparable scale before coordinate descent. The function also returns the means and standard deviations so they can be reused later.

# How it fits into the full project
The output of this part is used by the next part of the pipeline. The group should not treat this module as an isolated program: it must use the same `Vector`, `Matrix`, feature order, target order, and error rules as the other members' modules.

#Testing
I compiled the integrated Week 2 sources and ran tests/test_week2.cpp. The expected result is All LASSO Week 2 tests passed. I will replace this sentence with the exact command, commit, and test result from my branch before final submission.

# What I will add in Week 3
I will make sure the final version calculates scaling statistics from training data only and reuses them on test data.

#References
The group consulted the course notes and Robert Tibshirani's paper, “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996. C++ syntax and standard-library behavior were checked with cppreference where needed. 

