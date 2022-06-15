// =========================================================
// File: container.h
// Author: Sergio Garnica González - A01704025
// Date: 20/05/2022
// Description:
// =========================================================
#ifndef CONTAINER_H
#define CONTAINER_H

typedef enum
{
  LIGHT,
  HEAVY,
  REFRIGERATED,
  LIQUID,
  UNDEFINED
} ContainerType;

class Container
{
protected:
  int id, weight;
  ContainerType type;

public:
  Container(int, int, ContainerType);
  Container(const Container &);

  ContainerType getType() const;
  int getId() const;
  int getWeight() const;

  bool operator==(const Container *);
  bool operator==(const Container &);
  bool operator<(const Container *);
  bool operator<(const Container &);

  virtual double getConsumption() const = 0;
};

Container::Container(int id, int weight, ContainerType type)
{
  this->id = id;
  this->type = type;

  if (weight < 0)
  {
    this->weight = 0;
  }
  else
  {
    this->weight = weight;
  }
}

Container::Container(const Container &container)
{
  this->id = container.id;
  this->weight = container.weight;
  this->type = container.type;
}

ContainerType Container::getType() const
{
  return this->type;
}

int Container::getId() const
{
  return this->id;
}

int Container::getWeight() const
{
  return this->weight;
}

bool Container::operator==(const Container *container)
{
  if (this->id != container->id)
    return false;

  if (this->weight != container->weight)
    return false;

  if (this->type != container->type)
    return false;

  return true;
}

bool Container::operator==(const Container &container)
{
  if (this->id != container.id)
    return false;

  if (this->weight != container.weight)
    return false;

  if (this->type != container.type)
    return false;

  return true;
}

bool Container::operator<(const Container *container)
{
  return this->id < container->id ? true : false;
}

bool Container::operator<(const Container &container)
{
  return this->id < container.id ? true : false;
}

#endif
