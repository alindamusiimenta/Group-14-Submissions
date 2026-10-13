
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