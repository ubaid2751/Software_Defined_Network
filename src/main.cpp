#include <iostream>
#include <memory>
#include <cassert>
#include "../include/flowrule.h"
#include "../include/packet.h"

// Function to test forwarding action
void test_forward_action() {
    std::cout << "Running Forward Action Test..." << std::endl;
    Packet packet(Header("192.168.1.1", "192.168.1.2", "TCP", 1234, 80), Payload("Test Data"));
    MatchFields match_fields = { "192.168.1.1", "192.168.1.2", "TCP", 1234, 80 };
    auto action = std::make_unique<ForwardAction>(5);
    FlowRule flow_rule(match_fields, std::move(action));

    if (flow_rule.matches_packet(packet)) {
        flow_rule.execute_action(); // Expect: "Forwarding to port 5"
    }
}

// Function to test drop action
void test_drop_action() {
    std::cout << "Running Drop Action Test..." << std::endl;
    Packet packet(Header("192.168.1.1", "192.168.1.2", "TCP", 1234, 80), Payload("Test Data"));
    MatchFields match_fields = { "192.168.1.1", "192.168.1.2", "TCP", 1234, 80 };
    auto action = std::make_unique<DropAction>();
    FlowRule flow_rule(match_fields, std::move(action));

    if (flow_rule.matches_packet(packet)) {
        flow_rule.execute_action(); // Expect: "Dropping packet"
    }
}

// Function to test modify action
void test_modify_action() {
    std::cout << "Running Modify Action Test..." << std::endl;
    Packet packet(Header("192.168.1.1", "192.168.1.2", "TCP", 1234, 80), Payload("Test Data"));
    MatchFields match_fields = { "192.168.1.1", "192.168.1.2", "TCP", 1234, 80 };
    auto action = std::make_unique<ModifyAction>();
    FlowRule flow_rule(match_fields, std::move(action));

    if (flow_rule.matches_packet(packet)) {
        flow_rule.execute_action(); // Expect: "Modifying packet"
    }
}

// Function to test no match
void test_no_match() {
    std::cout << "Running No Match Test..." << std::endl;
    Packet packet(Header("192.168.1.3", "192.168.1.4", "UDP", 1234, 80), Payload("Test Data"));
    MatchFields match_fields = { "192.168.1.1", "192.168.1.2", "TCP", 1234, 80 };
    auto action = std::make_unique<DropAction>();
    FlowRule flow_rule(match_fields, std::move(action));

    assert(!flow_rule.matches_packet(packet)); // Expect: false
}

// Function to test statistics update
void test_update_stats() {
    std::cout << "Running Update Stats Test..." << std::endl;
    Packet packet(Header("192.168.1.1", "192.168.1.2", "TCP", 1234, 80), Payload("Test Data"));
    MatchFields match_fields = { "192.168.1.1", "192.168.1.2", "TCP", 1234, 80 };
    auto action = std::make_unique<ForwardAction>(5);
    FlowRule flow_rule(match_fields, std::move(action));

    if (flow_rule.matches_packet(packet)) {
        flow_rule.execute_action();
        flow_rule.update_stats(packet);
        // Verify counts
        // Add your actual implementations for getting counts if you have them
        // Example assertions (assuming you have methods to get these values):
        // assert(flow_rule.get_packet_count() == 1);
        // assert(flow_rule.get_byte_count() == packet.payload.data.size());
    }
}

// Function to test timeouts
void test_timeouts() {
    std::cout << "Running Timeouts Test..." << std::endl;
    MatchFields match_fields = { "192.168.1.1", "192.168.1.2", "TCP", 1234, 80 };
    auto action = std::make_unique<ForwardAction>(5);
    FlowRule flow_rule(match_fields, std::move(action));

    // Simulate timeout logic here if implemented
    // This will depend on how you've implemented timeouts
    // For example, checking if flow rule is valid after a timeout period
}

int main() {
    test_forward_action();
    test_drop_action();
    test_modify_action();
    test_no_match();
    test_update_stats();
    test_timeouts();

    std::cout << "All tests completed!" << std::endl;
    return 0;
}
