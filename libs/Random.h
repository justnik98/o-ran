//
// Created by justnik on 13.12.2020.
//

#ifndef RANDOM_RANDOM_H
#define RANDOM_RANDOM_H

#include <iostream>
#include "utils.h"

class Random {
private:
    uint32_t i = 0;
    /* Constants for Mersenne Twister */
    constexpr static uint32_t mask1 = 1 << 31;
    constexpr static uint32_t mask2 = mask1 - 1;
    constexpr static uint32_t p = 624;
    constexpr static uint32_t w = 32;
    constexpr static uint32_t r = 31;
    constexpr static uint32_t q = 397;
    constexpr static uint32_t a = 0x9908b0df;
    constexpr static uint32_t u = 11;
    constexpr static uint32_t s = 7;
    constexpr static uint32_t t = 15;
    constexpr static uint32_t l = 18;
    constexpr static uint32_t b = 0x9d2c5680;
    constexpr static uint32_t c = 0xefc60000;
    uint32_t X[p];

public:
    Random();

    explicit Random(uint32_t seed);

    virtual ~Random() = default;

    uint32_t rand();

    double rnd();

    double randGaussian(double mean = 0, double sigma = 1);

    double randExp(double mean);

    double randChi2(uint32_t k);

    double randLogistic(double mean, double sigma);

    double randCauchy(double x0, double gamma);

    double randStudentT(uint32_t k);
};


#endif //RANDOM_RANDOM_H
