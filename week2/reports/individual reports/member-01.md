# Individual Week 2 Report — Member 1

 Name: NANTALE PAULINE
 Student number: 2500708611
 Registration number: 25/U/08611/PS
 Branch: member-01-data
 Assigned part: Dataset loading
 Pull request: https://github.com/alindamusiimenta/Group-14-Submissions/pull/5
## What my part means

This stage is the entry point of the LASSO pipeline. In simple terms, it is where the data is read and organized so that the rest of the project can use it consistently. My role was to make sure the dataset is loaded in a clear structure, with the correct target and feature arrangement, so the subsequent preprocessing and modeling steps do not run into avoidable errors.

## Files changed

I changed the file.

## What I did

I prepared a small numerical CSV file for training data. The first column represents the target variable, while the remaining columns represent the feature values. This format is important because it keeps the data predictable and easy to interpret, allowing the model and preprocessing code to read each row without confusion. I focused on making the file simple, consistent, and ready to be used by the rest of the pipeline.

## How it fits into the full project

This part is not an isolated task; it is the foundation of the whole project. The output from this module is used by the next stage, so it needs to match the same `Vector`, `Matrix`, feature ordering, target ordering, and error-handling rules used by the other team members. If these details are inconsistent, the pipeline may still compile but fail in practice when the data is passed between modules.

## Testing

I compiled the integrated Week 2 sources and ran `tests/test_week2.cpp` to check that the data-loading stage works correctly within the overall application. The expected result is `All LASSO Week 2 tests passed.` I will update this section with the exact command, commit details, and final result from my branch before final submission.

## What I will add in Week 3

In Week 3, I plan to expand this work by testing how the loader handles empty rows, incomplete values, and non-numeric entries. These edge cases are common in real data, and handling them properly will make the pipeline more reliable and robust.

## References

The group reviewed the course notes and Robert Tibshirani’s paper, “Regression Shrinkage and Selection via the Lasso,” published in the *Journal of the Royal Statistical Society: Series B* in 1996. I also checked C++ syntax and standard-library behavior using cppreference when needed.