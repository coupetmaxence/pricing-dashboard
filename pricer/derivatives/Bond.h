#ifndef _BOND_H_INCLUDED_
#define _BOND_H_INCLUDED_

#include <math.h>

namespace derivatives
{
class Bond
{
protected:
    double N, t, dt, y, c;
public:
    Bond(double p_N, double p_t, double p_dt, double p_y, double p_c=0):N(p_N), 
        t(p_t), dt(p_dt), y(p_y), c(p_c){};
    double get_N(){return N;};
    double get_y(){return y;};
    double get_t(){return t;};
    double get_c(){return c;};
    double price()
    {
        double somme = 0;
        for(int i = 1; i < t/dt; i++)
        {
            somme += c*exp(-y*i*dt);
        }
        somme += N*exp(-y*t);
        return somme;
    };
};
}

#endif
