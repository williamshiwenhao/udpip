//
// Created by shiwenhao on 2019/10/9.
//
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <memory>
#include <arpa/inet.h>

#include "udp.h"
#include "json.h"

const char kConfigFile[] = "server_config.json";

void Server(uint16_t port) {
  UdpSocket server;
  if (server.Init()) {
    fprintf(stderr, "[Error] Socket init error\n");
    return;
  }
  if (server.Bind(port)) {
    fprintf(stderr, "[Error] Socket bind port error\n");
    return;
  }
  sockaddr_in addr{};
  memset(&addr, 0, sizeof(addr));
  uint8_t buff[16000];
  char str_ip[20];
  while (true) {
    int len = server.RecvFrom((char *) buff, sizeof(buff), &addr);
    if (len < 0) {
      fprintf(stderr, "[Warning] Receive error");
      break;
    }
    inet_ntop(AF_INET, &addr.sin_addr, str_ip, sizeof(str_ip));
    uint16_t port = ntohs(addr.sin_port);
    printf("Receive a packet: src_ip: %s, src_port %u\n", str_ip, port);
  }
}

int main() {
  std::ifstream fd(kConfigFile, std::ifstream::in);
  Json::Value root;
  if (!fd) {
    fprintf(stderr, "[Error] Server error, cannot open config file\n");
    return -1;
  }
  try {
    fd >> root;
  }
  catch (...) {
    fprintf(stderr, "[Error] Wrong conifg file, config file must be json");
    return -1;
  }
  unsigned listen_port = root["port"].asUInt();
  printf("----------------------------------\n");
  printf("|UDP Server\n");
  printf("----------------------------------\n");
  printf("[Port] %u\n", listen_port);
  printf("----------------------------------\n");
  Server(listen_port);
  return 0;
}
