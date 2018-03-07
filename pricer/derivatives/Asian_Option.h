#ifndef _ASIAN_OPTION_H_INCLUDED_
#define _ASIAN_OPTION_H_INCLUDED_

#include <vector>
#include <numeric>

#include "Option.h"
#include "Path_Dependant.h"

namespace derivatives
{
class Asian_Option : public Option,
                        public Path_Dependant
{
public:
    // Constructor
    Asian_Option(OptionType p_type, double p_s0, double p_k, double p_t,
        double p_sigma, double p_r, double p_q=0, double p_c=0):
        derivatives::Option(p_type, p_s0, p_k, p_t, p_sigma, p_r, p_q, p_c)
    {};
    // Payoff function
    double payoff(std::vector<double> prices) override
    {
        // We define here the arithmetical mean payoff
        double price_mean = std::accumulate(prices.begin()
                                    , prices.end(), 0.0)/prices.size();

        if(type == Call)
            return std::max(0.0, price_mean-k);
        else
            return std::max(0.0, k-price_mean);
    };
};
}

#endif
