#ifndef PACKET_H
#define PACKET_H

#include <cstdint>
#include <vector>

class Packet {
public:
    Packet() = default;

    Packet(struct timeval time, const std::vector<uint8_t>& data)
        : time(time), data(data) {}

    struct timeval time;
    std::vector<uint8_t> data;
};

#endif  // PACKET_H