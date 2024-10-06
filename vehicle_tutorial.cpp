// Example of strategy design pattern

#include <bits/stdc++.h>
using namespace std;
class DriveStrategy
{
public:
    virtual void drive() = 0;
};

class NormalDriveStrategy : public DriveStrategy
{
public:
    void drive() override
    {
        cout << "Normal Drive Strategy" << endl;
    }
};

class SpeedDriveStrategy : public DriveStrategy
{
public:
    void drive() override
    {
        cout << "Speed Drive Strategy" << endl;
    }
};
class PowerDriveStrategy : public DriveStrategy
{
public:
    void drive() override
    {
        cout << "Power Drive Strategy" << endl;
    }
};
class Vehicle
{
private:
    DriveStrategy *driveobj;

public:
    // constructor injection
    Vehicle(DriveStrategy *obj) : driveobj(obj){}
    void drive()
    {
        driveobj->drive();
    }
};

class SportVehicle : public Vehicle
{
public : 
    SportVehicle() : Vehicle(new SpeedDriveStrategy()){}
};

class PassengerVehicle : public Vehicle
{
public : 
    PassengerVehicle() : Vehicle(new NormalDriveStrategy()){}
};

class OffroadVehicle : public Vehicle
{
public :
    OffroadVehicle() : Vehicle(new PowerDriveStrategy()){}
};




int main(){
    OffroadVehicle thar;
    PassengerVehicle i20;
    SportVehicle lambo;
    thar.drive();
    i20.drive();
    lambo.drive();
    return 0;
}