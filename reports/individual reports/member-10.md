
## Individual Week 2 Report: Member 10
• Name: kalid Alias
• Reg number 25/U/0831
• Student number:  2500700831
• Branch: member-10-build-integration
• Assigned part: Build integration, examples, and tests
• Pull request: https://github.com/alindamusiimenta/Group-14-Submissions/pull/4

## My part in the project## 
My job was to make sure everyone's separate pieces of the LASSO project actually work together. Each member wrote their own source file, such as scaling and the coordinate descent optimizer. My part was to connect those files so they build as one library, and to check that they behave correctly togethers.
## Files I changed
• CMakeLists.txt
• examples/week2_demo.cpp
• tests/test_week2.cpp
## What I did
First, I updated CMakeLists.txt so that the members' source files are compiled together into one library. Before this, each file only worked on its own.
Second, I wrote a demo program in examples/week2_demo.cpp. It runs feature scaling and then coordinate descent one after the other, so we can see the two parts working as a pipeline.
Third, I wrote a test program in tests/test_week2.cpp. It checks four things: the means, the optimizer output, the evaluation results, and how the code handles invalid input.
How it fits into the whole project
My part sits on top of everyone else's work. If a module uses a different Vector or Matrix type, a different feature order, or different error handling, the build and the tests will fail. So I had to make sure all modules follow the same conventions. The output of my part is a working build that the rest of the group can use for the next stage.
## what i did during testing
I compiled the integrated Week 2 sources and ran tests/test_week2.cpp. The command I used was [exact command], on commit [commit id]. The result was [paste the real output, for example: "All LASSO Week 2 tests passed."].
## What I will do in Week 3 possibly 
In Week 3, I will do a clean build from scratch, review my teammates' pull requests, and help coordinate the final integration.
## The References i managed to use to accomplish my part
• Tibshirani, R. (1996). Regression Shrinkage and Selection via the Lasso. Journal of the Royal Statistical Society: Series B.
• Course notes for the module.
• cppreference.com, for C++ syntax and standard library behaviour.



## WEEK 3
# Individual Week 3 Report — Member 10

- Name:KALID ALIAS
- Student number:25/U/0831
- Branch:`member-10-build-integration`
- Assigned part:  Week 3 integration, tests, and demo
- Pull request:
## What my part means

This is the Week 3 continuation of my Week 2 module. The purpose is to add one step needed for a fair LASSO experiment rather than writing an unrelated piece of code.

## Files changed

`CMakeLists.txt, tests/test_week3.cpp, examples/week3_demo.cpp`

## What I added

I connected all Week 3 source files in CMake. The tests check the split, scaler, predictions, feature selection, lambda comparison, and metrics. The demo runs the workflow and prints the chosen lambda, test errors, and selected-feature count.

## How it fits into the full pipeline

My part receives data or model results from the previous stage and passes a clear result to the next stage. It must keep the same row order, feature order, `Vector` and `Matrix` types, and error-handling rules used by the rest of the group.

## Testing

I compiled the integrated Week 3 sources and ran `tests/test_week3.cpp`. The expected result is:

```text
All LASSO Week 3 tests passed.
```

Before final submission, I will replace this with the exact command, commit hash, and pull-request result from my branch.

## Week 4/final plan

Run a clean final build, review all pull requests, and package the final project.

## References

The group used the course notes, Robert Tibshirani's paper “Regression Shrinkage and Selection via the Lasso,” *Journal of the Royal Statistical Society: Series B*, 1996, and C++ reference material for standard-library functions.