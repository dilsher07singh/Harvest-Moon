/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "Property.h"
#include "Employee.h"



void Property::writeToStream(ostream& os) const {
	Object::writeToStream(os);
	os << "Cost:" << getCost() << endl;
    os << "Upgrade Cost:" << getUpgradeCost() << endl;
    os << "Level:" << getLevel() << endl;
    os << "# of Employee:" << getNumEmployee() << " / " << getMaxNumEmployee() << endl;
}

void Property::upgrade() {
    m_level++;
}

void Property::getConstEmployeeList(const Employee**& employee) const {
	if (m_num_employee == 0) {
		employee =nullptr;
		return;
	}
	employee = new const Employee*[m_num_employee];
	for (int i = 0; i < m_num_employee; i++)
		employee[i] = m_employee_list[i];
}

// TODO: Start to implement your code.

Property::Property(int a, int b, int c):m_cost(a),m_upgrade_cost(b),m_max_num_employee(c) {
  //  m_employee_list=new Employee*[m_max_num_employee];
    
}

Property::~Property(){
    
    for(int i=0;i<m_num_employee;i++)
        delete m_employee_list[i];
    
    
    delete []m_employee_list;
    
    
}


int Property::getCost() const{
    return m_cost;
}

int Property::getLevel() const{
    return m_level;
}

int Property::getNumEmployee() const{
    return m_num_employee;
}

int Property::getMaxNumEmployee() const{
    return m_max_num_employee;
}

void Property::setMaxNumEmployee(int a){
    m_max_num_employee=a;
}

bool Property::assignEmployee(Employee* b){
    int d,e;
    getXY(d, e);
    int f,g;
    getSize(f, g);
   
    
    if(b->getState()!=ObjectState::NORMAL){
        return false;
    }
    if(checkEmployee(b)==false || m_num_employee>=m_max_num_employee){
        return false;
    }
    /*for(int i=0;i<m_num_employee;i++){
        if(m_employee_list[i]==b)
        return false;
    }
    */
    
    m_num_employee++;
    b->setState(ObjectState::WORK);
    Employee** m_employee_list1=new Employee*[m_num_employee];
    for(int i=0;i<m_num_employee-1;i++){
        m_employee_list1[i]=m_employee_list[i];
    }
    m_employee_list1[m_num_employee-1]=b;
    
    
    int y=1;
    int z=1;
    int w=e+1;
    for(int i=0;i<m_num_employee;i++){
    m_employee_list1[i]->setXY(d+y, e+z);
        if(w==e+g-2){
        y++;
            w=e+1;
            z=1;
        }
        else{
            w++;
            z++;
        }
    }
    
    delete []m_employee_list;
    m_employee_list=m_employee_list1;
    return true;
}

bool Property::fireEmployee(Employee* b){
    int d,e;
    getXY(d, e);
    int f,g;
    getSize(f, g);
    
    if(b==nullptr)
        return false;
    if(m_employee_list==nullptr)
        return false;
    
    m_num_employee--;
    Employee** m_employee_list1=new Employee*[m_num_employee];
    //     for(int i=0;i<m_num_employee-1;i++){
    //         m_employee_list1[i]=m_employee_list[i];
    //     }
    
    
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
    
   
    
    int y=1;
    int z=1;
    int w=e+1;
    for(int i=0;i<m_num_employee;i++){
    m_employee_list1[i]->setXY(d+y, e+z);
        if(w==e+g-2){
        y++;
            w=e+1;
            z=1;
        }
        else{
            w++;
            z++;
        }
    }
    
    
    //m_num_employee--;
    
    delete []m_employee_list;
    m_employee_list=m_employee_list1;
    return true;
}

int Property::getUpgradeCost() const{
    return m_upgrade_cost;
}
