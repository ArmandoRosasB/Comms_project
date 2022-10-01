// =========================================================
// File: Operator.h
// Author: Jos� Armando Rosas Balderas - A01704132
// Date: 1/06/2022
// Description: This file implements some functions. And it
//is a class that plays the role of an operator.
//Is the parent class of Voxoperator and InternetOperator
// =========================================================

#ifndef OPERATOR_H_INCLUDED
#define OPERATOR_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

typedef enum{VOX, INTERNET} OperatorType;
/* VOX = 0
   INTERNET = 1
*/

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingChage() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  std::string toString() const;

  /*=0 SGINIFICA QUE ESTA FUNCION NO HARA NADA
  EN ESTA CLASE, SOLO EN LAS DERIVADAS*/
  virtual double calculateTalkingCost(int, int) = 0;
  virtual double calculateMessageCost(int, int, int) = 0;
  virtual double calculateNetworkCost(double) = 0;
};

Operator :: Operator (int identificacion, double costoLlamada,
                      double costoMensaje, double costoGB,
                      int descuento, OperatorType Tipo ){

id = identificacion;
talkingCharge = costoLlamada;
messageCost = costoMensaje;
networkCharge = costoGB;
discountRate = descuento;
type = Tipo;
totalInternetUsage = 0;
totalMessageSent = 0;
totalSpentTalkingTime = 0;
}

Operator ::Operator(const Operator &other){
    id = other.id;
    talkingCharge = other.talkingCharge;
    messageCost = other.messageCost;
    networkCharge = other.networkCharge;
    discountRate = other.discountRate;
    type = other.type;
    totalInternetUsage = other.totalInternetUsage;
    totalMessageSent = other.totalMessageSent;
    totalSpentTalkingTime = other.totalSpentTalkingTime;
}

int Operator ::getId() const{
    return id;
}
int Operator::getDiscountRate()const{
    return discountRate;
}
double Operator::getTalkingChage()const{
    return talkingCharge;
}
double Operator::getMessageCost()const{
    return messageCost;
}
double Operator::getNetworkCharge()const{
    return networkCharge;
}
int Operator::getTotalSpentTalkingTime()const{
    return totalSpentTalkingTime;
}
int Operator::getTotalMessageSent()const{
    return totalMessageSent;
}
double Operator::getTotalInternetUsage() const{
    return totalInternetUsage;
}
OperatorType Operator::getType()const {
    return type;
}

void Operator::addTalkingTime(int minute){
    if(minute <=0){
        return;
    }
    totalSpentTalkingTime += minute;
}

void Operator::addTotalMessageSent(int quantity){
    if (quantity <= 0){
        return;
    }
    totalMessageSent += quantity;
}

void Operator::addTotalInternetUsage(double amount){
    if(amount<= 0){
        return;
    }
    totalInternetUsage += amount;
}

std:: string Operator::toString() const{
    std::stringstream aux;
    aux << "Operator "<<getId()<<": "<< std::fixed<< std::setprecision(2)<<" "
    <<getTotalSpentTalkingTime()<< " "<<getTotalMessageSent()<<" "
    <<getTotalInternetUsage()<< " \n";


    return aux.str();
}



#endif // OPERATOR_H_INCLUDED
