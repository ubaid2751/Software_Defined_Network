#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include "../include/packet.h"
#define  PACKET_H
using namespace std;

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BOLD  "\033[1m"

void test_packet_serialization() {
    // Create a Header and Payload object
    Header header("192.168.1.1", "10.0.0.1", "TCP", 8080, 80);
    Payload payload("This is a test payload.");

    // Create a Packet object
    Packet packet(header, payload);

    // Serialize the Packet
    byte* serialized_packet = packet.serialize();

    // Deserialize to create a new Packet object
    Packet deserialized_packet = Packet::deserialize(serialized_packet);

    // Check the integrity of the data
    assert(packet.header.source_ip == deserialized_packet.header.source_ip);
    assert(packet.header.destination_ip == deserialized_packet.header.destination_ip);
    assert(packet.header.protocol_type == deserialized_packet.header.protocol_type);
    assert(packet.header.source_port == deserialized_packet.header.source_port);
    assert(packet.header.destination_port == deserialized_packet.header.destination_port);
    assert(packet.payload.data == deserialized_packet.payload.data);

    // Clean up
    delete[] serialized_packet;

    std::cout << "Packet serialization test passed!" << std::endl;
}

void test_edge_case_empty_payload() {
    Header header("192.168.1.1", "10.0.0.1", "UDP", 12345, 54321);
    Payload payload(""); // Empty payload

    Packet packet(header, payload);

    byte* serialized_packet = packet.serialize();
    Packet deserialized_packet = Packet::deserialize(serialized_packet);

    assert(packet.payload.data == deserialized_packet.payload.data);
    
    delete[] serialized_packet;
    std::cout << "Empty payload test passed!" << std::endl;
}

void test_edge_case_empty_header() {
    // Empty header fields
    Header header("", "", "", 0, 0);
    Payload payload("Data");

    Packet packet(header, payload);

    byte* serialized_packet = packet.serialize();
    Packet deserialized_packet = Packet::deserialize(serialized_packet);

    assert(packet.header.source_ip == deserialized_packet.header.source_ip);
    assert(packet.header.destination_ip == deserialized_packet.header.destination_ip);
    
    delete[] serialized_packet;
    std::cout << "Empty header test passed!" << std::endl;
}

int main() {
    std::cout << GREEN << BOLD;
    test_packet_serialization();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    test_edge_case_empty_payload();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    test_edge_case_empty_header();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "All tests passed!" << std::endl;
    return 0;
}