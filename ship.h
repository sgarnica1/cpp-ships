// =========================================================
// File: ship.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef SHIP_H
#define SHIP_H

#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include "container.h"
#include "light.h"
#include "heavy.h"
#include "refrigerated.h"
#include "liquid.h"
#include "simpleship.h"
#include "port.h"

class Ship : public SimpleShip
{
private:
      int currentWeight, totalWeight;
      int currentNumberOfAllContainers, maxNumberOfAllContainers;
      int currentNumberOfHeavyContainers, maxNumberOfHeavyContainers;
      int currentNumberOfRefrigeratedContainers, maxNumberOfRefrigeratedContainers;
      int currentNumberOfLiquidContainers, maxNumberOfLiquidContainers;
      double fuel, fuelConsumptionPerKM;
      Port *currentPort;
      std::list<Container *> containers;

      bool contains(Container *);
      void remove(Container *);

public:
      Ship(int, Port *, int, int, int, int, int, double);
      Ship(const Ship &);

      int getId() const;
      int getCurrentWeight() const;
      int getTotalWeight() const;
      int getCurrentNumberOfAllContainers() const;
      int getMaxNumberOfAllContainers() const;
      int getCurrentNumberOfHeavyContainers() const;
      int getMaxNumberOfHeavyContainers() const;
      int getCurrentNumberOfRefrigeratedContainers() const;
      int getMaxNumberOfRefrigeratedContainers() const;
      int getCurrentNumberOfLiquidContainers() const;
      int getMaxNumberOfLiquidContainers() const;
      double getFuel() const;
      double getFuelConsumptionPerKM() const;
      Port *getCurrentPort() const;
      std::list<Container *> getCurrentContainers() const;

      bool operator<(const Ship *);
      bool operator<(const Ship &);

      bool sailTo(Port *);
      void reFuel(double);
      bool load(Container *);
      bool unLoad(Container *);

      std::string toString() const;
};

Ship::Ship(int id, Port *currentPort, int totalWeight, int maxNumberOfAllContainers, int maxNumberOfHeavyContainers, int maxNumberOfRefrigeratedContainers, int maxNumberOfLiquidContainers, double fuelConsumptionPerKM) : SimpleShip(id), currentPort(currentPort), totalWeight(totalWeight), maxNumberOfAllContainers(maxNumberOfAllContainers), maxNumberOfHeavyContainers(maxNumberOfHeavyContainers), maxNumberOfRefrigeratedContainers(maxNumberOfRefrigeratedContainers), maxNumberOfLiquidContainers(maxNumberOfLiquidContainers), fuelConsumptionPerKM(fuelConsumptionPerKM)
{
      this->currentWeight = 0;
      this->currentNumberOfAllContainers = 0;
      this->currentNumberOfHeavyContainers = 0;
      this->currentNumberOfLiquidContainers = 0;
      this->currentNumberOfRefrigeratedContainers = 0;
      this->fuel = 0;
}

Ship::Ship(const Ship &ship) : SimpleShip(ship), currentPort(ship.currentPort), totalWeight(ship.totalWeight), maxNumberOfAllContainers(ship.maxNumberOfAllContainers), maxNumberOfHeavyContainers(ship.maxNumberOfHeavyContainers), maxNumberOfRefrigeratedContainers(ship.maxNumberOfRefrigeratedContainers), maxNumberOfLiquidContainers(ship.maxNumberOfLiquidContainers), fuelConsumptionPerKM(ship.fuelConsumptionPerKM)
{
      this->currentWeight = 0;
      this->currentNumberOfAllContainers = 0;
      this->currentNumberOfHeavyContainers = 0;
      this->currentNumberOfLiquidContainers = 0;
      this->currentNumberOfRefrigeratedContainers = 0;
      this->fuel = 0;
}

int Ship::getId() const
{
      return this->id;
}

int Ship::getCurrentWeight() const
{
      return this->currentWeight;
}

int Ship::getTotalWeight() const
{
      return this->totalWeight;
}

int Ship::getCurrentNumberOfAllContainers() const
{
      return this->currentNumberOfAllContainers;
}

int Ship::getMaxNumberOfAllContainers() const
{
      return this->maxNumberOfAllContainers;
}

int Ship::getCurrentNumberOfHeavyContainers() const
{
      return this->currentNumberOfHeavyContainers;
}

int Ship::getMaxNumberOfHeavyContainers() const
{
      return this->maxNumberOfHeavyContainers;
}

int Ship::getCurrentNumberOfRefrigeratedContainers() const
{
      return this->currentNumberOfRefrigeratedContainers;
}

int Ship::getMaxNumberOfRefrigeratedContainers() const
{
      return this->maxNumberOfRefrigeratedContainers;
}

int Ship::getCurrentNumberOfLiquidContainers() const
{
      return this->currentNumberOfLiquidContainers;
}

int Ship::getMaxNumberOfLiquidContainers() const
{
      return this->maxNumberOfLiquidContainers;
}

double Ship::getFuel() const
{
      return this->fuel;
}

double Ship::getFuelConsumptionPerKM() const
{
      return this->fuelConsumptionPerKM;
}

Port *Ship::getCurrentPort() const
{
      return this->currentPort;
}

bool Ship::operator<(const Ship *ship)
{
      return this->id < ship->getId() ? true : false;
}

bool Ship::operator<(const Ship &ship)
{
      return this->id < ship.getId() ? true : false;
}
std::list<Container *> Ship::getCurrentContainers() const
{
      return containers;
}

bool Ship::sailTo(Port *port)
{
      double containerFuelConsumption = 0;
      double totalFuelRequired = 0;
      double distance = this->currentPort->getDistance(port);

      for (Container *container : containers)
      {
            containerFuelConsumption += (*container).getConsumption();
      }

      totalFuelRequired = (fuelConsumptionPerKM * distance) + containerFuelConsumption;

      if (totalFuelRequired < fuel)
      {
            fuel -= totalFuelRequired;
            this->currentPort->outgoingShip(this);
            port->incomingShip(this);
            this->currentPort = port;
            return true;
      }

      return false;
}

void Ship::reFuel(double fuelQuantity)
{
      if (fuelQuantity > 0)
      {
            this->fuel = this->fuel + fuelQuantity;
      }
}

bool Ship::load(Container *c)
{
      bool spaceAvailabe = currentNumberOfAllContainers < maxNumberOfAllContainers ? true : false;
      bool weightAvailable = currentWeight + c->getWeight() < totalWeight ? true : false;
      bool containerExists = false;
      bool containerInCurrentPort = false;

      for (Container *container : currentPort->getContainers())
      {
            if (container->getId() == c->getId())
            {
                  containerInCurrentPort = true;
            }
      }

      if (!containerInCurrentPort)
            return false;

      for (Container *container : containers)
      {
            if (container->getId() == c->getId())
            {
                  containerExists = true;
            }
      }

      if (containerExists || !spaceAvailabe || !weightAvailable)
      {
            return false;
      }

      if (c->getType() == HEAVY && currentNumberOfHeavyContainers + 1 > maxNumberOfHeavyContainers)
      {
            return false;
      }

      if (c->getType() == REFRIGERATED && currentNumberOfRefrigeratedContainers + 1 > maxNumberOfRefrigeratedContainers)
      {
            return false;
      }

      if (c->getType() == LIQUID && currentNumberOfLiquidContainers + 1 > maxNumberOfLiquidContainers)
      {
            return false;
      }

      currentPort->remove(c);
      containers.insert(containers.end(), c);
      currentNumberOfAllContainers += 1;
      currentWeight += c->getWeight();

      if (c->getType() == HEAVY)
      {
            currentNumberOfHeavyContainers += 1;
      }

      if (c->getType() == LIQUID)
      {
            currentNumberOfLiquidContainers += 1;
      }

      if (c->getType() == REFRIGERATED)
      {
            currentNumberOfRefrigeratedContainers += 1;
      }

      // if (c->getType() == LIGHT)
      // {
      //   return false;
      // }

      return true;
}

bool Ship::unLoad(Container *c)
{
      // if (c->getType() == LIGHT)
      // {
      //   return false;
      // }

      for (const Container *container : containers)
      {
            if (container->getId() == c->getId())
            {
                  containers.remove(c);
                  currentPort->add(c);
                  currentNumberOfAllContainers -= 1;

                  if (c->getType() == HEAVY)
                  {
                        currentNumberOfHeavyContainers -= 1;
                  }

                  if (c->getType() == REFRIGERATED)
                  {
                        currentNumberOfRefrigeratedContainers -= 1;
                  }

                  if (c->getType() == LIQUID)
                  {
                        currentNumberOfLiquidContainers -= 1;
                  }

                  this->currentWeight -= c->getWeight();

                  return true;
            }
      }

      return false;
}

bool Ship::contains(Container *container)
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

void Ship::remove(Container *container)
{
      containers.remove(container);
}

std::string Ship::toString() const
{
      std::string lightContainersIds = "";
      std::string heavyContainersIds = "";
      std::string refrigeratedContainersIds = "";
      std::string liquidContainersIds = "";

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

      std::stringstream aux;

      aux << "Ship " << this->id << ": " << std::fixed << std::setprecision(2) << this->fuel
          << "\n";

      if (lightContainersIds != "" && heavyContainersIds == "" && refrigeratedContainersIds == "" && liquidContainersIds == "")
      {
            aux << "\t\t"
                << "Light Containers: " << lightContainersIds << "\n";
      }
      else if (lightContainersIds != "" || heavyContainersIds != "" || refrigeratedContainersIds != "" || liquidContainersIds != "")
      {
            aux << "\t\t"
                << "Light Containers: " << lightContainersIds << "\n"
                << "\t\t"
                << "Heavy Containers: " << heavyContainersIds << "\n"
                << "\t\t"
                << "Refrigerated Containers: " << refrigeratedContainersIds << "\n"
                << "\t\t"
                << "Liquid Containers: " << liquidContainersIds
                << "\n";
      }

      return aux.str();
}

#endif
