// #ifndef HEADER_H
#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include "../include/header.h" // Include your header file
#define  HEADER_H
using namespace std;

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BOLD  "\033[1m"

void test_basic_serialization() {
    // Create a Header object
    Header header("192.168.1.1", "10.0.0.1", "TCP", 8080, 80);
    
    // Serialize the Header
    byte* serialized_data = header.serialize();
    
    // Deserialize to create a new Header object
    Header deserialized_header = Header::deserialize(serialized_data);
    
    // Check the integrity of the data
    assert(header.source_ip == deserialized_header.source_ip);
    assert(header.destination_ip == deserialized_header.destination_ip);
    assert(header.protocol_type == deserialized_header.protocol_type);
    assert(header.source_port == deserialized_header.source_port);
    assert(header.destination_port == deserialized_header.destination_port);
    
    // Clean up
    delete[] serialized_data;

    std::cout << "Basic serialization test passed!" << std::endl;
}

void test_multiple_headers() {
    Header header1("192.168.1.1", "10.0.0.1", "TCP", 8080, 80);
    Header header2("172.16.0.1", "192.168.0.1", "UDP", 3000, 53);

    // Serialize both headers
    byte* serialized_data1 = header1.serialize();
    byte* serialized_data2 = header2.serialize();

    // Deserialize both headers
    Header deserialized_header1 = Header::deserialize(serialized_data1);
    Header deserialized_header2 = Header::deserialize(serialized_data2);

    // Check the integrity of the data
    assert(header1.source_ip == deserialized_header1.source_ip);
    assert(header1.destination_ip == deserialized_header1.destination_ip);
    assert(header1.protocol_type == deserialized_header1.protocol_type);
    assert(header1.source_port == deserialized_header1.source_port);
    assert(header1.destination_port == deserialized_header1.destination_port);

    assert(header2.source_ip == deserialized_header2.source_ip);
    assert(header2.destination_ip == deserialized_header2.destination_ip);
    assert(header2.protocol_type == deserialized_header2.protocol_type);
    assert(header2.source_port == deserialized_header2.source_port);
    assert(header2.destination_port == deserialized_header2.destination_port);

    // Clean up
    delete[] serialized_data1;
    delete[] serialized_data2;

    std::cout << "Multiple headers test passed!" << std::endl;
}

void test_edge_cases() {
    // Test with empty fields
    Header header("", "", "", 0, 0);
    
    // Serialize the Header
    byte* serialized_data = header.serialize();
    
    // Deserialize to create a new Header object
    Header deserialized_header = Header::deserialize(serialized_data);
    
    // Check the integrity of the data
    assert(header.source_ip == deserialized_header.source_ip);
    assert(header.destination_ip == deserialized_header.destination_ip);
    assert(header.protocol_type == deserialized_header.protocol_type);
    assert(header.source_port == deserialized_header.source_port);
    assert(header.destination_port == deserialized_header.destination_port);
    
    // Clean up
    delete[] serialized_data;

    std::cout << "Edge cases test passed!" << std::endl;
}

void test_boundary_values() {
    // Test with maximum expected lengths
    Header header("255.255.255.255", "255.255.255.255", "TCP", 65535, 65535);
    
    // Serialize the Header
    byte* serialized_data = header.serialize();
    
    // Deserialize to create a new Header object
    Header deserialized_header = Header::deserialize(serialized_data);
    
    // Check the integrity of the data
    assert(header.source_ip == deserialized_header.source_ip);
    assert(header.destination_ip == deserialized_header.destination_ip);
    assert(header.protocol_type == deserialized_header.protocol_type);
    assert(header.source_port == deserialized_header.source_port);
    assert(header.destination_port == deserialized_header.destination_port);
    
    // Clean up
    delete[] serialized_data;

    std::cout << "Boundary values test passed!" << std::endl;
}

int main() {
    // Run tests
    std::cout << GREEN << BOLD;
    test_basic_serialization();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    test_multiple_headers();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    test_edge_cases();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    test_boundary_values();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
