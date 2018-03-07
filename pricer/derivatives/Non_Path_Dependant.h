#ifndef _NON_PATH_DEPENDANT_H_INCLUDED_
#define _NON_PATH_DEPENDANT_H_INCLUDED_

namespace derivatives
{
class Non_Path_Dependant
{
public:
    virtual double payoff(double price)=0;
};
}

#endif
