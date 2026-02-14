"Ride Sharing System - Smalltalk Implementation"

" Base class for all rides, holds shared ride data "
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance fareAmount |

    initialize [
        fareAmount := 0.0.
    ]

    "  Ride details setter "
    setRideID: anID pickup: aPickup dropoff: aDropoff distance: aDist [
        rideID := anID.
        pickupLocation := aPickup.
        dropoffLocation := aDropoff.
        distance := aDist.
    ]

    " Getter for rideID returns the ride's unique identifier "
    getRideID [
        ^ rideID.
    ]

    " Default fare: $5.00 per mile. Subclasses override this (Polymorphism) "
    fare [
        fareAmount := distance * 5.0.
        ^ fareAmount.
    ]

    " Displays ride details "
    rideDetails [
        Transcript show: 'Ride ID: ', rideID printString.
        Transcript nl.
        Transcript show: 'Pickup: ', pickupLocation.
        Transcript nl.
        Transcript show: 'Dropoff: ', dropoffLocation.
        Transcript nl.
        Transcript show: 'Distance: ', distance printString, ' miles'.
        Transcript nl.
        Transcript show: 'Fare: $', self fare printString.
        Transcript nl.
    ]
]

" Standard ride - inherits from Ride , charges $10.00/mile "
Ride subclass: StandardRide [
    fare [
        fareAmount := distance * 10.00.
        ^ fareAmount.
    ]

    " Prints label then use to parent for details "
    rideDetails [
        Transcript show: '[Standard Ride]'.
        Transcript nl.
        super rideDetails.
    ]
]

" Premium ride"
Ride subclass: PremiumRide [

    " Overrides fare to charge $15.00 per mile "
    fare [
        fareAmount := distance * 15.00.
        ^ fareAmount.
    ]

    rideDetails [
        Transcript show: '[Premium Ride]'.
        Transcript nl.
        super rideDetails.
    ]
]

" Driver class - private data "
Object subclass: Driver [
    | driverID name rating assignedRides |

    " Initializes an empty list "
    initialize [
        assignedRides := OrderedCollection new.
    ]

    " driver details "
    setDriverID: anID name: aName rating: aRating [
        driverID := anID.
        name := aName.
        rating := aRating.
    ]

    " Adds a ride to the drivers "
    addRide: aRide [
        assignedRides add: aRide.
    ]

    " Displays driver completed rides "
    getDriverInfo [
        Transcript show: 'Driver ID: ', driverID printString.
        Transcript nl.
        Transcript show: 'Name: ', name.
        Transcript nl.
        Transcript show: 'Rating: ', rating printString, ' / 5.0'.
        Transcript nl.
        Transcript show: 'Total Rides: ', assignedRides size printString.
        Transcript nl.
        Transcript show: ' '.
        assignedRides isEmpty ifFalse: [
            Transcript show: '---------- Completed Rides ------------'.
            Transcript nl.
            assignedRides do: [ :eachRide |
                eachRide rideDetails.
                Transcript nl.
            ].
        ].
        Transcript nl.
    ]
]

" Rider class"
Object subclass: Rider [
    | riderID name requestedRides |

    " Initializes with an empty ride list "
    initialize [
        requestedRides := OrderedCollection new.
    ]

    setRiderID: anID name: aName [
        riderID := anID.
        name := aName.
    ]

    " Adds a ride to the rider's history "
    requestRide: aRide [
        requestedRides add: aRide.
        Transcript show: name, ' requested ride #', aRide getRideID printString.
        Transcript nl.
    ]

    " Displays rider info and ride history "
    viewRides [
        Transcript show: '------------ Rider Info ------------ '.
        Transcript nl.
        Transcript show: 'Rider ID: ', riderID printString.
        Transcript nl.
        Transcript show: 'Name: ', name.
        Transcript nl.
        Transcript show: 'Total Rides: ', requestedRides size printString.
        Transcript nl.
        Transcript nl.
        requestedRides isEmpty ifFalse: [
            Transcript show: '----------- Ride History -------------'.
            Transcript nl.
            "  displays details"
            requestedRides do: [ :eachRide |
                eachRide rideDetails.
                Transcript nl.
            ].
        ].
        Transcript nl.
    ]
]

" Main - System Functionality Demonstration "

| ride1 ride2 ride3 ride4 ride5 allRides driver1 rider1 |

Transcript show: '*************  Ride Sharing System   ***************'.
Transcript nl.

" Creating standard and premium rides "
ride1 := StandardRide new.
ride1 setRideID: 101 pickup: 'Mass Ave' dropoff: 'Cambridge' distance: 5.0.

ride2 := StandardRide new.
ride2 setRideID: 102 pickup: 'Brattle Drive' dropoff: 'Malden' distance: 3.2.

ride3 := PremiumRide new.
ride3 setRideID: 201 pickup: 'Logan Airport' dropoff: 'Boston University' distance: 12.0.

ride4 := PremiumRide new.
ride4 setRideID: 202 pickup: 'South Boston' dropoff: 'Wentworth Institute' distance: 7.5.

" Base ride for testing "
ride5 := Ride new.
ride5 setRideID: 301 pickup: 'Prudential' dropoff: 'Mass Ave' distance: 10.0.

Transcript nl.

allRides := OrderedCollection new.
allRides add: ride1.
allRides add: ride2.
allRides add: ride3.
allRides add: ride4.
allRides add: ride5.

allRides do: [ :eachRide |
    eachRide rideDetails.
    Transcript nl.
].

" Driver and rides "
Transcript show: '------------ Driver Info --------------'.
Transcript nl.
driver1 := Driver new.
driver1 setDriverID: 1 name: 'Priyanka' rating: 5.0.
driver1 addRide: ride1.
driver1 addRide: ride3.
driver1 getDriverInfo.

" Rider and its rides "
Transcript show: '------------- Ride Requested -------------'.
Transcript nl.
rider1 := Rider new.
rider1 setRiderID: 1 name: 'Nick'.
rider1 requestRide: ride1.
rider1 requestRide: ride3.
rider1 requestRide: ride4.
Transcript nl.
rider1 viewRides.
