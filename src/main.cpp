#include "./Packet.hpp"
#include "./Delay.hpp"
#include "./Tamper.hpp"
#include "./LinkEmulator.hpp"
#include "./PacketLost.hpp"
#include "./Duplicate.hpp"
#include "./Throttle.hpp"
#include <ctime>
using DataType = std::string;
using NetLink = hm::LinkEmulator<DataType>;
using MyPacket = hm::Packet<DataType>;
using Lost = hm::PacketLost<DataType>;
using Delay = hm::Delay<DataType>;
using Tamper = hm::Tamper<DataType>;
using Duplicate = hm::Duplicate<DataType>;
using Throttle = hm::Throttle<DataType>;
int main(){
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    NetLink network;
    MyPacket p("192.168.1.10", "8.8.8.8", 12345, 80, "veryLongText"); 
    network += std::make_shared<Throttle>(10);
    network += std::make_shared<Delay>(100, 300);
    network += std::make_shared<Lost>(0.5);
    network += std::make_shared<Tamper>(0.5);
    network += std::make_shared<Duplicate>(1.4);
    
    
    network.send(p);

    std::cout << p << "\n";


}