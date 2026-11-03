#include "lasso/week4.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <stdexcept>

namespace lasso {
namespace {
Dataset subset(const Dataset& data, const std::vector<std::size_t>& ids) {
    Dataset out;
    for (auto i : ids) { out.features.push_back(data.features.at(i)); out.target.push_back(data.target.at(i)); }
    return out;
}
double rmse(const Vector& a, const Vector& b) {
    if (a.empty() || a.size()!=b.size()) throw std::invalid_argument("RMSE vectors must match and be non-empty");
    double sum=0.0;
    for (std::size_t i=0;i<a.size();++i) { const double e=a[i]-b[i]; sum+=e*e; }
    return std::sqrt(sum/a.size());
}
}
CrossValidationResult cross_validate_lambda(const Dataset& data, double lambda, int folds, unsigned seed) {
    if (data.features.size()!=data.target.size() || data.target.size()<2)
        throw std::invalid_argument("dataset must have matching feature and target rows");
    if (folds<2 || static_cast<std::size_t>(folds)>data.target.size())
        throw std::invalid_argument("folds must be between 2 and the number of rows");
    if (lambda<0.0 || !std::isfinite(lambda)) throw std::invalid_argument("lambda must be finite and non-negative");
    const std::size_t n=data.target.size();
    std::vector<std::size_t> order(n); std::iota(order.begin(),order.end(),0);
    std::mt19937 generator(seed); std::shuffle(order.begin(),order.end(),generator);
    std::vector<double> scores; scores.reserve(folds);
    for (int fold=0;fold<folds;++fold) {
        std::vector<std::size_t> train_ids, valid_ids;
        for (std::size_t pos=0;pos<n;++pos) {
            if (static_cast<int>(pos % static_cast<std::size_t>(folds))==fold) valid_ids.push_back(order[pos]);
            else train_ids.push_back(order[pos]);
        }
        Dataset train=subset(data,train_ids), valid=subset(data,valid_ids);
        auto scaler=fit_scaler(train.features);
        Matrix xtrain=scaler.transform(train.features), xvalid=scaler.transform(valid.features);
        auto fit=coordinate_descent(xtrain,train.target,lambda,1000,1e-7);
        auto pred=predict_rows(xvalid,fit.coefficients,fit.intercept);
        scores.push_back(rmse(valid.target,pred));
    }
    const double mean=std::accumulate(scores.begin(),scores.end(),0.0)/scores.size();
    return {lambda,mean,scores};
}
CrossValidationResult select_lambda_by_cross_validation(const Dataset& data, const Vector& candidates, int folds, unsigned seed) {
    if (candidates.empty()) throw std::invalid_argument("provide at least one lambda candidate");
    CrossValidationResult best{0.0,INFINITY,{}};
    for (double lambda:candidates) {
        auto result=cross_validate_lambda(data,lambda,folds,seed);
        if (result.mean_validation_rmse<best.mean_validation_rmse) best=result;
    }
    return best;
}
} // namespace lasso
