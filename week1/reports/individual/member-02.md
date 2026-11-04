# Week 1 Report — Member 2: Data preprocessing

- **Name:** Karungi Mary Gorret
- **Student number:**25/U/0832
- **Branch:** `member-02-preprocessing`

## Foundation I built

I wrote two small yes/no checks on the shape of the data. `rows_match_target` is true when there is at least one row and exactly one target per row. `rows_have_equal_width` is true when every row has the same number of features as the first row. They return true or false and do not throw, so other members can use them in their own error handling. The cost function already uses both.

## Files
`src/member02_preprocessing.cpp`

## Why this comes first
A numerical algorithm gives wrong answers if rows and targets do not line up. These are the basic rules that every later check is built from.

## How Week 2 continues this part
I will combine the two checks into one function, `check_preprocessing_input`, that throws a clear error for each invalid case and is called before scaling and optimization.

## References
Robert Tibshirani, "Regression Shrinkage and Selection via the Lasso," *Journal of the Royal Statistical Society: Series B*, 1996, and cppreference.com for C++ library behavior. 