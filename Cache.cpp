//
// Created by Michael Patterson on 18/10/2020.
//
#include <iostream>
#include "Cache.h"
#include "IP_Address.h"
#include "Connection.h"

using namespace std;

bool Cache::contains(const string& key){
    return core_map.find(key) != core_map.end();
}

string Cache::create_key(IP_Address* add1,uint16_t port1,IP_Address* add2,uint16_t port2){

    string key;
    if(add1<add2)
        key = add1->format()  + to_string(port1) +
              add2->format()  + to_string(port2);
    else
        key = add2->format()  + to_string(port2)  +
              add1->format()  + to_string(port1);
    return key;
}

pair<string,int> Cache::add_cache(IP_Address* add1,uint16_t port1,IP_Address* add2,uint16_t port2){

    combined = create_key(add1,port1,add2,port2);

    int num_of_entries=1;

    if(contains(combined)) {

        num_of_entries = core_map[combined]->get_and_increment_lookups();
        sort(ordered_list.begin(),ordered_list.end(),LessThan());
        return {"existing",num_of_entries};
    }

    Connection* connection = new Connection(add1,&port1,add2,&port2);
    core_map.insert({combined, connection});
    ++size;

    ordered_list.push_back(connection);
    sort(ordered_list.begin(),ordered_list.end(),LessThan());
    return {"new", num_of_entries};

}

pair<char,int> Cache::lookup_cache(IP_Address* add1,uint16_t port1,IP_Address* add2,uint16_t port2){

    string search_key = create_key(add1,port1,add2,port2);
    int lookups = 0;
    if(contains(search_key)){
        lookups = core_map[search_key]->get_and_increment_lookups();
        return {'T',lookups};
    }
    else
        return {'F',lookups};
}


void Cache::dump(){

    sort(ordered_list.begin(),ordered_list.end(),LessThan());
     vector<Connection*>::reverse_iterator iter;
    string key;

    for(iter=ordered_list.rbegin();iter!=ordered_list.rend();++iter){
        key = (*iter)->get_key();
        delete core_map[key];
        core_map.erase(key);
        ordered_list.pop_back();
    }
}

int Cache::get_size(){return this->size;}


bool LessThan::operator() (const Connection* con1, const Connection* con2) {
    return (con1->get_lookups() < con2->get_lookups());
}



