#pragma once
#include "Disturbance.hpp"
#include <algorithm>

namespace hm
{
    template <typename T>
    /**
     * @class Delay
     * @brief this class draws number between two ints
     * and it represents delay
     */
    class Delay: public Disturbance<T>{
    private:
        int minMs;  ///< minimum delay
        int maxMs;  ///< maximum delay

    public:
        /**
         * @brief Constructor of delay with one number
         * protection against specifying one variable.
         * If user specifying only one number, class will choose this number
         * @param fixedDelay number of delay in miliseconds (int)
         */
        Delay(int fixedDelay) : minMs(fixedDelay) , maxMs(fixedDelay){
            validate();
        }
        /**
         * @brief Constructor of delay with two numbers
         * @param min minimum delay in milliseconds
         * @param max maximum delay in milliseconds
         */
        Delay(int min, int max) : minMs(min), maxMs(max){
            validate();
        }
        /**
         * @brief set the value ascending
         * if user set first greater value 
         * it will swap it 
         */
        void validate() {
            if(minMs<0 || maxMs<0) {
                minMs = 0;
                maxMs = 0;
            }
            if(minMs > maxMs) std::swap(minMs, maxMs);
        } 
        
        /**
         * @brief add delay to packet
         *  The method introduces a transmission delay to the packet. The delay
         * value is either fixed or randomly selected from the range
         * [minMs, maxMs], depending on the configuration.
         * @param pkt Reference to tha packet to which the delay is applied.
         */
        void apply(Packet<T>& pkt) override{
            int currentDelay = 0;
            if(minMs == maxMs){
                currentDelay = minMs;
            }else{
                currentDelay = minMs + (std::rand() % (maxMs - minMs + 1));
            }
            pkt.addDelay(currentDelay);
        }
    };
    
    
} // namespace hm


