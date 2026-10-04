#include "../include/RedisServer.h"
#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {
  int port = 6379;
  if (argc >= 2)
    port = std::stoi(argv[1]);
  RedisServer server(port);

  // Background persistence : dump the database eveery 300 sec (5*60 save
  // database)
  std::thread persistenceThread([]() {
    while (true) {
      std::this_thread::sleep_for(std::chrono::seconds(300));
      //  dump the database
    }
  });
  persistenceThread.detach();
  server.run();

  return 0;
}