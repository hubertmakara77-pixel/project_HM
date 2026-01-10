#pragma once 
#include <memory>
#include <vector>
#include "Disturbance.hpp"

namespace hm{
    /**
     * @class LinkEmulator
     * @brief class simulate network link (cable). 
     * @tparam T is a type of data 
     * it works like a container for Disturbance 
     * it passes it sequentially through all detected interference
     */
    template <typename T>
    class LinkEmulator{
    private:
        /**
         * @ brief List of active disturbances
         * use std::shared_ptr to store polyorphic object 
         * (e.g., Delay, PacetLost) and automatically manage memory
        */
        std::vector<std::shared_ptr<Disturbance<T>>> effects;
    public:
        /**
         * @brief Adds a disturbance effect to the link emulator
         * This operator appends the given disturbance effect to the internal
         * list of effects applied by the link emulator.
         * @param effect Shared pointer to a disturbacne effect to be added.
         * @return Reference to the current LinkEmulator instance, allowing 
         * operator chaining
         */
        LinkEmulator& operator+=(std::shared_ptr<Disturbance<T>> effect) {
            effects.push_back(effect);
            return *this;
        }
        /**
         * @brief Sends a packet through the link emulator
         * The packet is processed sequentially by all registered disturbance
         * effects before being transmitted. Each effect may modify the packet
         * in place.
         * @param pkt Reference to the packet to be transmitted.
         * @return true if the packet was successfully processed and sent.
         */
        bool send(Packet<T>& pkt) {
            for (auto& effect : effects) {
                effect->apply(pkt);
                if (pkt.isLost()) {
                    return false;
                }
            }
        return true;
    }
    };
}
