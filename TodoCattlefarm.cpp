/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoCow.h"
#include <cstdlib>

// Cattlefarm cost 80 upgrade cost 16
// Cattlefarm size 6, 6
// Cattlefarm init max num. of employee is CATTLEFARM_MAX_NUM_EMPLOYEE_MIN
// Cattlefarm Upgrade:
//      level increases by 1;
//      max num. of employees increases by 1 until CATTLEFARM_MAX_NUM_EMPLOYEE_MAX
// Cattlefarm Makemoney:
//      min(num. of cows, num. of feeders in work) x level x 10;

const int CATTLEFARM_COST = 80;
const int CATTLEFARM_UPGRADE_COST = 16;
const int CATTLEFARM_SIZE_X = 6; const int CATTLEFARM_SIZE_Y = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MIN = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MAX = (CATTLEFARM_SIZE_X-2) * (CATTLEFARM_SIZE_Y-2);

// TODO: Start to implement your code.

Cattlefarm::Cattlefarm(int x,int y):Property(CATTLEFARM_COST, CATTLEFARM_UPGRADE_COST, CATTLEFARM_MAX_NUM_EMPLOYEE_MIN ) {
    setXY(x, y);
    setSize(CATTLEFARM_SIZE_X, CATTLEFARM_SIZE_Y);
}

bool Cattlefarm::checkEmployee(Employee* b) const{
    if(b==nullptr)
          return false;
    else if(b->getName()=="Feeder" || b->getName()=="Cow")
        return true;
    else
        return false;
}

int Cattlefarm::makeMoney() const{
    const Employee** used;
    getConstEmployeeList(used);
    
    int feeder=0;
    int cow=0;
    for(int i=0;i<getNumEmployee();i++){
        if(used[i]->getName()=="Feeder" && used[i]->getState()==ObjectState::WORK)
            feeder++;
        else if(used[i]->getName()=="Cow")
            cow++;
    }
    delete []used;
    int x=std::min(feeder,cow);
    int y=x*10*getLevel();
    return y;
}

void Cattlefarm::removeDiedCow(){
// implementing using dynamic cast and const cast
    const Employee **b;
    getConstEmployeeList(b);
    int x=getNumEmployee();
    for(int i=0;i<x;i++){
        Employee*a=const_cast<Employee*>(b[i]);
        Cow*p=dynamic_cast<Cow*>(a);
        if(p!=nullptr){
            if(p->isAlive()==false){
                fireEmployee(p);
            }
        }
        
    }
    delete []b;
}

void Cattlefarm::upgrade(){
   Property::upgrade();
    
    
    if(getMaxNumEmployee()<CATTLEFARM_MAX_NUM_EMPLOYEE_MAX){
        setMaxNumEmployee(getMaxNumEmployee()+1);


    }
}

string Cattlefarm::getName() const{
    return "Cattlefarm";
}

char Cattlefarm::getSymbol() const{
    return 'C';
}
