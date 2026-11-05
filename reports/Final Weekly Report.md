# Week 5

A# Group 14 – Week 5 Final Project

## 1. Project Purpose

In this project, we developed a C++ program that uses numerical data to predict a target value. We used Linear Regression and LASSO Regression to understand how different inputs can be used to make predictions.

Our sample dataset contains three input features: study hours, attendance, and assignments. The program uses these inputs to predict a target value.

We also wanted to understand how LASSO helps improve a regression model by reducing the influence of features that contribute less to the prediction.

The sample data we used are made up for practice and testing. They are not real measurements.

## 2. What Our Program Does

As a group, we developed the program to perform several tasks:

- Reads numerical data from a CSV file and checks whether the data is valid.
- Scales the input features so that they can be compared on similar ranges.
- Builds a simple Linear Regression model using one feature.
- Builds a LASSO Regression model using multiple features.
- Uses cross-validation to compare different LASSO settings and select a suitable value of lambda.
- Makes predictions using the trained models.
- Calculates error scores to help us evaluate how well the models perform.
- Includes test programs and examples to demonstrate how the different parts work.

## 3. Week 5: Introduction to C++ Templates

In Week 5, we extended our project by introducing C++ templates. We wanted to make some of our classes reusable so that they could work with different numerical data types without having to write separate classes for each type.

With templates, we can use data types such as `short`, `int`, `float`, and `double` depending on the values we want to store and process.

We introduced the following template classes:

- **Matrix:** Stores numerical values in rows and columns and supports matrix operations.
- **NumericDataset:** Keeps the input feature matrix and target values together.
- **CsvDataProcessor:** Reads numerical data from a CSV file and stores it using the selected data type.
- **TypedLinearRegression:** Accepts numerical inputs of different types and uses the existing Linear Regression implementation.
- **TypedLassoRegression:** Accepts typed numerical inputs and uses the existing LASSO Regression implementation.

One important decision we made was to keep the actual model calculations in `double`. This allowed us to reuse the existing regression algorithms instead of creating separate versions for every data type.

However, converting values to `double` does not guarantee that every number will be represented exactly. We also included a check to reject decimal values when converting them to integer types, rather than silently losing the decimal part.

## 4. Requirements

To build and run our project, we need:

- A C++17 compiler, such as GCC, Clang, or MSVC.
- CMake version 3.16 or newer.
- No additional C++ libraries are required.

## 5. Sample Data

We included sample datasets to demonstrate how our program works.

The main sample CSV file is located at:

`data/input/sample.csv`

It contains 8 rows, with 3 input features in each row.

We also used another small dataset containing 12 rows for the Week 4 validation example.

Since these datasets are made up for practice, the results we obtain only demonstrate how our program works. They should not be taken as proof that the models will achieve the same accuracy when working with real-world data.

## 6. Building and Testing the Project

We used CMake to configure and build our project. To do this on Windows, we open PowerShell in the main project folder and run the following commands.

**Step 1: Configure the project**

```powershell
cmake -S . -B build
```

**Step 2: Build the project**

```powershell
cmake --build build
```

**Step 3: Run the tests**

```powershell
ctest --test-dir build --output-on-failure
```

Our project contains five CTest programs:

1. Week 2 LASSO test.
2. Week 3 LASSO test.
3. Week 4 validation test.
4. Linear Regression test.
5. Numeric Templates test.

We use these tests to check whether the different parts of our project are working as expected.

If all five tests pass, it means that the tested components have performed as expected.

### Installing the Libraries and Headers

We can also install the project libraries and public headers into an installation folder by running:

```powershell
cmake --install build --prefix install
```

## 7. Running the Examples

After building the project, we can run the example programs from the main project folder using:

**Week 5 demonstration**

```powershell
.\build\lasso_week5_demo.exe
```

**Week 4 demonstration**

```powershell
.\build\lasso_week4_demo.exe
```

The Week 5 example demonstrates how we load CSV data, work with different numerical data types, and use the typed Linear Regression and LASSO Regression models.

The Week 4 example demonstrates how we select a suitable lambda value and evaluate the model using test scores.

We also included other examples to demonstrate CSV loading, the Linear Regression baseline, cost calculation, soft-thresholding, and lambda comparison.

## 8. Project Structure

We organised our project into different folders to make the code easier to understand, manage and maintain.

| Folder        | What it contains                                                         |
| ------------- | ------------------------------------------------------------------------ |
| `include/`    | Public C++ header files and class declarations.                          |
| `src/`        | Source files containing the implementation of the project.               |
| `examples/`   | Example programs that demonstrate how our code works.                    |
| `tests/`      | Test programs used to check the different components.                    |
| `data/input/` | Sample CSV datasets used by our program.                                 |
| `docs/`       | Diagrams, illustrations and template design notes.                       |
| `reports/`    | Weekly reports, final reports, file assignments and presentation script. |

### LASSO Workflow

The following diagram shows the general process followed by our LASSO model, from loading the data to making predictions.



### Week 5 Template Class Diagram

We also included a UML class diagram to show how the different template classes in Week 5 relate to one another.



## 9. Reports and Presentation Materials

Throughout the project, we prepared reports to document our progress and explain the work completed in each week.

The following are the reports and supporting documents included in our project:

- [Week 1 report](reports/week-01-member-01.md)
- [Week 2 report](reports/week-02-member-05.md)
- [Week 3 report](reports/week-03-member-10.md)
- [Week 4 report](reports/week-04-member-10.md)
- [Week 5 final report](reports/week-05-member-10.md)
- [File assignments for the project](reports/week-05-file-ownership.md)

- [Template design notes and UML](docs/template-design.md)

.

## 10. Project Limitations

Although our project demonstrates several useful regression techniques and C++ programming concepts, it has some limitations:

- The sample datasets are small and made up for practice. They may not represent real-world data.
- Our CSV reader handles simple rows containing numerical values. It does not support quoted text fields.
- The typed model interfaces convert numerical values to `double` before performing the actual model calculations.
- Our project focuses on Linear Regression and LASSO Regression. It does not include Logistic Regression, Graph Neural Networks (GNNs), or Convolutional Neural Networks (CNNs).
- We were not provided with the textbook pages containing the Chapter 18 exercises. Therefore, we do not claim that those specific exercises were completed.

These limitations help us understand what our current program can do and what could be improved in future versions.

## 11. Use of AI Tools

During the development of this project, we used OpenAI Codex to assist us with some of the programming and documentation tasks.

It helped us review and simplify code, add template examples and tests, update the CMake configuration, create diagrams, and prepare report drafts.

We have included more information about its use in:

`reports/ai-use-declaration-member-10.md`

As Group 14, we worked together to develop this project and understand the concepts behind its implementation. Through this work, we gained practical experience in C++ programming, templates, Linear Regression and LASSO Regression. 