#pragma once

#include <string>
#include <map>
#include <vector>
#include <ostream>

using namespace std;


struct BusesForStopResponse {
    vector<string> buses;
};

struct StopsForBusResponse {
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);
