// Created by Michael Patterson on 18/10/2020.
/* Connection Class containing pointers to two IP Address and two ports
 * this class enables easy management of the creation,lookup and
 * deletion of connections within the cache*/
//

#ifndef DARKTRACE_INITIAL_CONNECTION_H
#define DARKTRACE_INITIAL_CONNECTION_H

#include "IP_Address.h"

class Connection {

    IP_Address *IP1,*IP2;
    uint16_t *port1,*port2;
    std::string key;
    int lookups = 1;

public:
    Connection(IP_Address *add1,uint16_t *port1,IP_Address *add2,
                                                    uint16_t *port2);

    //Function to return the string key of the specified connection
    std::string get_key();

    //Redefining the less than operator for the connection class
    bool operator < (const Connection &IP2) const;

    //Function increments and returns the number of lookups the connection has
    int get_and_increment_lookups();

    //Function just returns the number of lookups but does not increment them
    int get_lookups()const;

    //Destructor dumps the connection attributes to std output
    ~Connection();

};

#endif //DARKTRACE_INITIAL_CONNECTION_H
