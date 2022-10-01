// =========================================================
// File: Bill.h
// Author: José Armando Rosas Balderas - A01704132
// Date: 29/05/2022
// Description: This file implements some functions. And it
//is a class that plays the role of a bill.
// =========================================================

#ifndef BILL_H_INCLUDED
#define BILL_H_INCLUDED

#include <iostream>

class Bill {
private:
    /*
    Atributos:
    Limite de crédito
    Deuda actual
    Dinero total que el cliente ha pagado a lo largo del tiempo.
    */
  double limitAmount, currentDebt, totalMoneySpent;

public:
  //Constructores
  Bill(); //Constructor default;
  Bill(double); //Constructor con parámetros
  Bill(const Bill&); //Constructor copia

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};
Bill ::Bill (){
    limitAmount = 0;
    currentDebt = 0;
    totalMoneySpent = 0;
}
Bill ::Bill(double limiteCredito) {
    if (limiteCredito <0){
        limitAmount = 0;
        currentDebt = 0;
        totalMoneySpent = 0;
    } else{
        limitAmount = limiteCredito;
        currentDebt = 0;
        totalMoneySpent = 0;
    }
}
Bill ::Bill(const Bill &b) {
    limitAmount = b.limitAmount;
    currentDebt = b.currentDebt;
    totalMoneySpent = b.totalMoneySpent;
}

double Bill ::getLimitAmount() const{
    return limitAmount;

}
double Bill ::getCurrentDebt() const{
    return currentDebt;

}
double Bill ::getTotalMoneySpent() const{
    return totalMoneySpent;

}

void Bill ::add(double amount){
    if (amount <= 0){
        return;
    }
    currentDebt += amount;
}

void Bill ::pay(double amount){
    if (amount <= 0){
        return;
    }
    if(amount > currentDebt){
        totalMoneySpent += currentDebt;
        currentDebt = 0;
        return;
    }
    currentDebt -= amount;
    totalMoneySpent += amount;
}
void Bill ::changeTheLimit(double amount){
    if (amount < currentDebt){
        return;
    }
    if (amount <= 0){
        return;
    }
    limitAmount = amount;
}

bool Bill ::check(double amount) const{
    return (amount + currentDebt <= limitAmount);
}
#endif // BILL_H_INCLUDED
