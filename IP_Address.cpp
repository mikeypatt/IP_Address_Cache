//
// Created by Michael Patterson on 18/10/2020.
//

#include <iostream>
#include "IP_Address.h"

using namespace std;
bool IP_Address::operator ==(const IP_Address &IP2) const{
    return first == IP2.first && second == IP2.second && third == IP2.third && fourth == IP2.fourth;
}

bool IP_Address::operator <(const IP_Address &IP2) const{
    if (first < IP2.first)
        return true;
    if (second < IP2.second)
        return true;
    if (third < IP2.third)
        return true;
    return fourth < IP2.fourth;

    // first < IP2.first || second < IP2.second || third < IP2.third || fourth != IP2.fourth;
}

string IP_Address::format() const {
    return to_string(first) + "." + to_string(second) + "." +
           to_string(third) + "." +  to_string(fourth);
}

void IP_Address::print(){
    cout << this->format() << endl;
}