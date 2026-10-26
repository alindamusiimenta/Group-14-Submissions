# Individual Week 1 Report — Member 07

**Project:** LASSO Regression From Scratch in C++17  
**Assigned area:** L1 regularization  
**Student name:** ALINDA LARRY MUSIIMENTA
**Student number:** 2500708684
**Registration number:** 25/U/08684/PS 
**Week:** 1

## 1. Introduction
This report documents the Week 1 planning and foundation work for **l1 regularization**, a component of the group project to build LASSO regression from scratch in C++17.

## 2. Objective
Explain coefficient shrinkage and why some coefficients can become zero.

## 3. Week 1 work and understanding
Week 1 focuses on understanding the requirement, agreeing on inputs and outputs, documenting the mathematical or software design, and identifying tests. Full integration and model fitting are staged across later weeks; this report must not claim unimplemented work as complete.

## 4. Relevant mathematics or technical design
LASSO minimizes a squared-error term plus an L1 penalty:

\[
J(\\boldsymbol{\\beta})=\\frac{1}{2n}\\sum_{i=1}^n(y_i-\\mathbf{x}_i^T\\boldsymbol{\\beta})^2+\\lambda\\sum_{j=1}^p|\\beta_j|.
\]

The parameter \\(\\lambda\\geq0\\) controls the strength of regularization. The intercept is normally kept outside the L1 penalty. Include further equations or API details specific to this assigned area before submission.

## 5. Illustration
Refer to the labelled figures in `../..//docs/figures/`: the fitted-baseline plot shows the data workflow context, the function workflow shows the Week 1 pipeline, and the soft-thresholding plot illustrates coefficient shrinkage. Explain which figure best supports this member's task.

## 6. Evidence and testing
Record the relevant function, test case, reading, design note, or code review completed for this task. If implementation is planned for Week 2 or 3, state that clearly.

## 7. Challenges and next steps
- Challenge or unresolved decision: ____________________
- Next action for Week 2: ____________________
- Evidence to attach: ____________________

## 8. Conclusion
Summarize what was understood or defined in Week 1 and how this work will support later integration.

## 9. References
1. Tibshirani, R. (1996). Regression Shrinkage and Selection via the Lasso. *Journal of the Royal Statistical Society: Series B*, 58(1), 267–288.
2. C++ reference documentation: https://en.cppreference.com/
