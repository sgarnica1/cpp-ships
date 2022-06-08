// =========================================================
// File: simpleship.h
// Author: Sergio Garnica González - A01704025
// Date:
// Description:
// =========================================================

#ifndef SIMPLE_SHIP_H
#define SIMPLE_SHIP_H

class SimpleShip
{
protected:
  int id;

public:
  SimpleShip(int);
  SimpleShip(const SimpleShip &);

  int getId() const;

  bool operator==(const SimpleShip *);
  bool operator==(const SimpleShip &);

  bool operator<(const SimpleShip *);
  bool operator<(const SimpleShip &);

  virtual std::string toString() const = 0;
};

SimpleShip::SimpleShip(int id)
{
  this->id = id;
}

SimpleShip::SimpleShip(const SimpleShip &ship)
{
  this->id = ship.id;
}

int SimpleShip::getId() const
{
  return this->id;
}

bool SimpleShip::operator==(const SimpleShip *ship)
{
  return this->id == ship->id ? true : false;
}

bool SimpleShip::operator==(const SimpleShip &ship)
{
  return this->id == ship.id ? true : false;
}

bool SimpleShip::operator<(const SimpleShip *ship)
{
  return this->id == ship->id ? true : false;
}

bool SimpleShip::operator<(const SimpleShip &ship)
{
  return this->id == ship.id ? true : false;
}

#endif
