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

    Registry x{1000000};
    std::generate(x.begin(), x.end(), [&](){return distribution(generator);});

    Variable mu{"mu", 4.0, .01};
    Variable sigma{"sigma", 1.5, .01};
    
    Gauss gauss(x,mu,sigma);

    FitManager manager(gauss);
    manager.fit();
    
    std::cout << mu << " (was 4, should be 5)" << std::endl;
    std::cout << sigma << " (was 1.5, should be 2)" << std::endl;
    
    return 0;
}
