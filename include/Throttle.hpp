#pragma once
#include "Disturbance.hpp"  
#include <string>
#include <algorithm>

namespace hm{
    /**
     * @brief Disturbance that simulates bandwidth throttling.
     *
     * The throttle disturbance models limited transmission bandwidth by
     * introducing a delay proportional to the packet size and the configured
     * transfer speed.
     *
     * @tparam T Type of the packet payload.
    */
    template <typename T>
    class Throttle : public Disturbance<T> {
    private: 
        int speedBytesPerMS;    ///< maximum transfer speed in bytes per milliseconds.
    public:
        Throttle() : speedBytesPerMS(1) {} ///< Default constructor
        /**
         * @brief Constructs a throttle disturbance with given transfer speed.
         * If the provided speed is less than or equal to zero, a minimum
         * transfer speed of one byte per millisecond is enforced.
         * @param speed Tranfser speed in bytes per milliseconds.
         */
        Throttle(int speed) : speedBytesPerMS(speed){
            if(speedBytesPerMS <= 0) speedBytesPerMS = 1;
        }
        /**
         * @brief Applies bandwidth-based delay to the packet
         * The metod computes the transmission delay based on the packet 
         * payload size and the configured transfer speed. The resulting 
         * delay is added to the packet.
         * @param pkt reference to the packet subjected to throttling
         */
        void apply(Packet<T>& pkt) override {
            T data = pkt.getData();

            long long size = data.size();

            int transferDelay = (int)(size / speedBytesPerMS);

            if(transferDelay > 0){
                pkt.addDelay(transferDelay);
            }
        }
    };
}