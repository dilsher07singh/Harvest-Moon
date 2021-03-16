/*
 * File Created: Mon Mar 16 2020
 * Author:
 * SID:
*/

#include "Scene.h"
#include "Property.h"
#include "TodoFarmland.h"
#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoFarmer.h"
#include "TodoFeeder.h"
#include "TodoCow.h"

const int SCENE_W = 45;
const int SCENE_H = 10;
const int PROPERTY_X = 35;
const int SCENE_INIT_MONEY = 200;

Scene::Scene()
: m_objects(nullptr), m_num_objects(0), m_money(SCENE_INIT_MONEY) {
    nextRound();
}

Scene::~Scene() {
    //shallowremove employees
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::EMPLOYEE)
            shallowRemoveEmployee(dynamic_cast<Employee*>(m_objects[i]));
    }
    // remove properties
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::PROPERTY)
            delete m_objects[i];
    }
    delete[] m_objects;
}

void Scene::shallowRemoveEmployee(Employee* e) {
    if (m_num_objects <= 0) return;
    if (m_num_objects == 1 && e == m_objects[0]) {
        m_num_objects = 0;
        m_objects = nullptr;
        return;
    }
    int i;
    for (i = 0; i < m_num_objects; i++) {
        if (m_objects[i] == e)
            break;
    }
    Object ** newObjects = new Object*[m_num_objects--];
    for (int j = 0; j < m_num_objects; j++)
        newObjects[j] = m_objects[j];
    if (m_num_objects != i)
        newObjects[i] = m_objects[m_num_objects];
    delete [] m_objects;
    m_objects = newObjects;
}

bool Scene::checkOverlap(const Property* newproperty) {
    int x, y, sz_x, sz_y;
    newproperty->getXY(x, y);
    newproperty->getSize(sz_x, sz_y);
    for(int xx=x; xx<x+sz_x; xx++)
        for(int yy=y; yy<y+sz_y; yy++)
            if(getObjectAt(xx, yy) != nullptr) return true;
    return false;
}


void Scene::addProperty(int property, int x, int y) {
    Property* newProperty = nullptr;
    switch(property) {
    case FARMLAND:
        newProperty = new Farmland(x,y);
        break;
    case CATTLEFARM:
        newProperty = new Cattlefarm(x, y);
        break;
    }
    if (newProperty == nullptr) return;
    if (newProperty->getCost() > m_money || checkOverlap(newProperty)) {
        delete newProperty;
        return;
    }
    addObject(newProperty);
    m_money -= newProperty->getCost();
}


bool Scene::hire(Property* p, int employee) {
    Employee* newEmployee = nullptr;
    switch(employee){
    case EMPLOYEE:
        newEmployee = new Employee();
        break;
    case FARMER:
        newEmployee = new Farmer();
        break;
    case FEEDER:
        newEmployee = new Feeder();
        break;
    case COW:
        newEmployee = new Cow();
        break;
    }
    if (newEmployee == nullptr) return false;
    if (newEmployee->getCost() > m_money || ! p->assignEmployee(newEmployee)) {
        delete newEmployee;
        return false;
    }
    addObject(newEmployee);
    m_money -= newEmployee->getCost();
    return true;
}


Object* Scene::getObjectAt(int s_x, int s_y) const {
    int x, y, sz_x, sz_y;
    // If employee is at s_x, s_y, get employee
    // else, get property
    // otherwise return null
    for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::PROPERTY)
            continue;
        m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
            return m_objects[i];
    }
    for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE)
            continue;
        m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
            return m_objects[i];
    }
    return nullptr;
}

//perform shallow copying
void Scene::addObject(Object* newobj) {
    Object** newobjects = new Object*[m_num_objects + 1];
    for (int i = 0; i < m_num_objects; i++)
        newobjects[i] = m_objects[i];
    newobjects[m_num_objects++] = newobj;
    if (m_num_objects != 1)
        delete [] m_objects;
    m_objects = newobjects;
}

void Scene::getConstObjects(const Object**& obj, int& count) const {
    count = m_num_objects;
    if (m_num_objects == 0) {
        obj =nullptr;
        return;
    }
    obj = new const Object*[m_num_objects];
    for (int i = 0; i < m_num_objects; i++)
        obj[i] = m_objects[i];
}

// TODO: Start to implement your code.

void Scene::removeProperty(Property* a){
   
    const Employee**f;
    a->getConstEmployeeList(f);
    int x=a->getNumEmployee();
    
    for(int i=0;i<x;i++){
        Employee*y=const_cast<Employee*>(f[i]);
        fire(y);
    }

    
    Object**m_objects1=new Object*[m_num_objects-1];
      
   
    for(int i=0;i<m_num_objects;i++){
          if(m_objects[i]==a){
              delete m_objects[i];
              for(int j=i;j<m_num_objects-1;j++)
                  m_objects1[j]=m_objects[j+1];
              for(int j=0;j<i;j++)
              m_objects1[j]=m_objects[j];
          
      }
    }

    /*
      for(int i=0;i<m_num_employee+1;i++){
             if(m_employee_list[i]==b){
                 delete m_employee_list[i];
                 for(int j=i;j<m_num_employee;j++){
                     m_employee_list1[j]=m_employee_list[j+1];
                 }
                 for(int j=0;j<i;j++){
                     m_employee_list1[j]=m_employee_list[j];
                              }

             }
                 
         }
     */

    m_num_objects--;
      delete []m_objects;
      m_objects=m_objects1;
    delete []f;
}

bool Scene::fire(Employee* c){
    if(c==nullptr)
        return false;
    
    shallowRemoveEmployee(c);

    for(int i=0;i<m_num_objects;i++){
        if(m_objects[i]->getObjectType()==ObjectType::PROPERTY){
            const Employee**b;
            Property*p=dynamic_cast<Property*>(m_objects[i]);
            p->getConstEmployeeList(b);
            int f=p->getNumEmployee();
            
            for(int i=0;i<f;i++){
                if(b[i]==c)
                    p->fireEmployee(c);
                   }
            delete []b;
        }
            
    }

//    shallowRemoveEmployee(c);
    
    return true;
}

bool Scene::upgrade(Property* p){
    if(p==nullptr)
        return false;
    
    if(m_money<p->getUpgradeCost())
        return false;
    
    if(m_money>=p->getUpgradeCost()){
        p->upgrade();
    m_money=m_money-p->getUpgradeCost();
    }
    
    return true;
}

void Scene::nextRound(){
  
        for(int i=0;i<m_num_objects;i++){

         if(m_objects[i]->getObjectType()==ObjectType::PROPERTY){
                   Property*q=dynamic_cast<Property*>(m_objects[i]);
                   m_money=m_money+q->makeMoney();
        
         }}
    for(int i=0;i<m_num_objects;i++){
          
           if(m_objects[i]->getObjectType()==ObjectType::EMPLOYEE){
              Employee*p=dynamic_cast<Employee*>(m_objects[i]);
              m_money=m_money-p->getSalary();
              p->updateWorkAge();
              p->updateState();
              
           }}
    for(int i=0;i<m_num_objects;i++){

            if(m_objects[i]->getObjectType()==ObjectType::PROPERTY){
                  Cattlefarm*j=dynamic_cast<Cattlefarm*>(m_objects[i]);

                   if(j!=nullptr){
                       const Employee **y;
                          j->getConstEmployeeList(y);
                          int z=j->getNumEmployee();
                          for(int i=0;i<z;i++){
                              Employee*t=const_cast<Employee*>(y[i]);
                              Cow*h=dynamic_cast<Cow*>(t);
                              if(h!=nullptr){
                                  if(h->isAlive()==false)
                                      shallowRemoveEmployee(h);
                              }
                          }
                           
                           
                              j->removeDiedCow();
                       delete []y;
               }
            }
           
       }
    
    
    
    }

bool Scene::isGameOver() const{
    if(m_money<0)
    return true;
    else
        return false;
}
