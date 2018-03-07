#ifndef _PATH_DEPENDANT_H_INCLUDED_
#define _PATH_DEPENDANT_H_INCLUDED_

#include <vector>

namespace derivatives
{
class Path_Dependant
{
public:
    virtual double payoff(std::vector<double> prices)=0;
};
}

#endif
