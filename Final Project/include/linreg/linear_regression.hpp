#pragma once

#include <cstddef>
#include <vector>

namespace linreg {

struct FitResult {
    double intercept{};
    double slope{};
    double mse{};
    double r_squared{};
    std::size_t iterations{};
};

struct DatasetSplit {
    std::vector<double> train_x;
    std::vector<double> train_y;
    std::vector<double> test_x;
    std::vector<double> test_y;
};

class LinearRegression {
public:
    // Fit y = intercept + slope*x using the closed-form least-squares solution.
    FitResult fit_closed_form(const std::vector<double>& x,
                              const std::vector<double>& y);

    // Fit y = intercept + slope*x using batch gradient descent.
    FitResult fit_gradient_descent(const std::vector<double>& x,
                                   const std::vector<double>& y,
                                   double learning_rate = 0.01,
                                   std::size_t iterations = 1000);

    // Fit using one observation at a time, shuffling observations each epoch.
    FitResult fit_stochastic_gradient_descent(const std::vector<double>& x,
                                              const std::vector<double>& y,
                                              double learning_rate = 0.001,
                                              std::size_t epochs = 1000,
                                              unsigned seed = 42);

    [[nodiscard]] double predict(double x) const;
    [[nodiscard]] std::vector<double> predict(const std::vector<double>& x) const;
    [[nodiscard]] double intercept() const noexcept { return intercept_; }
    [[nodiscard]] double slope() const noexcept { return slope_; }

private:
    double intercept_{0.0};
    double slope_{0.0};
    bool fitted_{false};
};

[[nodiscard]] double mean_squared_error(const std::vector<double>& actual,
                                         const std::vector<double>& predicted);
[[nodiscard]] double r_squared(const std::vector<double>& actual,
                               const std::vector<double>& predicted);
[[nodiscard]] double correlation_coefficient(const std::vector<double>& x,
                                             const std::vector<double>& y);
[[nodiscard]] double standard_error_of_estimate(const std::vector<double>& actual,
                                                const std::vector<double>& predicted,
                                                std::size_t number_of_parameters = 2);

// Split paired observations into training and testing subsets.
DatasetSplit train_test_split(const std::vector<double>& x,
                              const std::vector<double>& y,
                              double test_fraction = 0.2,
                              unsigned seed = 42,
                              bool shuffle = true);

} // namespace linreg
