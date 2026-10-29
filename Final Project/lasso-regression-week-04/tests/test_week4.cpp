#include "lasso/week4.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
int main() {
    const lasso::Dataset d{
        {{1,2},{2,1},{3,4},{4,3},{5,6},{6,5},{7,8},{8,7}},
        {2.1,2.8,4.2,4.8,6.1,6.9,8.2,8.8}
    };
    auto a=lasso::cross_validate_lambda(d,0.01,4,42);
    auto b=lasso::cross_validate_lambda(d,0.01,4,42);
    assert(a.fold_rmse.size()==4);
    assert(std::isfinite(a.mean_validation_rmse));
    assert(std::abs(a.mean_validation_rmse-b.mean_validation_rmse)<1e-12);
    auto best=lasso::select_lambda_by_cross_validation(d,{0.001,0.01,0.1},4,42);
    assert(best.lambda>=0.0 && std::isfinite(best.mean_validation_rmse));
    bool threw=false;
    try { (void)lasso::cross_validate_lambda(d,0.1,1,42); } catch (...) { threw=true; }
    assert(threw);
    std::cout << "Week 4 tests passed.\n";
}
