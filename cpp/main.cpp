// Ride Sharing System - C++ Implementation
// Demonstrates Encapsulation, Inheritance, and Polymorphism

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class for all rides, holds shared ride data
class Ride
{
    // Protected so subclasses can access, but outside code cannot access it.
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance; // in miles
    double fareAmount;

public:
    // Constructor to initialize ride details
    Ride(int id, string pickup, string dropoff, double dist)
    {
        rideID = id;
        pickupLocation = pickup;
        dropoffLocation = dropoff;
        distance = dist;
        fareAmount = 0.0;
    }

    // Virtual so subclasses can override with their own pricing
    virtual double fare()
    {
        // Default rate: $5.00 per mile
        fareAmount = distance * 5.0;
        return fareAmount;
    }

    // Virtual so subclasses can customize the output
    virtual void rideDetails()
    {
        cout << "[Standard Ride]" << endl;
        cout << "Ride ID     : " << rideID << endl;
        cout << "Pickup      : " << pickupLocation << endl;
        cout << "Dropoff     : " << dropoffLocation << endl;
        cout << "Distance    : " << distance << " miles" << endl;
        cout << "Fare        : $" << fare() << endl;
    }

    // Getter for rideID (Encapsulation)
    int getRideID() { return rideID; }

    // Virtual destructor for safe cleanup through base pointers
    virtual ~Ride() {}
};

// Standard ride - inherits from Ride (Inheritance), charges $1.50/mile
class StandardRide : public Ride
{
public:
    // Calls the parent Ride constructor
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist)
    {
    }

    // Overrides fare() to charge $1.50 per mile (Polymorphism)
    double fare() override
    {
        fareAmount = distance * 10.00;
        return fareAmount;
    }

    void rideDetails() override
    {
        cout << "[Standard Ride]" << endl;
        cout << "Ride ID     : " << rideID << endl;
        cout << "Pickup      : " << pickupLocation << endl;
        cout << "Dropoff     : " << dropoffLocation << endl;
        cout << "Distance    : " << distance << " miles" << endl;
        cout << "Fare        : $" << fare() << endl;
    }
};

// Premium ride - inherits from Ride (Inheritance), charges $3.00/mile
class PremiumRide : public Ride
{
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist)
    {
    }

    // Overrides fare() to charge $3.00 per mile (Polymorphism)
    double fare() override
    {
        fareAmount = distance * 15.00;
        return fareAmount;
    }

    void rideDetails() override
    {
        cout << "[Premium Ride]" << endl;
        cout << "Ride ID     : " << rideID << endl;
        cout << "Pickup      : " << pickupLocation << endl;
        cout << "Dropoff     : " << dropoffLocation << endl;
        cout << "Distance    : " << distance << " miles" << endl;
        cout << "Fare        : $" << fare() << endl;
    }
};

// Driver class - private data accessible only through methods
class Driver
{
private:
    int driverID;
    string name;
    double rating;
    vector<Ride *> assignedRides;

public:
    Driver(int id, string driverName, double driverRating)
    {
        driverID = id;
        name = driverName;
        rating = driverRating;
    }

    // Adds a ride to the driver's list (controlled access)
    void addRide(Ride *ride)
    {
        assignedRides.push_back(ride);
    }

    // Displays driver info and completed rides
    void getDriverInfo()
    {
        cout << "Driver ID   : " << driverID << endl;
        cout << "Name        : " << name << endl;
        cout << "Rating      : " << rating << " / 5.0" << endl;
        cout << "Total Rides : " << assignedRides.size() << endl;
        cout << " " << endl;
        if (!assignedRides.empty())
        {
            cout << "----------- Completed Rides ------------" << endl;
            for (int i = 0; i < assignedRides.size(); i++)
            {
                // Calls the correct rideDetails() based on actual type (Polymorphism)
                assignedRides[i]->rideDetails();
                cout << endl;
            }
        }
        cout << " " << endl;
    }
};

// Rider class - tracks requested rides with private data (Encapsulation)
class Rider
{
private:
    int riderID;
    string name;
    vector<Ride *> requestedRides;

public:
    Rider(int id, string riderName)
    {
        riderID = id;
        name = riderName;
    }

    // Adds a ride to the rider's history
    void requestRide(Ride *ride)
    {
        requestedRides.push_back(ride);
        cout << name << " requested ride #" << ride->getRideID() << endl;
    }

    // Displays rider info and ride history
    void viewRides()
    {
        cout << "---------- Rider Information ----------" << endl;
        cout << "Rider ID    : " << riderID << endl;
        cout << "Name        : " << name << endl;
        cout << "Total Rides : " << requestedRides.size() << endl;
        cout << " " << endl;
        if (!requestedRides.empty())
        {
            cout << "---------- Ride History -----------" << endl;
            for (int i = 0; i < requestedRides.size(); i++)
            {
                // Each ride displays its own details based on type (Polymorphism)
                requestedRides[i]->rideDetails();
                cout << endl;
            }
        }
        cout << endl;
    }
};

// Main function - creates rides, drivers, and riders to test the system
int main()
{
    cout << "****** Ride Sharing System   ********" << endl;
    cout << " " << endl;

    // Create standard and premium rides for testing
    StandardRide *ride1 = new StandardRide(101, "Mass Ave", "Broadway", 5.0);
    StandardRide *ride2 = new StandardRide(102, "Cambridge", "Somerville", 3.2);
    PremiumRide *ride3 = new PremiumRide(201, "Logan Airport", "Downtown", 12.0);
    PremiumRide *ride4 = new PremiumRide(202, "South Boston", "Boston University", 7.5);
    Ride *ride5 = new Ride(301, "Back Bay", "Seaport", 10.0); // Base ride for testing

    vector<Ride *> allRides;
    allRides.push_back(ride1);
    allRides.push_back(ride2);
    allRides.push_back(ride3);
    allRides.push_back(ride4);
    allRides.push_back(ride5);

    for (int i = 0; i < allRides.size(); i++)
    {
        allRides[i]->rideDetails();
        cout << endl;
    }

    // Create a driver and rides
    cout << "-------------- Driver Info ---------------" << endl;
    Driver driver1(1, "Priyanka", 5.0);
    driver1.addRide(ride1);
    driver1.addRide(ride3);
    driver1.getDriverInfo();
    cout << endl;

    // Create a rider and request rides
    cout << "--------------- Rides Requested ---------------" << endl;
    Rider rider1(1, "Nick");
    rider1.requestRide(ride1);
    rider1.requestRide(ride3);
    rider1.requestRide(ride4);
    cout << endl;
    rider1.viewRides();

    // Free allocated memory
    delete ride1;
    delete ride2;
    delete ride3;
    delete ride4;
    delete ride5;

    return 0;
}
