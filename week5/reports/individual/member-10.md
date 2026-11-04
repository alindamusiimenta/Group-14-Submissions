Individual Report – Member 10

Name: KALID ALIAS
Student Number: 2500700831

Registration Number:  25/U/0831
Member Number: 10
Report Date: 4 November 2026
Assigned Role: Integration and Testing

1. Project Purpose

Our group project focuses on using numerical data to make predictions through regression models. We developed a C++ program that uses Linear Regression with one input feature and LASSO Regression with multiple input features.

We used sample data to demonstrate how the models work and how different numerical inputs can be used to predict a target value. The datasets were created for practice and testing rather than collected from real measurements.

2. My Assigned Area

My assigned role as Member 10 was Integration and Testing. This involved helping to bring the different parts of our project together, checking that they worked correctly and supporting the preparation of the final examples and reports.

My area of responsibility included the cross-validation implementation, CMake configuration, and the Week 4 and Week 5 demonstration programs.

3. My Contributions to the Project

During the development of the project, my responsibilities included the following areas:

Project integration: I worked on bringing the Linear Regression and LASSO Regression components together within one CMake project so that they could be built and tested as part of the same system.

Week 4 demonstration: I worked on the example that compares different lambda values using cross-validation. This helped demonstrate how we can evaluate different LASSO settings before choosing a suitable one.

Model validation: I helped maintain the separation between the training, validation and final test data. This is important because the final test data should not influence the model during training or the selection of its settings.

Week 5 templates: I helped connect the template examples and their tests to the main project build.

Documentation: I helped organise the final reports, UML diagrams and presentation materials.

These contributions relate to my assigned role in the project. The exact tasks listed should reflect the work I personally completed.

4. Project Building and Testing

As part of my integration and testing responsibilities, I worked with the CMake build system to check whether the different project components could be built and tested together.

We used the following commands:

Step 1: Configure the project

cmake -S . -B build

Step 2: Build the project

cmake --build build

Step 3: Run the tests

ctest --test-dir build --output-on-failure

The project test record shows that the build completed successfully and all five CTest programs passed. The Week 5 demonstration also ran successfully, and a separate CMake example was able to use the installed headers.

The five tests cover:

Week 2 LASSO.

Week 3 LASSO.

Week 4 validation.

Linear Regression.

Numeric Templates.

These tests helped us check whether the main components of our project were working as expected.

5. What I Learned

Working on this project helped me understand several important concepts in programming and machine learning.

One of the main things I learned was how cross-validation is used to compare different model settings. Instead of relying on only one portion of the training data, cross-validation divides the training data into different groups and uses them to evaluate the model.

I also learned why it is important to keep the final test data separate. This allows us to evaluate the model using data that was not used during training or model selection.

Another important concept I learned was the use of C++ templates. Templates allow us to write reusable classes that can work with different numerical data types, such as int, float and double.

In our Week 5 implementation, the template classes accept different numerical types, while the actual regression calculations are performed using double.

Overall, the project improved my understanding of C++ programming, project integration, testing and the practical application of regression techniques.

6. Challenges and Limitations

During the project, we encountered some limitations that affected what we could demonstrate.

Small sample datasets: The datasets used in our examples are small and made up for practice. Therefore, they cannot fully demonstrate how the models would perform with real-world data.

Textbook exercises: The textbook pages containing the Chapter 18 exercises were not supplied. We therefore could not verify or claim completion of those specific exercises.

Project organisation: Since the project contains several components developed across different weeks, bringing them together required attention to the CMake configuration, file organisation and testing.

Data type conversion: Although our template classes accept different numerical types, the regression calculations use double. This means that some conversions may affect numerical precision.

These challenges helped me appreciate the importance of testing, proper project organisation and understanding the limitations of the methods we use.

7. Use of AI Tools



The AI-use declaration for my assigned report is available at:

reports/ai-use-declaration-member-10.md



8. Conclusion

My role as Member 10 gave me an opportunity to participate in bringing the different parts of our project together and checking how they worked as one system.

Through this work, I gained practical experience in C++ project organisation, CMake, cross-validation, regression models and numerical templates.

The project also helped me understand the importance of teamwork, testing and proper documentation when developing a software project. Overall, it was a valuable learning experience that improved my programming skills and my understanding of how machine learning concepts can be implemented using C++.