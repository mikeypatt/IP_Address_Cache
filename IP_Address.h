// Created by Michael Patterson on 18/10/2020.
/* IP Address Class containing the information and functionality
 * required: display format and comparable functions*/
//

#ifndef DARKTRACE_INITIAL_IP_ADDRESS_H
#define DARKTRACE_INITIAL_IP_ADDRESS_H

#include <cstdint>
#include <string>

class IP_Address {

    uint8_t first,second,third,fourth; //unsigned short integer (1 byte)
public:

    IP_Address(uint8_t one,uint8_t two,uint8_t three,uint8_t four):
            first(one),second(two),third(three),fourth(four){}

    //Redefining the equal to than operator for the IP Address class
    bool operator == (const IP_Address &IP2) const;

    //Redefining the less than operator for the IP Address class
    bool operator < (const IP_Address &IP2) const;

    // Function to convert the 4 unsigned short 1 Byte Integers into a readable format
    std::string format() const;

    void print();

};




#endif //DARKTRACE_INITIAL_IP_ADDRESS_H
