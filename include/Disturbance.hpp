#pragma once
#include "Packet.hpp"

namespace hm{
    /**
     * @class Disturbance
     * @brief abstract class which represent any disturbance
     * @tparam T type of data sending in packet
     * This is a polymorphic interface. Each inheriting class
     * must implement the apply() method. This allows LinkEmulator to store 
     * a collection of different disruptions in a single
     */
    template < typename T>
    class Disturbance {
    protected:
        Disturbance() = default; ///< explicitly defaulted default constructor
        explicit Disturbance(int /*unused*/) {}
    public:
        /**
         * @brief virtual destructor
         * Necessary for polymorphism to correct delete derived objects
         * via a pointer to base class
        */
        virtual ~Disturbance() = default;
        /**
         * @brief A purely virtual method that applies a distruption 
         * to the package.
         * @param pkt A reference to the packet to be modified
         * @note This method is virtual, it must be override
        */
        virtual void apply(Packet<T>& pkt) = 0;
    };
}