# Week 3 Progress Report member 02 Karungi Mary Gorret

**General week 3 report** (integration, tests, and class-layout documentation)  
**Record note:** Reconstructed on 2026-10-28 from the supplied Week 3 and Week 4 packages and the integrated source. It describes the current implementation rather than claiming historical dates or commits.

## Completed

- Integrated reproducible data splitting, input validation, feature scaling, row predictions, feature selection, and regression metrics.
- Kept the regression baseline's internal model values private and exposed operations through public member functions.
- Added class-layout JPGs and an editable Mermaid diagram that match the current headers.
- Reviewed the current implementation for inheritance and polymorphism and documented their absence accurately.

## In Progress

- Improving the Week 4 model-selection workflow and ensuring test rows are not used during scaling or lambda selection.
- Consolidating the reports and CMake targets for a clean final build.

## Challenges/Blockers

- The numerical workflow does not need a parent/child class hierarchy. Adding inheritance just to show an inheritance arrow would not describe the program honestly.
- The class-layout JPGs are digital diagrams made from the code declarations. They are not photographs of hand-drawn paper diagrams.
- Member names and student numbers were not supplied, so this report uses the member identifier included in the project files.

## Week 3 object-oriented design

### Encapsulation

The class `linreg::LinearRegression` is the project's concrete class. It keeps `intercept_`, `slope_`, and `fitted_` private. Calling code fits the model with `fit_closed_form()`, `fit_gradient_descent()`, or `fit_stochastic_gradient_descent()`, makes predictions with `predict()`, and reads the fitted parameters through `intercept()` and `slope()`. The class checks that prediction follows a successful fit.

The code has no `protected` members. The data carriers, including `Dataset`, `TrainTestSplit`, `FittedScaler`, `LassoFit`, `RegressionMetrics`, and `CrossValidationResult`, are `struct`s, so their members are public by default.

### Inheritance

No project class derives from another project class. The diagrams therefore show no inheritance arrow and no protected member section.

### Polymorphism

The project has no virtual functions, overrides, or calls through a base-class pointer or reference. `predict()` is a regular member function; it is not a polymorphic override.

### Layout diagrams

- [`week3_class_layouts.jpg`](../docs/figures/week3_class_layouts.jpg) shows the class and data structures, fields, functions, and access markers.
- [`week3_oop_relationships.jpg`](../docs/figures/week3_oop_relationships.jpg) highlights the containment relationship and notes that inheritance and polymorphism are not implemented.
- [`class-diagram.mmd`](../docs/diagrams/class-diagram.mmd) is the editable Mermaid source.

The JPGs are digital diagrams based on the implemented declarations, not photographs of handwritten sheets. If the course requires a literal paper drawing, a group member should print or copy the layouts by hand.

![LinearRegression class layout](../docs/figures/week3_class_layouts.jpg)

![Week 3 data structures and relationships](../docs/figures/week3_oop_relationships.jpg)

## Next Week

- Use deterministic k-fold cross-validation to choose lambda on training data.
- Fit scaling values on training rows only and evaluate once on held-out test rows.
- Run the complete CMake build, CTest suite, and final demo.

## AI Use

- **Tool:** OpenAI Codex.
- **Purpose:** Inspect the supplied code, improve beginner-level readability and validation.
- **Reason:** To support integration and documentation while keeping the class analysis tied to declarations in the project headers.
