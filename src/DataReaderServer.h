#ifndef SECONDYEARPROJECT_BIU_DATAREADERSERVER_H
#define SECONDYEARPROJECT_BIU_DATAREADERSERVER_H

#include "thread"
#include "map"
#include "vector"
#define PARAMETERS_SIZE 23
std::vector<std::string> paths{"/instrumentation/airspeed-indicator/indicated-speed-kt",
                               "/instrumentation/altimeter/indicated-altitude-ft",
                               "/instrumentation/altimeter/pressure-alt-ft",
                               "/instrumentation/attitude-indicator/indicated-pitch-deg",
                               "/instrumentation/attitude-indicator/indicated-roll-deg",
                               "/instrumentation/attitude-indicator/internal-pitch-deg",
                               "/instrumentation/attitude-indicator/internal-roll-deg",
                               "/instrumentation/encoder/indicated-altitude-ft",
                               "/instrumentation/encoder/pressure-alt-ft",
                               "/instrumentation/gps/indicated-altitude-ft",
                               "/instrumentation/gps/indicated-ground-speed-kt",
                               "/instrumentation/gps/indicated-vertical-speed",
                               "/instrumentation/heading-indicator/indicated-heading-deg",
                               "/instrumentation/magnetic-compass/indicated-heading-deg",
                               "/instrumentation/slip-skid-ball/indicated-slip-skid",
                               "/instrumentation/turn-indicator/indicated-turn-rate",
                               "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                               "/controls/flight/aileron",
                               "/controls/flight/elevator",
                               "/controls/flight/rudder",
                               "/controls/flight/flaps",
                               "/controls/engines/engine/throttle",
                               "/engines/engine/rpm"};
class DataReaderServer {
    /**
     * @return vector of strings, each from the buffer
     */
    static std::vector<std::string> splitByComma(char* buffer);

    /**
     * Updates the Paths table
     * @param vector vector
     */
    static void updatePathsTable(std::vector<std::string> vector);

    /**
     * Updates symbol table
     */
    static void updateSymbolTable();
public:
    /**
     * OPens the server
     * @param port port
     * @param hz hz
     */
    static void openServer(int port, int hz);
};


#endif //SECONDYEARPROJECT_BIU_DATAREADERSERVER_H