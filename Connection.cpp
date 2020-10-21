// Created by Michael Patterson on 18/10/2020.

#include <iostream>
#include "Connection.h"

using namespace std;

Connection::Connection(IP_Address *add1,uint16_t *port1,IP_Address *add2,
            uint16_t *port2):IP1(add1),IP2(add2),port1(port1),port2(port2){

    if(add1<add2)
    key = add1->format() + std::to_string(*port1) +
          add2->format() + std::to_string(*port2);
    else
    key = add2->format() + std::to_string(*port2) +
          add1->format() + std::to_string(*port1);
}

bool Connection::operator < (const Connection &con2) const{
    return this->lookups < con2.get_lookups();
}

std::string Connection::get_key() {return key;}

int Connection::get_lookups() const { return lookups;}
int Connection::get_and_increment_lookups() {return ++lookups;}

Connection::~Connection(){
    cout << IP1->format() + "," << *port1 ;
    cout << " <-> " + IP2->format() + "," << *port2;
    cout << ": " << lookups << endl;
}
