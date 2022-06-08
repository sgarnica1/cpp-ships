// =========================================================
// File: port.h
// Author: Sergio Garnica González
// Date:
// Description:
// =========================================================
#ifndef PORT_H
#define PORT_H

#include <list>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include "container.h"
#include "simpleship.h"

class Port
{
private:
  int id;
  double x, y;
  std::list<Container *> containers;
  std::list<SimpleShip *> history;
  std::list<SimpleShip *> current;

public:
  Port(int, double, double);
  Port(const Port &);

  int getId() const;
  double getX() const;
  double getY() const;
  std::list<Container *> getContainers() const;
  std::list<SimpleShip *> getHistory() const;
  std::list<SimpleShip *> getCurrent() const;

  double getDistance(Port *) const;
  void incomingShip(SimpleShip *);
  void outgoingShip(SimpleShip *);

  bool contains(Container *);
  void add(Container *);
  void remove(Container *);

  std::string toString() const;
};

Port::Port(int id, double x, double y)
{
  this->id = id;
  this->x = x;
  this->y = y;
}

Port::Port(const Port &port)
{
  this->id = port.id;
  this->x = port.x;
  this->y = port.y;
}

int Port::getId() const
{
  return this->id;
}

double Port::getX() const
{
  return this->x;
}

double Port::getY() const
{
  return this->y;
}

std::list<Container *> Port::getContainers() const
{
  return this->containers;
}

std::list<SimpleShip *> Port::getHistory() const
{
  return this->history;
}

std::list<SimpleShip *> Port::getCurrent() const
{
  return this->current;
}

double Port::getDistance(Port *port) const
{
  double xf, yf, d;
  xf = this->x - port->x;
  yf = this->y - port->y;
  d = pow(pow(xf, 2) + pow(yf, 2), 0.5);

  return d;
}

void Port::incomingShip(SimpleShip *ship)
{
  std::list<SimpleShip *>::iterator itr;

  // Añadir a la historia
  bool inHistory = false;

  for (itr = history.begin(); itr != history.end(); itr++)
  {
    if (*itr == ship)
    {
      inHistory = true;
      break;
    }
  }

  if (!inHistory)
  {
    history.insert(history.begin(), ship);
  }

  // Añadir a la lista actual
  bool exists = false;

  for (itr = current.begin(); itr != current.end(); itr++)
  {
    if (*itr == ship)
    {
      exists = true;
      break;
    }
  }

  if (!exists)
  {
    current.insert(current.begin(), ship);
  }
}

void Port::outgoingShip(SimpleShip *ship)
{
  std::list<SimpleShip *>::iterator itr;
  bool exists = false;

  for (itr = current.begin(); itr != current.end(); itr++)
  {
    if (*itr == ship)
    {
      exists = true;
      current.remove(ship);
      break;
    }
  }
}

bool Port::contains(Container *container)
{
  std::list<Container *>::iterator itr;
  for (itr = containers.begin(); itr != containers.end(); itr++)
  {
    if (*itr == container)
    {
      return true;
    }
  }

  return false;
}

void Port::add(Container *container)
{
  containers.insert(containers.end(), container);
}

void Port::remove(Container *container)
{
  containers.remove(container);
}

std::string Port::toString() const
{
  std::string lightContainersIds = 0;
  std::string heavyContainersIds = 0;
  std::string refrigeratedContainersIds = 0;
  std::string liquidContainersIds = 0;

  for (const Container *container : containers)
  {
    if ((*container).getType() == HEAVY)
    {
      heavyContainersIds += std::to_string((*container).getId());
      heavyContainersIds += " ";
    }

    if ((*container).getType() == LIGHT)
    {
      lightContainersIds += std::to_string((*container).getId());
      lightContainersIds += " ";
    }

    if ((*container).getType() == REFRIGERATED)
    {
      refrigeratedContainersIds += std::to_string((*container).getId());
      refrigeratedContainersIds += " ";
    }

    if ((*container).getType() == LIQUID)
    {
      liquidContainersIds += std::to_string((*container).getId());
      liquidContainersIds += " ";
    }
  }

  for (const SimpleShip *ship : current)
  {
    std::string lightContainersIds = 0;
    std::string heavyContainersIds = 0;
    std::string refrigeratedContainersIds = 0;
    std::string liquidContainersIds = 0;

    std::list<Container *> shipContainers;

    // shipContainers = (*ship).getCurrentContainers();

    // std::stringstream aux;
    // aux <<
  }

  std::stringstream aux;
  aux << "Port " << this->id << ": (" << x << ", " << y << ")"
      << "  "
      << "Light Containers: " << lightContainersIds << "\n"
      << "  "
      << "Heavy Containers: " << heavyContainersIds << "\n"
      << "  "
      << "Refrigerated Containers: " << refrigeratedContainersIds << "\n"
      << "  "
      << "Liquid Containers: " << liquidContainersIds << "\n";

  return aux.str();
}

#endif
