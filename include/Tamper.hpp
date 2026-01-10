#pragma once
#include "Disturbance.hpp"


namespace hm{
    /**
     * @brief Disturbance that randomly corrupts packet data.
     * The Tamper disturbance simulates data corruption by modifying
     * the packet payload with a given probability. When triggered,
     * a single character in the packet data is replaced with a
     * placeholder value.
     */
    template <typename T>
    class Tamper : public Disturbance<T>{
    private:
        double probability;     ///< Probability of data corruption (range: 0.0-1.0). 
    public:
        Tamper() : probability(0.0) {} ///< Default constructor
        static double badRange(double prob){
            if(prob < 0.0) return 0.0;
            if(prob > 1.0) return 1.0;
            return prob;
        }
        /**
         * @brief Constructor a Tamper disturbacne with given probability
         * @param prob  Probability that packet data will be corrupted
         */
        Tamper(double prob) : probability(badRange(prob)) {}
        /** 
         * @brief Applies data corruption to the packet with a given probability.
         *
         * The method generates a random value and, if it is below the configured
         * probability threshold, modifies the packet payload by replacing a
         * randomly selected character.
         *
         * @param pkt Reference to the packet potentially subjected to corruption.
         */
        void apply(Packet<T>& pkt) override{
            double los = (double)rand() / RAND_MAX;

            if (los< probability) {
                T corruptedData = pkt.getData();

                if(!corruptedData.empty()) {
                    int index = rand() % corruptedData.length();
                    corruptedData[index] = '#';
                }
                pkt.setData(corruptedData);
            }
        }
    };
}