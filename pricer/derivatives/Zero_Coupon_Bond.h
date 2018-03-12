#ifndef _ZERO_COUPON_BOND_H_INCLUDED_
#define _ZERO_COUPON_BOND_H_INCLUDED_

#include "Bond.h"

namespace derivatives
{
class Zero_Coupon_Bond :public derivatives::Bond
{
public:
    Zero_Coupon_Bond(double N, double t, double y):
        derivatives::Bond(N, t, t, y);
};
}

#endif
