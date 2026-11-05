//bringing in the group's LASSO declarations
#include "lasso/lasso_regression.hpp"

//bringing in the std:: into the program
#include <iostream>

int main() {//starts the program
    
    const lasso::Matrix x{{1, 2}, {2, 1}}; // creates a fixed feature table of rows(1,2) and (2,1)
    const lasso::Vector y{5, 4};// creates  fixed target values of each row

    //calling LASSO cost function and printing the result
    std::cout << "LASSO cost: " << lasso::lasso_cost(x, y, {1, 2}, 0.5) << "\n";
}

