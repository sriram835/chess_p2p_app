
/*

Files contains functions to get mapped port and ip and also contains the
function to communicate using p2p.

*/

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>

#include "connection.hpp"

#pragma pack(push, 1)
struct StunHeader {
  uint16_t type;
  uint16_t length;
  uint32_t magic_cookie;
  uint8_t transaction_id[12];
};
#pragma pack(pop)

MappedAddress get_mapped_address(int sock) {

  hostent *host = gethostbyname("stun.l.google.com");
  if (!host) {
    throw std::runtime_error("Failed to resolve STUN server");
  }

  sockaddr_in server{};
  server.sin_family = AF_INET;
  server.sin_port = htons(19302);
  memcpy(&server.sin_addr, host->h_addr, host->h_length);

  StunHeader req{};
  req.type = htons(0x0001);
  req.length = htons(0);
  req.magic_cookie = htonl(0x2112A442);

  std::random_device rd;
  for (auto &b : req.transaction_id) {
    b = rd();
  }

  if (sendto(sock, &req, sizeof(req), 0, (sockaddr *)&server, sizeof(server)) <
      0) {
    throw std::runtime_error("Failed to send STUN request");
  }

  uint8_t buffer[1024];

  sockaddr_in from{};
  socklen_t fromlen = sizeof(from);

  int received =
      recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&from, &fromlen);

  if (received < 0) {
    throw std::runtime_error("Failed to receive STUN response");
  }

  constexpr uint32_t magic_cookie = 0x2112A442;

  int pos = 20;

  while (pos + 4 <= received) {
    uint16_t attr_type = ntohs(*(uint16_t *)(buffer + pos));

    uint16_t attr_len = ntohs(*(uint16_t *)(buffer + pos + 2));

    if (attr_type == 0x0020) { // XOR-MAPPED-ADDRESS
      uint8_t family = buffer[pos + 5];

      if (family == 0x01) { // IPv4
        uint16_t xport;
        memcpy(&xport, buffer + pos + 6, sizeof(xport));

        uint16_t port = ntohs(xport) ^ (magic_cookie >> 16);

        uint32_t xaddr;
        memcpy(&xaddr, buffer + pos + 8, sizeof(xaddr));

        uint32_t ip = ntohl(xaddr) ^ magic_cookie;

        in_addr addr{};
        addr.s_addr = htonl(ip);

        return {inet_ntoa(addr), port};
      }
    }

    pos += 4 + attr_len;
    pos = (pos + 3) & ~3;
  }

  throw std::runtime_error("XOR-MAPPED-ADDRESS attribute not found");
}

void connection() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0) {
    perror("socket");
    return;
  }

  struct MappedAddress addr = get_mapped_address(sock);
  cout << addr.ip << " " << addr.port << "\n";

  addr = get_mapped_address(sock);
  cout << addr.ip << " " << addr.port << "\n";

  addr = get_mapped_address(sock);
  cout << addr.ip << " " << addr.port << "\n";
  close(sock);
}
