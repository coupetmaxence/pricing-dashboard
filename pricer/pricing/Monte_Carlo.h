#ifndef _MONTECARLO_H_INCLUDED_
#define _MONTECARLO_H_INCLUDED_

# include "../derivatives/Derivative.h"

namespace pricers
{
class Monte_Carlo
{
public:
    static double price(derivatives::Derivative* derivative, int nbr_simulations,
        int nbr_steps);
};

}

#endif
