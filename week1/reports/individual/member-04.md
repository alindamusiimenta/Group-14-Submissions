Week 1 Report — Member 04: Matrix Operations 
Name: ASIIMWE MARY 
Student number: 25/U/0823
Branch: member-04-matrix 

Foundation I built 

I implemented the basic matrix operations required for the Lasso Regression project. The main functionality involves multiplying a matrix by a vector using the multiply_rows() function. It calculates the dot product of each matrix row with the corresponding vector elements to produce a resulting vector.

I also included dimension validation to ensure that the number of elements in each matrix row matches the size of the vector before multiplication is performed. If the dimensions do not match, the program throws a clear std::invalid_argument error instead of attempting an invalid calculation.

Additionally, the predict_rows() function uses matrix–vector multiplication to calculate predicted values based on the input feature matrix, model coefficients and intercept.

Files 

member04_matrix.cpp

Why this comes first 

Matrix operations are essential in Lasso Regression because the algorithm works with datasets containing multiple features and observations. The feature matrix represents the input data, while the coefficient vector contains the weights assigned to each feature.

Multiplying these allows the program to calculate predicted values for the observations. These predictions are later used in calculating errors and evaluating the cost function.

Without reliable matrix operations and dimension checking, the regression algorithm could produce incorrect results or encounter runtime errors.

How Week 2 continues this part 

I will continue improving the matrix operations by integrating them with the other components of the Lasso Regression project. This will involve ensuring that matrix–vector multiplication and prediction functions work correctly with the preprocessing, cost function and optimization modules.

I will also work towards making the matrix operations reusable through the shared project interface in lasso/week2.hpp, allowing other members to call them without duplicating code.

References 

Robert Tibshirani, "Regression Shrinkage and Selection via the Lasso," Journal of the Royal Statistical Society: Series B, 1996, and cppreference.com for C++ library behavior.

