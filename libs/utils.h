//
// Created by justnik on 14.12.2020.
//

#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <numeric>

namespace statistic {
    template<class It>
    double min(It first, It last) {
        return std::accumulate(first, last, std::numeric_limits<double>::max(), std::min<double>);
    }

    template<class It>
    double max(It first, It last) {
        return std::accumulate(first, last, std::numeric_limits<double>::min(), std::max<double>);
    }

    template<class It>
    double sum(It first, It last) {
        return std::accumulate(first, last, 0.0);
    }

    template<class It>
    double mean(It first, It last) {
        return static_cast<double>(sum(first, last)) / (last - first);
    }

    template<class It>
    double variance(It first, It last){
        auto sqr = [] (double res, double val){
            return res += val*val;
        };
        auto meansqr = std::accumulate(first,last,0.0,sqr)/(last-first);
        auto meanval = mean(first, last);
        return meansqr - meanval*meanval;
    }
}
#endif //RANDOM_UTILS_H
