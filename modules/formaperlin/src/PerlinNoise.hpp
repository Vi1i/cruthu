#ifndef FORMAPERLIN_PERLINNOISE_HPP
#define FORMAPERLIN_PERLINNOISE_HPP

#include <vector>

namespace utils {
class PerlinNoise {
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);

    double Noise(double x, double y, double z);

private:
    std::vector<int> mPermutations;

    double Fade(double t);
    double Lerp(double t, double a, double b);
    double Grad(int hash, double x, double y, double z);
};
}
#endif
