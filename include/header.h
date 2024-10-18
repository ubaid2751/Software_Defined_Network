#ifndef HEADER_H
#define HEADER_H

#include<string>
#include<cstdint>
#include<cstring>
#include<iostream>
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
    size_t src_ip_len = source_ip.size();
    size_t dest_ip_len = destination_ip.size();
    size_t protocol_len = protocol_type.size();

    size_t total_size = sizeof(size_t) + src_ip_len 
                      + sizeof(size_t) + dest_ip_len 
                      + sizeof(size_t) + protocol_len
                      + sizeof(int) * 2;

    byte* serialized_data = new byte[total_size];

    memcpy(serialized_data, &src_ip_len, sizeof(size_t));
    memcpy(serialized_data + sizeof(size_t), source_ip.c_str(), src_ip_len);

    memcpy(serialized_data + sizeof(size_t) + src_ip_len, &dest_ip_len, sizeof(size_t));
    memcpy(serialized_data + sizeof(size_t) + src_ip_len + sizeof(size_t), destination_ip.c_str(), dest_ip_len);

    memcpy(serialized_data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len, &protocol_len, sizeof(size_t));
    memcpy(serialized_data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len + sizeof(size_t), protocol_type.c_str(), protocol_len);

    memcpy(serialized_data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len + sizeof(size_t) + protocol_len, &source_port, sizeof(int));
    memcpy(serialized_data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len + sizeof(size_t) + protocol_len + sizeof(int), &destination_port, sizeof(int));

    if (serialized_data == nullptr) {
        cout << "Error: Memory allocation failed!" << endl;
        throw std::bad_alloc();
    }

    return serialized_data;
}

Header Header::deserialize(byte* data) {
    size_t src_ip_len;
    memcpy(&src_ip_len, data, sizeof(size_t));
    char* src_ip = new char[src_ip_len + 1];
    memcpy(src_ip, data + sizeof(size_t), src_ip_len);
    src_ip[src_ip_len] = '\0';

    size_t dest_ip_len;
    memcpy(&dest_ip_len, data + sizeof(size_t) + src_ip_len, sizeof(size_t));
    char* dest_ip = new char[dest_ip_len + 1];
    memcpy(dest_ip, data + sizeof(size_t) + src_ip_len + sizeof(size_t), dest_ip_len);
    dest_ip[dest_ip_len] = '\0';

    size_t protocol_len;
    memcpy(&protocol_len, data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len, sizeof(size_t));
    char* protocol = new char[protocol_len + 1];
    memcpy(protocol, data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len + sizeof(size_t), protocol_len);
    protocol[protocol_len] = '\0';

    int src_port;
    memcpy(&src_port, data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len + sizeof(size_t) + protocol_len, sizeof(int));

    int dest_port;
    memcpy(&dest_port, data + sizeof(size_t) + src_ip_len + sizeof(size_t) + dest_ip_len + sizeof(size_t) + protocol_len + sizeof(int), sizeof(int));

    Header header(src_ip, dest_ip, protocol, src_port, dest_port);

    delete[] src_ip;
    delete[] dest_ip;
    delete[] protocol;

    return header;
}

#endif // HEADER_H