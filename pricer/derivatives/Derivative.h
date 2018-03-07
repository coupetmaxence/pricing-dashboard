#ifndef _DERIVATIVE_H_INCLUDED_
#define _DERIVATIVE_H_INCLUDED_

namespace derivatives
{
class Derivative
{
protected:
    // Underlying asset price
    double s0;
    // Maturity (in years)
    double t;
    // Volatility
    double sigma;
    // Risk-free interest rate (continuously compounded)
    double r;
    // Dividend rate (continuously compounded)
    double q;
    // Cost of carry of the underlying (continuously compounded)
    double c;


public:
    // Constructor
    Derivative(double p_s0, double p_t, double p_sigma, double p_r,
        double p_q=0, double p_c=0) : s0(p_s0), t(p_t), sigma(p_sigma),
        r(p_r), q(p_q), c(p_c)
        {

        };
    double get_s0(){return s0;};
    double get_t(){return t;};
    double get_sigma(){return sigma;};
    double get_r(){return r;};
    double get_q(){return q;};
    double get_c(){return c;};
    virtual ~Derivative() = default;
};

}

#endif
