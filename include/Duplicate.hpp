#pragma once
#include "Disturbance.hpp"
#include <stdexcept>

namespace hm{
    /**
     * @class Duplicate
     * This class can duplicate packet depending of probability
     */
    template <typename T>
    class Duplicate : public Disturbance<T> {
    private:    
        double probability; ///<  probability of drawing a duplicate
    public:
        Duplicate() : probability(0.0) {} ///< Default constructor
        static double badRange(double prob){
            if(prob < 0.0) return 0.0;
            if(prob > 1.0) return 1.0;
            return prob;
        }
        explicit Duplicate(double prob) : probability(badRange(prob)) {
        }
        /**
         * @brief Applies a duplicate to the packet
         * The method introduces a duplicate. The value of "los"
         * is randomly selected and if it is smaller than 
         * probability it would be marked as duplicate.
         * 
         * @param pkt Reference to the packet to which the duplicate is applied
         */
        void apply(Packet<T>& pkt) override {
            double los = (double)rand() / RAND_MAX;
            if(los<probability){
                pkt.markDuplicate();
            }
        }
    };
}