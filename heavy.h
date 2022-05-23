// =========================================================
// File: heavy.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef HEAVY_H
#define HEAVY_H

#include "container.h"

class HeavyContainer : public Container
{
public:
  HeavyContainer(int, int);
  HeavyContainer(int, int, ContainerType);
  HeavyContainer(const HeavyContainer &);

  double getConsumption() const;
};

HeavyContainer::HeavyContainer(int id, int weight) : Container(id, weight, HEAVY) {}

HeavyContainer::HeavyContainer(int id, int weight, ContainerType HEAVY) : Container(id, weight, HEAVY) {}

HeavyContainer::HeavyContainer(const HeavyContainer &container) : Container(container) {}

double HeavyContainer::getConsumption() const
{
  return (weight * 3);
}

#endif
