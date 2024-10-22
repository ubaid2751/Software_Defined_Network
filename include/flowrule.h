#ifndef FLOWRULE_H
#define FLOWRULE_H

#include <string>
#include <iostream>
#include <memory>
#include "packet.h"
using namespace std;

class Action {
public:
    virtual ~Action() = default;
    virtual void execute() const = 0;
};

class ForwardAction: public Action {
private:
    uint16_t out_port;
public:
    ForwardAction(uint16_t port) : out_port(port) {}
    void execute() const override {
        cout << "Forwarding to port " << out_port << endl;
    }
};

class DropAction: public Action {
public:
    void execute() const override {
        cout << "Dropping packet" << endl;
    }
};

class ModifyAction: public Action {
public:
    void execute() const override {
        cout << "Modifying packet" << endl;
    }
};

struct MatchFields {
    string src_ip;
    string dest_ip;
    uint16_t src_port;
    uint16_t dest_port;
    uint8_t protocol;

    bool operator==(const MatchFields &other) const {
        return (
            src_ip == other.src_ip &&
            dest_ip == other.dest_ip &&
            src_port == other.src_port &&
            dest_port == other.dest_port &&
            protocol == other.protocol
        );
    }
};

class FlowRule {
private:
    MatchFields match_fields;
    unique_ptr<Action> action;
    uint16_t priority;
    uint32_t hard_timeout;
    uint32_t idle_timeout;
    uint64_t packet_count;
    uint64_t byte_count;

public:
    FlowRule(
        MatchFields match_fields,
        unique_ptr<Action> action,
        uint16_t priority = 1,
        uint32_t hard_timeout = 0,
        uint32_t idle_timeout = 0) 
        : match_fields(match_fields), action(move(action)), priority(priority), hard_timeout(hard_timeout), idle_timeout(idle_timeout), packet_count(0), byte_count(0) {}
    
    bool matches_packet(const Packet &p) const {
        return (
            match_fields.src_ip == p.header.source_ip &&
            match_fields.dest_ip == p.header.destination_ip &&
            match_fields.src_port == p.header.source_port &&
            match_fields.dest_port == p.header.destination_port &&
            match_fields.protocol == p.header.protocol_type
        );
    }

    void execute_action() const {
        if(action) {
            action->execute();
        }
    }

    void update_stats(const Packet &p) {
        packet_count++;
        byte_count += p.payload.data.size();
    }
};

#endif // FLOWRULE_H