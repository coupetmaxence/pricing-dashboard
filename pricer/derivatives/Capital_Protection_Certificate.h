#ifndef _CAPITAL_PROTECTION_CERTIFICATE_H_INCLUDED_
#define _CAPITAL_PROTECTION_CERTIFICATE_H_INCLUDED_

#include <string>
#include "Derivative.h"
#include "Zero_Coupon_Bond.h"
#include "European_Option.h"

namespace derivatives
{
class Capital_Protection_Certificate : public derivatives::Derivative
{
protected:
    double N, floor, cap, participation;
public:
    Capital_Protection_Certificate(double p_s0, double p_t, double p_sigma,
            double p_r, double p_q, double p_N, std::string solve_for,
            double arg1, double arg2, double arg3)
};
}

#endif 
