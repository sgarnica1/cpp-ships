// =========================================================
// File: liquid.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef LIQUID_H
#define LIQUID_H

#include "heavy.h"

class LiquidContainer : public HeavyContainer {
public:
  LiquidContainer(int, int);
  LiquidContainer(const LiquidContainer&);

  double getConsumption() const;
};

LiquidContainer::LiquidContainer(int id, int weight) : HeavyContainer(id, weight, LIQUID) {}

LiquidContainer::LiquidContainer(const LiquidContainer &container) : HeavyContainer(container) {}

double LiquidContainer::getConsumption() const
{
  return (weight * 4);
}

#endif
