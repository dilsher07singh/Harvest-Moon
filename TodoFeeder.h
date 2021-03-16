/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#ifndef FEEDER_H_
#define FEEDER_H_

#include "Employee.h"
// TODO: Start to implement your code.
class Feeder: public Employee{
    
public:
    Feeder();
    
    ~Feeder();
    
    string getName() const override;
    
    char getSymbol() const override;
    
};

#endif /*FEEDER_H_*/
