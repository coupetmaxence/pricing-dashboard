#ifndef _EUROPEAN_OPTION_H_INCLUDED_
#define _EUROPEAN_OPTION_H_INCLUDED_

#include <algorithm>

#include "Derivative.h"
#include "Option.h"
#include "Non_Path_Dependant.h"


namespace derivatives
{
class European_Option : public derivatives::Option,
                        public derivatives::Non_Path_Dependant
{

public:
    // Constructor
    European_Option(OptionType p_type, double p_s0, double p_k, double p_t,
        double p_sigma, double p_r, double p_q=0, double p_c=0):
        derivatives::Option(p_type, p_s0, p_k, p_t, p_sigma, p_r, p_q, p_c)
    {};
    // Payoff function
    double payoff(double price) override
    {
        if(type == Call)
            return std::max(0.0, price-k);
        else
            return std::max(0.0, k-price);
    };

};

}
#endif
