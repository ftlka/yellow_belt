#include "responses.h"

using namespace std;


ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus";
    } else {
        for (const string& stop : r.stops) {
            os << "Stop " << stop << ": ";
            if (r.stops_to_buses.at(stop).size() == 1) {
                os << "no interchange";
            } else {
                for (const string& other_bus : r.stops_to_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}


ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No buses";
    } else {
        for (const auto& bus_item : r.buses_to_stops) {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}
