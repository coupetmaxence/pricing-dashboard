#ifndef _OPTION_H_INCLUDED_
#define _OPTION_H_INCLUDED_

#include "Derivative.h"

namespace derivatives
{

// enumerate type for the type of the option
enum OptionType {Call, Put};

class Option : public derivatives::Derivative
{
protected:
    // Option type
    OptionType type;
    // Strike price
    double k;

public:
    // Constructor
    Option(OptionType p_type, double p_s0, double p_k, double p_t,
        double p_sigma, double p_r, double p_q=0, double p_c=0):
        derivatives::Derivative(p_s0, p_t, p_sigma, p_r, p_q, p_c),
        type(p_type), k(p_k)
    {};
    // Getters
    OptionType get_type(){return type;};
    double get_k(){return k;};

};

}
#endif
