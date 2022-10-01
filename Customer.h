// =========================================================
// File: customer.h
// Author: José Armando Rosas Balderas
// Date: 13/06/2022
// Description: This file implements some functions. And it
//is a class that plays the role of a customer.
//Include the class operator and bill
// =========================================================

#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  std::string name;
  Operator* op;
  Bill *bill;

public:
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  std::string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
  void pay(double);
};

Customer :: Customer(int identificacion, std::string nombre, int edad,
                      Operator *o, double limite_Credito){
    id = identificacion;
    name = nombre;
    age = edad;
    op = o;
    bill = new Bill(limite_Credito);
    totalSpentTalkingTime = 0;
    totalMessageSent= 0;
    totalInternetUsage = 0;

}
Customer :: Customer(const Customer &other){}

Customer:: ~Customer(){
    delete bill;
    bill = 0;

}

int Customer:: getId() const {
    return id;
}
int  Customer:: getAge() const{
    return age;
}
int  Customer::getTotalSpentTalkingTime() const{
    return totalSpentTalkingTime;
}
int  Customer::getTotalMessageSent() const{
    return totalMessageSent;
}
double Customer::getTotalInternetUsage() const{
    return totalInternetUsage;
}
std::string Customer::getName() const {
    return name;
}
Operator* Customer::getOperator() const{
    return op;
}
Bill* Customer::getBill() const {
    return bill;
}
void Customer:: setOperator(Operator* o){
    op = o;
}

std::string Customer:: toString() const {
    std::stringstream aux;
    aux << "Customer "<<getId()<<": " <<std::fixed<<std::setprecision(2)
    <<" "<< bill->getTotalMoneySpent()<<" "<< bill->getCurrentDebt()<<"\n";

    return aux.str();
}

void Customer ::talk(int minutes, Customer &other){
    double CostoLlamada ;

    if(minutes >0 && id != other.getId()){
        CostoLlamada = op->calculateTalkingCost(minutes, age);

        if (bill->check(CostoLlamada) ){
            bill->add(CostoLlamada);
            totalSpentTalkingTime += minutes;
            op->addTalkingTime(minutes);

            if(op->getId() != other.getOperator()->getId()){
                other.getOperator()->addTalkingTime(minutes);
            }
    }

}
}

void Customer::message(int quantity, const Customer &other){
    double CostoMensajes ;
    if(quantity>0 && id != other.getId()){
        CostoMensajes = op->calculateMessageCost(quantity, id, other.getOperator()->getId());

        if(bill->check(CostoMensajes)){
            bill->add(CostoMensajes);
            totalMessageSent += quantity;
            op->addTotalMessageSent(quantity);
    }
    }
}
void Customer::connection(double amount){
    double costoInternet;
    if(amount> 0){
        costoInternet = op->calculateNetworkCost(amount);

    if(bill->check(costoInternet)){
        bill->add(costoInternet);
        totalInternetUsage += amount;
        op->addTotalInternetUsage(amount);
    }
    }
}
void Customer::pay(double pago){
        bill->pay(pago);

}

#endif // CUSTOMER_H_INCLUDED
