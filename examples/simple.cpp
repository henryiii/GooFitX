#include <goofit/Application.hpp>
#include <goofit/Registry.hpp>
#include <goofit/FitManager.hpp>
#include <goofit/Variable.hpp>
#include <goofit/PDFs/simple/Gauss.hpp>

#include <random>
#include <algorithm>
#include <iostream>

using namespace GooFit::experimental;

int main() {

    Application app;

    std::random_device r;
    std::default_random_engine generator{r()};
    std::normal_distribution<fptype> distribution{5.0,2.0};

    Registry x{100000};
    std::generate(x.begin(), x.end(), [&](){return distribution(generator);});

    Variable mu{"mu", 5.0};
    Variable sigma{"sigma", 2.0};
    
    Gauss gauss(x,mu,sigma);

    FitManager manager(gauss);
    std::cout << manager.calculate_nll() << std::endl;

    return 0;
}
