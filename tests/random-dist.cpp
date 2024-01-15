#define BOOST_TEST_MODULE random
#include <boost/test/included/unit_test.hpp>

#include <boost/math/distributions/chi_squared.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <cmath>
#include <map>

BOOST_AUTO_TEST_CASE(PearsonsChiSquared)
{
    auto gen = boost::random::mt19937_64(boost::random::random_device()());

    constexpr int n_cat = 2;
    const auto dist = boost::random::uniform_int_distribution<int>(0, n_cat - 1);
    constexpr int N = 1'000'000;
    constexpr double theoretical_p = 1.0 / n_cat;

    std::map<int, int> obesrvations;
    for(int i = 0; i < N; i++) {
        obesrvations[dist(gen)]++;
    }

    double statistics = 0;
    for(int i = 0; i < n_cat; i++) {
        const double E_i = N * theoretical_p;
        statistics += std::pow(obesrvations[i] - E_i, 2) / E_i;
        std::clog << std::string(
            static_cast<std::size_t>(
                static_cast<double>(obesrvations.at(i)) / N * 100.0),
            '*') << std::endl;
    }

    constexpr int deg_freedom = n_cat - 1;
    const auto chi2 = boost::math::chi_squared_distribution(deg_freedom);
    constexpr double p_value = 0.05;
    const double critical_value
        = boost::math::quantile(boost::math::complement(chi2, p_value));
    std::clog << "statistics = " << statistics << std::endl;
    std::clog << "critical_value = " << critical_value << std::endl;
    BOOST_TEST(statistics < critical_value);
}
