# Week 1 Report — Member 1: Dataset loading

- Name:NANTALE PAULINE
- Registration number: 25/U/08611/PS
- Student number:2500708611

## Foundation I built

I defined the data format for the whole project and wrote the function that reads it. The format is a CSV file with a header row; the first column is the target and every other column is a feature. `load_csv` opens the file, skips the header, converts each cell to a number, and stores the target and the feature row separately. It throws an error if the file cannot be opened, a cell is not a number, a row has fewer than two cells, rows have different widths, or there are no data rows. The sample file has 3 rows and 2 features.

## Files

`data/input/member01_training.csv`; loader section in `src/lasso_regression.cpp`

## Why this comes first

Nothing else can run without data. Fixing the format now means every member writes code for the same layout, and the target is always column 0.

## How Week 2 continues this part

I will replace the 3-row sample with the shared training file that has real features (`study_hours`, `attendance`, `assignments`) and a target score.

## Testing

`tests/test_week1.cpp` writes a small CSV, loads it, and checks the target and feature values. I will replace this with the exact command, commit, and result from my branch before submission.

## References

Robert Tibshirani, "Regression Shrinkage and Selection via the Lasso," *Journal of the Royal Statistical Society: Series B*, 1996, and cppreference.com for C++ library behavior. I will list only what I actually used.
