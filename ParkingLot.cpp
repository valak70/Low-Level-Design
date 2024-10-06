// Not Thread Safe

#include <bits/stdc++.h>
using namespace std;

enum class VehicleType
{
    Car,
    Bike,
    Truck,
};

// Array to map enum class values to string
const string VehicleTypeStrings[] = {"Car", "Bike", "Truck"};

// Utility to convert enum class to string
string vehicleTypeToString(VehicleType type)
{
    return VehicleTypeStrings[static_cast<int>(type)];
}

class Vehicle
{
protected:
    string license_plate;
    VehicleType type;

public:
    Vehicle(string license_plate, VehicleType type) : license_plate(license_plate), type(type)
    {
        cout << "This is a " + vehicleTypeToString(type) << endl;
    }
    VehicleType getType()
    {
        return type;
    }
};

class Car : public Vehicle
{
public:
    Car(string license_plate) : Vehicle(license_plate, VehicleType::Car) {}
};

class Bike : public Vehicle
{
public:
    Bike(string license_plate) : Vehicle(license_plate, VehicleType::Bike) {}
};

class Truck : public Vehicle
{
public:
    Truck(string license_plate) : Vehicle(license_plate, VehicleType::Truck) {}
};

class ParkingSpot
{
private:
    const int spotNumber;
    const VehicleType spotType;
    Vehicle *parkedVehicle;

public:
    ParkingSpot(int spotNumber, VehicleType type) : spotNumber(spotNumber), spotType(type), parkedVehicle(nullptr) {}
    bool isAvailable()
    {
        return this->parkedVehicle == NULL;
    }
    bool park(Vehicle *vehicle)
    {
        if (!this->isAvailable())
            return false;
        if (vehicle->getType() == spotType)
        {
            parkedVehicle = vehicle;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool release(Vehicle *vehicle)
    {
        if (parkedVehicle == vehicle)
        {
            parkedVehicle = NULL;
            return true;
        }
        return false;
    }
    Vehicle *getParkedVehicle()
    {
        return parkedVehicle;
    }
    int getSpotNumber()
    {
        return spotNumber;
    }
    VehicleType getSpotType()
    {
        return spotType;
    }
};

class Level
{
private:
    int floorNumber;
    list<ParkingSpot *> parkingSpots;

public:
    Level(int level, int spots)
    {
        floorNumber = level;
        int numBikes = spots / 2;
        int numTrucks = spots / 10;
        int numCars = spots - (numBikes + numTrucks);
        int i = 1;
        for (; i <= numBikes; i++)
        {
            parkingSpots.push_back(new ParkingSpot(i, VehicleType::Bike));
        }
        for (; i <= numBikes + numCars; i++)
        {
            parkingSpots.push_back(new ParkingSpot(i, VehicleType::Car));
        }
        for (; i <= spots; i++)
        {
            parkingSpots.push_back(new ParkingSpot(i, VehicleType::Truck));
        }
    }
    Level(int level, int numBikes, int numCars, int numTrucks)
    {
        floorNumber = level;
        int spots = numBikes + numCars + numTrucks;
        int i = 1;
        for (; i <= numBikes; i++)
        {
            parkingSpots.push_back(new ParkingSpot(i, VehicleType::Bike));
        }
        for (; i <= numBikes + numCars; i++)
        {
            parkingSpots.push_back(new ParkingSpot(i, VehicleType::Car));
        }
        for (; i <= spots; i++)
        {
            parkingSpots.push_back(new ParkingSpot(i, VehicleType::Truck));
        }
    }
    int getTotalspots()
    {
        return parkingSpots.size();
    }
    bool parkVehicle(Vehicle *vehicle)
    {
        for (auto spot : parkingSpots)
        {
            if (spot->park(vehicle))
                return true;
        }
        return false;
    }
    bool releaseVehicle(Vehicle *vehicle)
    {
        for (auto spot : parkingSpots)
        {
            if (spot->release(vehicle))
                return true;
        }
        return false;
    }
    void realtimeStatus()
    {
        cout << "Level : " + to_string(floorNumber) << endl;
        cout << "Total number of Parking spots: " + to_string(getTotalspots()) << endl;
        for (auto spot : parkingSpots)
        {
            cout << "Spot " + to_string(spot->getSpotNumber()) + " of type " + vehicleTypeToString(spot->getSpotType())
                 << (spot->isAvailable() ? " is free." : " is Occupied.") << endl;
        }
    }
};

class ParkingLot
{
private:
    list<Level *> levels;
    static ParkingLot *instance;
    ParkingLot() {}

public:
    // Delete copy constructor and assignment operator
    ParkingLot(const ParkingLot &) = delete;
    ParkingLot &operator=(const ParkingLot &) = delete;

    // Static method to provide access to the singleton instance
    static ParkingLot *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new ParkingLot();
        }
        return instance;
    }
    void addLevel(Level *level)
    {
        levels.push_back(level);
    }
    void parkVehicle(Vehicle *vehicle)
    {
        for (auto level : levels)
        {
            if (level->parkVehicle(vehicle))
            {
                cout << "Vehicle Parked Successfully." << endl;
                return;
            }
        }
        cout << "Could not park." << endl;
    }

    void releaseVehicle(Vehicle *vehicle)
    {
        for (auto level : levels)
        {
            if (level->releaseVehicle(vehicle))
            {
                cout << "Vehicle Released Successfully." << endl;
                return;
            }
        }
        cout << "Could not find Vehicle." << endl;
    }

    void displayAvailability()
    {
        for (auto level : levels)
        {
            level->realtimeStatus();
        }
    }
};

ParkingLot *ParkingLot ::instance = NULL;

int main() {
    // Get the singleton instance of ParkingLot
    ParkingLot* parkingLot = ParkingLot::getInstance();

    // Add levels to the parking lot
    Level* level1 = new Level(1, 10);  // 10 spots (default distribution of bikes, cars, and trucks)
    Level* level2 = new Level(2, 5, 3, 2);  // Custom distribution: 5 bike spots, 3 car spots, and 2 truck spots

    parkingLot->addLevel(level1);
    parkingLot->addLevel(level2);

    // Create vehicles
    Vehicle* car1 = new Car("CAR123");
    Vehicle* bike1 = new Bike("BIKE456");
    Vehicle* truck1 = new Truck("TRUCK789");

    // Park vehicles
    parkingLot->parkVehicle(car1);  // Should find a car spot
    parkingLot->parkVehicle(bike1);  // Should find a bike spot
    parkingLot->parkVehicle(truck1);  // Should find a truck spot

    // Try parking a car again (to test availability)
    Vehicle* car2 = new Car("CAR234");
    parkingLot->parkVehicle(car2);  // Should find the next available car spot

    // Display parking availability
    parkingLot->displayAvailability();

    // Release a vehicle
    parkingLot->releaseVehicle(car1);  // Should release car1 from its spot

    // Display parking availability after releasing
    parkingLot->displayAvailability();

    return 0;
}

