# Week 5 Group Progress Report — Final Project

**Group:** Group 14  
**Project:** LASSO Regression in C++  from scratch
**Report Date:** 4 November 2026

## 1. Goal for Week 5

Our main goal for Week 5 was to complete the final project and follow the lecturer's instructions on using C++ templates where they were appropriate.

We wanted to make our program more flexible by allowing it to work with different number types, including `short`, `int`, `float`, and `double`.

## 2. Work Completed

During this week, we worked on the following:

- We added a reusable Matrix template for storing and working with numerical values.
- We added templates for reading CSV files and organizing input features and target values.
- We added typed interfaces for our Linear Regression and LASSO Regression models.
- We made it possible for the models to accept different number types while using `double` for the main calculations.
- We created a Week 5 example and tests to check whether the templates were working correctly.
- We prepared notes explaining our template design, questions for the group, and a class diagram.
- We updated the CMake build files and project reports.

In simple terms, a template allows us to write code once and use it with different data types instead of writing separate code for each type.

## 3. Test Results

We successfully built the project using CMake, and all five tests passed. These tests covered:

1. Week 2 LASSO.
2. Week 3 LASSO.
3. Week 4 validation.
4. Linear Regression.
5. Numeric templates.

We also ran the Week 5 example, which successfully read 8 rows from the CSV file, with 3 input features.

The example also tested multiplication between an integer matrix and float values. Both the typed Linear Regression and LASSO models produced a prediction of 11 for an input value of 5.

We further tested the installation process. After installing the project, we created a separate CMake example that used the installed header files, and it ran successfully.

## 4. Challenges and Limitations

Although we completed the main tasks, we identified some limitations:

- Our sample dataset is small and was created for practice rather than collected from real measurements.
- The model calculations use `double` to keep the implementation consistent, but this type cannot represent every numerical value exactly.
- When converting values to integer types, our program rejects decimal values and values outside the supported range.
- Logistic Regression, Graph Neural Networks (GNNs), and Convolutional Neural Networks (CNNs) were considered as possible examples of template use, but they are outside the current scope of our LASSO project.
- The lecturer mentioned exercises from Chapter 18, but we did not have the textbook or the actual exercise questions available. We therefore still need to check the assigned textbook.

## 5. Work Remaining Before Submission

Before submitting our final project, we need to:

- Ensure that every member completes their individual report and describes the work they actually performed.
- Check the Chapter 18 exercises in the assigned textbook and include the relevant exercise numbers or questions.
- Make sure every group member understands the code, the concepts used, and the test results so that they can explain their contributions during the presentation.

## 6. Use of AI Tools

We used AI tools, including OpenAI Codex, to support parts of our project development. The tools helped us review and improve code, work on C++ templates and tests, prepare diagrams, and organize our reports.

We reviewed the generated work and used it to support our understanding of the project. As a group, we remain responsible for the final code, reports, and explanations presented in our submission.