#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <list>
#include "heavy.h"
#include "light.h"
#include "liquid.h"
#include "refrigerated.h"
#include "port.h"
#include "ship.h"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream inputFile;
  ofstream outputFile;

  if (argc != 3)
  {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  if (!inputFile.is_open())
  {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  outputFile.open(argv[2]);

  // TO DO

  int nContainers, nShips, nPorts, nEvents, eventType;
  inputFile >> nContainers >> nShips >> nPorts >> nEvents;

  char type;
  int idContainerCurrent = 0, idPortCurrent = 0, idShipCurrent = 0;
  int idPort, idShip, idContainer;
  int weight, totalWeight, maxNumberOfAllContainers, maxNumberOfHeavyContainers, maxNumberOfRefrigeratedContainers, maxNumberOfLiquidContainers;
  double x, y, fuel, fuelConsumptionPerKM;
  std::list<Port *> ports;
  std::list<Ship *> ships;
  std::list<Container *> containers;
  Port *currentPort;
  Ship *currentShip;
  Container *currentContainer;

  for (int i = 0; i < nEvents; i++)
  {
    inputFile >> eventType;

    switch (eventType)
    {
    case 1:
    {

      inputFile >> idPort >> weight >> type;

      if (type == *"R")
      {
        currentContainer = new RefrigeratedContainer(idContainerCurrent, weight);
      }
      else if (type == *"L")
      {
        currentContainer = new LiquidContainer(idContainerCurrent, weight);
      }
      else if (type == *"B")
      {
        if (weight <= 3000)
        {
          currentContainer = new LightContainer(idContainerCurrent, weight);
        }
        else if (weight > 3000)
        {
          currentContainer = new HeavyContainer(idContainerCurrent, weight);
        }
      }

      for (Port *port : ports)
      {
        if (idPort == port->getId())
        {

          port->add(currentContainer);
        }
      }

      containers.insert(containers.end(), currentContainer);
      idContainerCurrent += 1;

      break;
    }
    case 2:
    {

      inputFile >> idPort >> totalWeight >> maxNumberOfAllContainers >> maxNumberOfHeavyContainers >> maxNumberOfRefrigeratedContainers >> maxNumberOfLiquidContainers >> fuelConsumptionPerKM;

      for (Port *port : ports)
      {
        if (idPort == port->getId())
        {
          currentPort = port;
        }
      }

      Ship *ship = new Ship(idShipCurrent, currentPort, totalWeight, maxNumberOfAllContainers, maxNumberOfHeavyContainers, maxNumberOfRefrigeratedContainers, maxNumberOfLiquidContainers, fuelConsumptionPerKM);

      currentPort->incomingShip(ship);
      ships.insert(ships.end(), ship);

      idShipCurrent += 1;

      break;
    }
    case 3:
    {
      inputFile >> x >> y;

      Port *port = new Port(idPortCurrent, x, y);
      ports.insert(ports.end(), port);
      idPortCurrent += 1;

      break;
    }
    case 4:
    {

      inputFile >> idShip >> idContainer;

      for (Ship *s : ships)
      {
        if (s->getId() == idShip)
        {
          currentShip = s;
        }
      }

      for (Container *c : containers)
      {
        if (c->getId() == idContainer)
        {
          currentShip->load(c);
        }
      }

      break;
    }
    case 5:
    {

      inputFile >> idShip >> idContainer;

      std::list<Ship *>::iterator itr;
      for (itr = ships.begin(); itr != ships.end(); itr++)
      {
        if (idShip == (*itr)->getId())
        {
          currentShip = *itr;
        }
      }

      for (Container *container : containers)
      {
        if (container->getId() == idContainer)
        {
          currentShip->unLoad(container);
        }
      }
      break;
    }
    case 6:
    {

      inputFile >> idShip >> idPort;

      std::list<Ship *>::iterator itr;
      for (itr = ships.begin(); itr != ships.end(); itr++)
      {
        if (idShip == (*itr)->getId())
        {
          currentShip = *itr;
        }
      }

      for (Port *port : ports)
      {
        if (port->getId() == idPort)
        {
          currentPort = port;
        }
      }

      currentShip->sailTo(currentPort);

      break;
    }
    case 7:
    {

      inputFile >> idShip >> fuel;
      // outputFile << idShip << "\n";

      for (Ship *s : ships)
      {
        if (idShip == s->getId())
        {
          s->reFuel(fuel);
        }
      }
      break;
    }

    default:
      break;
    }
  }

  std::list<Port *>::iterator itr;
  for (itr = ports.begin(); itr != ports.end(); itr++)
  {
    std::string s = (*itr)->toString();
    outputFile << s;
  }

  inputFile.close();
  outputFile.close();

  delete currentShip;
  delete currentPort;
  delete currentContainer;

  return 0;
}