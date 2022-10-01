// =========================================================
// File: main.cpp
// Author: Jos� Armando Rosas Balderas
// Date: 14/06/2022
// Description:
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputFile;
    ofstream outputFile;
    int c, o, n, i, nc, j, k;
    vector <Customer*> customers;
    vector <Operator*> operators;
    if (argc != 3) {
        cout << "usage: " << argv[0] << "input_file output_file \n";
        return -1;
    }
    inputFile.open(argv[1]);

    if (!inputFile.is_open()) {
        cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
        return -1;
  }
    outputFile.open(argv[2]);

    inputFile >> c >> o >> n;
    customers.resize(c);
    operators.resize(o);
    j = 0;
    k = 0;

    for (i= 0; i<n; i++){//Leer cada palabra separada por espacio por separado en el renglon n
            inputFile >> nc;
            string name ;
            int id, iddos, age , operatorID, quantity, idOperator, t, time;
            double limitingAmount, talkingCharge, messageCost, networkCharge, discountRate, amount ;

        switch(nc) {
            case 1:
                inputFile>>name>>age>>operatorID>>limitingAmount;
                customers[j] = new Customer(j, name, age,operators[operatorID], limitingAmount);
                j +=1;
                break;
            case 2:
                inputFile>>t>>talkingCharge>> messageCost>> networkCharge>>discountRate;
                if(t = 1){
                   operators[k] = new VoxOperator(k, talkingCharge, messageCost,networkCharge, discountRate, VOX);
                     k+=1;
                } else{
                   operators[k] = new InternetOperator(k, talkingCharge, messageCost, networkCharge, discountRate, INTERNET);
                     k+=1;
                }
               break;
            case 3:
                inputFile>> id>> iddos>> time;
                customers[id]->talk(time, *customers[iddos]);
               break;
            case 4:
                inputFile>>id>>iddos>>quantity;
                customers[id]->message(quantity,* customers[iddos]);
                break;
            case 5:
                inputFile>>id>>amount;
                customers[id]->connection(amount);
                break;
            case 6:
                inputFile>>id>>amount;
                customers[id]->pay(amount);
                break;
            case 7:
                inputFile>> id>>idOperator;
                customers[id]->setOperator(operators[idOperator]);
                break;
            case 8:
                inputFile>>id>>amount;
                customers[id]->getBill()->changeTheLimit(amount);
                break;

        }

        }
    int maxTalk, ii, jj, idd, maxMess, maxInt;
    for (i = 0; i<o; i++){
        outputFile<< operators[i]->toString();
    }
    for(i = 0; i<c;i++){
        outputFile<< customers[i]->toString();
    }

    vector <Customer*> c1;
    vector <Customer*> c2;
    vector <Customer*> c3;

    //Cliente que m�s habla
    maxTalk = 0;
    for (i = 0; i<c; i++){
        if(customers[i]->getTotalSpentTalkingTime()>=maxTalk){
            maxTalk = customers[i]->getTotalSpentTalkingTime();
        }
    }

    ii = 0;
    for (i = 0; i<c; i++){
        if (customers[i]->getTotalSpentTalkingTime()==maxTalk){
        ii++;
        c1.resize(ii);
    }
    }


    jj = 0;
    for (i = 0; i<c; i++){
        if (customers[i]->getTotalSpentTalkingTime()==maxTalk){
            c1[jj] = customers[i];
            jj++;
        }
    }


    idd = 0;
    if(ii == 1){
        outputFile<<c1[jj-1]->getName()<<": "<<c1[jj-1]->getTotalSpentTalkingTime()<<endl;
    } else{
        for (i = 0; i<ii; i++){
            if(customers[i]->getId()<= idd){
                idd = customers[i]->getId();
            }
            for (i = 0; i<c; i++){
                if(customers[i]->getId() == idd){
                    outputFile<<customers[i]->getName()<<": "<<customers[i]->getTotalSpentTalkingTime()<<endl;
                }
            }

        }


    }

    //Cliente que mas mensajea
    maxMess = 0;

    for (i = 0; i<c; i++){
        if(customers[i]->getTotalMessageSent()>=maxMess){
            maxMess = customers[i]->getTotalMessageSent();
        }
    }

    ii = 0;
    for (i = 0; i<c; i++){
        if (customers[i]->getTotalMessageSent()==maxMess){
        ii++;
    }
    }
    c2.resize(ii);

    jj = 0;
    for (i = 0; i<c; i++){
        if (customers[i]->getTotalMessageSent()==maxMess){
            c2[jj] = customers[i];
            jj++;
        }
    }


    idd = 0;
    if(ii == 1){
        outputFile<<c2[jj-1]->getName()<<": "<<c2[jj-1]->getTotalMessageSent()<<endl;
    } else{
        for (i = 0; i<ii; i++){
            if(customers[i]->getId()<= idd){
                idd = customers[i]->getId();
            }
            for (i = 0; i<c; i++){
                if(customers[i]->getId() == idd){
                    outputFile<<customers[i]->getName()<<": "<<customers[i]->getTotalMessageSent()<<endl;
                }
            }

        }


    }

    //Cliente que mas usa Internet
    maxInt = 0;

    for (i = 0; i<c; i++){
        if(customers[i]->getTotalInternetUsage()>=maxInt){
            maxInt = customers[i]->getTotalInternetUsage();
        }
    }

    ii = 0;
    for (i = 0; i<c; i++){
        if (customers[i]->getTotalInternetUsage()==maxInt){
        ii++;
    }
    }
    c3.resize(ii);

    jj = 0;
    for (i = 0; i<c; i++){
        if (customers[i]->getTotalInternetUsage()==maxInt){
            c3[jj] = customers[i];
            jj++;
        }
    }


    idd = 0;
    if(ii == 1){
        outputFile<<c3[jj-1]->getName()<<": "<<c3[jj-1]->getTotalInternetUsage()<<endl;
    } else{
        for (i = 0; i<ii; i++){
            if(customers[i]->getId()<= idd){
                idd = customers[i]->getId();
            }
            for (i = 0; i<c; i++){
                if(customers[i]->getId() == idd){
                    outputFile<<customers[i]->getName()<<": "<<customers[i]->getTotalInternetUsage()<<endl;
                }
            }

        }


    }



    for (i = 0; i<o; i++){
         delete operators[i];
    }
    for(i = 0; i<c;i++){
        delete customers[i];
    }


    inputFile.close();
    outputFile.close();

  return 0;
}


