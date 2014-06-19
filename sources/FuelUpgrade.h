/*
 * FuelUpgrade.h
 *
 */

#ifndef FUELUPGRADE_H_
#define FUELUPGRADE_H_

#include "GameMapObject.h"

class FuelUpgrade : public GameMapObject
{
public:

    int getX();

    void setX(int _x);

private:
    int x;
};

#endif /* FUELUPGRADE_H_ */
