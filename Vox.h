// =========================================================
// File: Vox.h
// Author: José Armando Rosas Balderas - A01704132
// Date:04/06/2022
// Description: This file implements some functions. And it
//is a child class of Operator, designed for people that
//use more messages and talks than internet.
// =========================================================

#ifndef VOX_H_INCLUDED
#define VOX_H_INCLUDED

#include "Operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

VoxOperator:: VoxOperator(int identificacion, double costoLlamada,
                      double costoMensaje, double costoGB,
                      int descuento, OperatorType Tipo) :
    Operator(identificacion, costoLlamada, costoMensaje, costoGB, descuento, VOX){}

    /* OTRA FORMA DE INICIALIZAR EL CONSTRUCTOR COPIA
VoxOperator::VoxOperator(const VoxOperator &other): Operator(other.id, other.talkingCharge,
                      other.messageCost, other.networkCharge, other.discountRate, other.type){
    totalInternetUsage = other.totalInternetUsage;
    totalMessageSent = other.totalMessageSent;
    totalSpentTalkingTime = other.totalSpentTalkingTime;
}*/

VoxOperator::VoxOperator(const VoxOperator &other): Operator(other) {
}


double VoxOperator:: calculateTalkingCost(int minute, int age){
    double talkingCost;
    if(minute <=0 || age <= 0){
        talkingCost = 0;
        return talkingCost;
    }

    if(age < 18 || age > 65){
        talkingCost = (minute * talkingCharge);
        talkingCost =(100-discountRate)*talkingCost/100;
        return talkingCost;
    }
    talkingCost = (minute * talkingCharge);
    return talkingCost;

}

double VoxOperator:: calculateMessageCost(int quantity, int thisOpId, int otherOpId){
    double CostoMensaje;
    if (quantity <= 0){
        CostoMensaje = 0;
        return CostoMensaje;
    }
    if (id != otherOpId){
        CostoMensaje = messageCost * quantity;
        return CostoMensaje;
    }

    CostoMensaje = messageCost * quantity;
    CostoMensaje = (100- discountRate) *CostoMensaje/100;
    return CostoMensaje;
}

double VoxOperator::calculateNetworkCost(double amount) {
    double CostoInternet;
    if(amount <= 0){
        CostoInternet = 0;
        return CostoInternet;
    }
    CostoInternet = amount * networkCharge;
    return CostoInternet;

}
#endif // VOX_H_INCLUDED
