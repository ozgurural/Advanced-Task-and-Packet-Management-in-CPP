#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include <cstdint>

template <typename T>
class Packet {
public:
    Packet(struct timeval time, const T& data) : time(time), data(data) {}

    struct timeval time;
    T data;
};

#endif // PACKET_H