// =========================================================
// File: light.h
// Author: Sergio Garnica González - A01704025
// Date:
// Description:
// =========================================================
#ifndef LIGHT_H
#define LIGHT_H

#include "container.h"

class LightContainer : public Container
{
public:
  LightContainer(int, int);
  LightContainer(const LightContainer &);

  double getConsumption() const;
};

LightContainer::LightContainer(int id, int weight) : Container(id, weight, LIGHT) {}

LightContainer::LightContainer(const LightContainer &container) : Container(container) {}

double LightContainer::getConsumption() const
{
  return (weight * 2.5);
}
#endif
