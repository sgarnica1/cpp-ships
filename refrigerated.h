// =========================================================
// File: refrigerated.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef REFRIGERATED_H
#define REFRIGERATED_H

#include "heavy.h"

class RefrigeratedContainer : public HeavyContainer {
public:
  RefrigeratedContainer(int, int);
  RefrigeratedContainer(const RefrigeratedContainer&);

  double getConsumption() const;
};

RefrigeratedContainer::RefrigeratedContainer(int id, int weight) : HeavyContainer(id, weight, REFRIGERATED) {}

RefrigeratedContainer::RefrigeratedContainer(const RefrigeratedContainer &container) : HeavyContainer(container) {}

double RefrigeratedContainer::getConsumption() const
{
  return (weight * 5);
}

#endif
