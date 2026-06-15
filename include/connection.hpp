#pragma once

#include "chess_board.hpp"
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <random>
#include <sys/socket.h>
#include <unistd.h>

struct MappedAddress {
  std::string ip;
  uint16_t port;
};

MappedAddress get_mapped_address(int sock);
void connection();
