#pragma once
#include "Disturbance.hpp"

namespace hm{
template <typename T>
/**
 * @class PacketLost
 * @brief This class represent lost packet
 */
class PacketLost : public Disturbance<T> {
    private:
        double probability; ///< probability of drawing a lost packet
    public:
        PacketLost() : probability(0.0) {} ///< Default constructor
        static double badRange(double prob){
            if(prob < 0.0) return 0.0;
            if(prob > 1.0) return 1.0;
            return prob;
        }
        PacketLost(double prob) : probability(badRange(prob)) {} 
        /**
         * @brief Applies a lost to the packet
         * The metod introdues a lost packet. The value of "fortune"
         * is randomly selected and if it is smaller than 
         * probability it would be marked as lost.
         * 
         * @param pkt Reference to the packet to which the lost is applied
         */
        void apply(Packet<T>& pkt) override{
            double fortune = (double)rand()/RAND_MAX;

            if(fortune < probability){
                pkt.markAsLost();
            }
        }
};
}