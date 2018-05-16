#include <goofit/Application.hpp>
#include <goofit/Registry.hpp>
#include <goofit/FitManager.hpp>
#include <goofit/Variable.hpp>
#include <goofit/PDFs/simple/Gauss.hpp>

#include <random>
#include <algorithm>
#include <iostream>

using namespace GooFit::experimental;

int main(int argc, char** argv) {
    Application app("Fitting");
    CLI11_PARSE(app, argc, argv);

    std::random_device r;
    std::default_random_engine generator{r()};
    std::normal_distribution<fptype> distribution{5.0,2.0};

    //std::vector<fptype> xv;
    //xv.resize(1000000);
    //std::generate(xv.begin(), xv.end(), [&](){return distribution(generator);});
    //Registry x{xv};
    
    Registry x{1000000};
    vex::vector<fptype>& data = x.data();
    
    vex::RandomNormal<fptype, vex::random::threefry> rnd;
    data = rnd(vex::element_index(0,x.size()), 42) * 2 + 5 ;

    Variable mu{"mu", 4.0, .01};
    Variable sigma{"sigma", 1.5, .01};
    
    Gauss gauss(x,mu,sigma);

    FitManager manager(gauss);
    manager.fit();
    
    std::cout << mu << " (was 4, should be 5)" << std::endl;
    std::cout << sigma << " (was 1.5, should be 2)" << std::endl;
    
    return 0;
}
