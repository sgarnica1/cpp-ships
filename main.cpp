#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

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
  string line;

  for (int i = 0; i < nEvents; i++)
  {
    inputFile >> eventType;

    char type;
    int idPort, idShip, idContainer;
    int weight, totalWeight, maxNumberOfAllContainers, maxNumberOfHeavyContainers, maxNumberOfRefrigeratedContainers, maxNumberOfLiquidContainers;
    double x, y, fuel, fuelConsumptionPerKM;

    switch (eventType)
    {
    case 1:
      inputFile >> idPort >> weight >> type;
      outputFile << idPort << " " << weight << " " << type << "\n";
      break;
    case 2:
      inputFile >> idShip >> totalWeight >> maxNumberOfAllContainers >> maxNumberOfHeavyContainers >> maxNumberOfRefrigeratedContainers >> maxNumberOfLiquidContainers >> fuelConsumptionPerKM;
      outputFile << idShip << " " << totalWeight << " " << maxNumberOfAllContainers << " " << maxNumberOfHeavyContainers << " " << maxNumberOfRefrigeratedContainers << " " << maxNumberOfLiquidContainers << " " << fuelConsumptionPerKM << "\n";
      break;
    case 3:
      inputFile >> x >> y;
      outputFile << x << " " << y << "\n";
      break;
    case 4:
      inputFile >> idShip >> idContainer;
      outputFile << idShip << " " << idContainer << "\n";
      break;
    case 5:
      inputFile >> idShip >> idContainer;
      outputFile << idShip << " " << idContainer << "\n";
      break;
    case 6:
      inputFile >> idShip >> idPort;
      outputFile << idShip << " " << idPort << "\n";
      break;
    case 7:
      inputFile >> idShip >> fuel;
      outputFile << idShip << " " << fuel << "\n";
      break;

    default:
      break;
    }
  }

  inputFile.close();
  outputFile.close();
  return 0;
}