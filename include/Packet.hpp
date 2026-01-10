#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

namespace hm
{
    /**
     * @class RawFrame represent a Raw Frame with only frame ID and time
     */
    class RawFrame
    {
    protected:
        int frameId;            ///< unique frame ID 
        std::time_t timeStamp;  ///< Time of create a frame
    public:
    /**
     * @brief Default constructor 
     * initialization random frame ID and set current time
     */
        RawFrame()
        {
            frameId = std::rand();
            timeStamp = std::time(nullptr);
        }
        /**
         * @brief fetches ID frame
         * @return unique ID frame (int)
         */
        int getId() const { return frameId; }
        /**
         * @brief fetches current time 
         * @return time as std::time_t
         */
        std::time_t getTime() const { return timeStamp; }
        RawFrame(int id, std::time_t ts) : frameId(id), timeStamp(ts) {} ///< explicitly defaulted default constructor
    };
    /**
     * @class IPPacket
     * @brief class represent packet IP
     * inherits from class RawFrame and add information about 
     * IP addreses
     */
    class IPPacket : public RawFrame
    {
    protected:
        std::string sourceIP;       ///< sender's adress
        std::string destinationIP;  ///< recipient's address
    public:
        IPPacket() : RawFrame(), sourceIP("0.0.0.0"), destinationIP("0.0.0.0") {} ///< explicitly defaulted default constructor 
        /**
        * Constructor of IPPacket
        * @param source sender's adress IP (string)
        * @param destination recipient's address IP (string)
        */
        IPPacket(std::string source, std::string destination) : RawFrame(), sourceIP(source), destinationIP(destination) {}
        /**
         * @brief sender's recipient's address
         * @return std::string with adress IP
         */
        std::string getSourceIP() const { return sourceIP; }
        /**
         * @briefreturn recipient's address
         * @return std::string with adress IP
         */
        std::string getDestinationIP() const { return destinationIP; }
    };
    /**
     * @class Packet
     * @brief template class of full network packet
     * @tparam T type of data transfered in packet (Payload)
     * This class expands IPPacket for ports, payload and simulation flags
     * (lost, delay, corrupted, duplicate )
     */
    template <typename T>
    class Packet : public IPPacket
    {
    private:
        int sourcePort;         ///< sender's port
        int destinationPort;    ///< recipient's port

        T payload;              ///< transfered data

        bool lost;              ///< flag: has the packet been lost?
        int delayMs;            ///< value of delay in milliseconds
        bool corrupted;         ///< flag: has the data been corrupted? 
        bool duplicate;         ///< flag: has the packet been duplicated?

    public:
    /**
     * @brief main packet constructor
     * @param source sender's IP adress
     * @param destination recipient's IP adress
     * @param sPort sender's port
     * @param dPort recipient's port
     * @param data Data to send
     */
        Packet(std::string source, std::string destination, int sPort, int dPort, T data) : IPPacket(source, destination), sourcePort(sPort), destinationPort(dPort), payload(data), lost(false), delayMs(0), corrupted(false), duplicate(false) {}
        Packet() :
            IPPacket(),
            sourcePort(0),
            destinationPort(0),
            payload{},
            lost(false),
            delayMs(0),
            corrupted(false),
            duplicate(false) {} ///< Default constructor
        /**
         * @brief checks if packet is marked as lost
         * @return true if lost, false if arrived
         */
        bool isLost() const { return lost; }
        /**
         * @brief marked packet as lost
         */
        void markAsLost() { lost = true; }
        /**
         * @brief gets delay
         * @return delay in miliseconds
         */
        int getDelay() const { return delayMs; }
        /**
         * @brief add delay in miliseconds
         * @param ms number of milisecond to add
         */
        void addDelay(int ms) { delayMs += ms; }
        /**
         * @brief checks if packet is marked as corrupted
         * @return true if corrupted
         */
        bool isCorrupted() const { return corrupted; }
        /**
         * @brief marked packet as corrupted
         */
        void markCorrupted() { corrupted = true; }
        /**
         * @brief checks if packet is duplicate
         * @return true if copy
         */
        bool isDuplicate() const { return duplicate; }
        /**
         * @brief marked packet as duplciate
         */
        void markDuplicate() {duplicate = true;}
        /**
         * @brief gets data from packet
         * @return copy of data
         */
        T getData() const { return payload; }
        /**
         * @brief set new data
         * @param newData new data type T
         */
        void setData(T newData) { payload = newData; }
        /**
         * @brief comparison operator  
         */ 
        bool operator==(const Packet<T> &other) const
        {
            return this->payload == other.payload;
        }
        /**
         * @brief operator to write out a packet
         * allows to use std::cout << packet.
         * Also write out the status of the flag
         * (LOST,CORRUPTED) or Dleay and copy
         * @param os output stream
         * @param p object of the packet
         * @return reference to packet
         */
        friend std::ostream &operator<<(std::ostream &os, const Packet<T> &p)
        {
            os << "[ID:" << p.getId() << "] "
               << p.getSourceIP() << " -> "
               << p.getDestinationIP() << ":" << p.destinationPort
               << " | Data: " << p.payload;
               if (p.lost){
                os << " [LOST]";
               }else{
                os<<" [DELIVERED]";
               }
            if (p.delayMs > 0)
            {
                os << "[Delay:" << p.delayMs << "ms]";
            }
            if (p.corrupted)
                os << " [CORRUPTED]";
            if (p.duplicate && !p.lost){
                os << "\n";
                os << "[ID:" << p.getId() << "] "
               << p.getSourceIP() << " -> "
               << p.getDestinationIP() << ":" << p.destinationPort
               << " | Data: " << p.payload  << "(Copy)";
            }
            return os;
        }
    };
}
