#include <iostream>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

int main() {
  boost::random::random_device rd;
  boost::random::mt19937_64 gen(rd());
  boost::random::uniform_int_distribution<int> dist(1, 100);
  for (int i = 0; i < 10; i++) {
    std::cout << dist(gen) << std::endl;
  }
}
