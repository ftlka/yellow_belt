#include "bus_manager.h"

using namespace std;


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (auto stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse resp;
    if (stops_to_buses.count(stop) == 0) {
        resp.buses = {};
        return resp;
    }
    resp.buses = stops_to_buses.at(stop);
    return resp;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse resp;
    resp.bus = bus;
    if (buses_to_stops.count(bus) == 0) {
        resp.stops = {};
        return resp;
    }
    resp.stops = buses_to_stops.at(bus);
    resp.stops_to_buses = stops_to_buses;
    return resp;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse resp;
    resp.buses_to_stops = buses_to_stops;
    return resp;
}
