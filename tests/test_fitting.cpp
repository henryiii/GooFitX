#include <catch.hpp>

#include <goofit/Registry.hpp>
#include <goofit/FitManager.hpp>
#include <goofit/Variable.hpp>
#include <goofit/PDFs/simple/Gauss.hpp>

#include <random>
#include <algorithm>
#include <iostream>

using namespace GooFit::experimental;

TEST_CASE("Check to see if a Gauss can be fit", "[Gauss]") {

    std::random_device r;
    std::default_random_engine generator{r()};
    std::normal_distribution<fptype> distribution{5.0,2.0};

    Registry x{100000};
    std::generate(x.begin(), x.end(), [&](){return distribution(generator);});

    Variable mu{"mu", 4.0, .01};
    Variable sigma{"sigma", 1.5, .01};
    
    Gauss gauss(x,mu,sigma);

    FitManager manager(gauss);
    manager.fit();

    CHECK(mu.get_value() == Approx(5.0).margin(0.01));
    CHECK(sigma.get_value() == Approx(2.0).margin(0.01));
}
