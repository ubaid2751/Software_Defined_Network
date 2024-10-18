#ifndef HEADER_H
#define HEADER_H

#include<string>
#include<cstdint>
#include<cstring>
using namespace std;

class Header {
public:
    string source_ip;
    string destination_ip;
    string protocol_type;
    int source_port;
    int destination_port;

    Header(string src_ip, string dest_ip, string protocol, int src_port, int dest_port)
        : source_ip(src_ip), destination_ip(dest_ip), protocol_type(protocol), source_port(src_port), destination_port(dest_port) {}

    byte* serialize();
    static Header deserialize(byte* data);
};

byte* Header::serialize() {

}

#endif // HEADER_H