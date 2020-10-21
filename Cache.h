// Created by Michael Patterson on 18/10/2020.
/* Main Cache Class of a defined capacity,the size variable is not implemented
 * but can add to ensure the cache remains below a defined capacity
 * the unordered map was used to ensure an average of O(1) lookup*/
//

#ifndef DARKTRACE_INITIAL_CACHE_H
#define DARKTRACE_INITIAL_CACHE_H

#include <unordered_map>
#include <string>
#include <vector>

class IP_Address;
class Connection;

class Cache{

    int size=0,capacity;
    std::unordered_map<std::string,Connection*> core_map;
    std::string combined;
    std::vector<Connection*> ordered_list;

public:

    Cache(int capacity): capacity(capacity){};

/* Boolean Function checks whether the map contains the input parameter string key and returns true
 * if so and false if not the function does not modify the map in anyway as the function is required
 * by both add_cache and lookup cache. */
    bool contains(const std::string& key);

/* Function creates the unique key from the two IP_Addresses and the two Ports as input parameters.
 * As the order of the inputs does not count the function compares the two IP Addresses and reorders
 * them to be consistent. */
    std::string create_key(IP_Address* add1,uint16_t port1,IP_Address* add2,uint16_t port2);

/* Function to add an IP address to the cache,input parameters are a pair of [address, port]
 * combinations and checks if such combination exists and if not, adds it to the cache.
 * Returns a pair of values : A string determining whether the entry is new or existing
 * and a integer stating how many lookups the connection has had. */
    std::pair<std::string,int> add_cache(IP_Address* add1,uint16_t port1,
                                         IP_Address* add2,uint16_t port2);

/* Function to lookup a connection in the cache,input parameters are two pairs of
 * [address, port] combinations and checks if such combination exists and if not,
 * returns a pair of values : A character determining whether the entry is in the
 * cache (T or F), can be replaced with a boolean but from specifications it wasn't clear.
 * The second value is an integer stating how many lookups the connection has had. */
    std::pair<char,int> lookup_cache(IP_Address* add1,uint16_t port1,
                                     IP_Address* add2,uint16_t port2);

/* Function empties the contents of the cache to standard output by deleting the connections
 * in order of the most lookups. This order is maintained by a vector that is sorted upon every
 * connection entry and once when function is invoked. */
    void dump();

/* Function to return the current size of the cache, with the current configuration
 * it is not required as the size is not tracked. */
    int get_size();

};

struct LessThan
{
     bool operator() (const Connection* con1, const Connection* con2);
};


#endif //DARKTRACE_INITIAL_CACHE_H




