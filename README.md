Project Title : Black Knight Garage.
A console based vehicle management system using C++.

Features:
1. Add Cars, Bikes and Trucks with validated input.
2. View all vehicles or filter by brand.
3. Save and load garage data from a file(vehicles.txt).
4. Dynamic Garage capacity that doubles when full.

How to compile and run:
g++ Garage.cpp -o garage
./garage

Usage:
7 (1-6 + 0) menu options:
0. Exit Program.
1. Show all vehicles
2. Add new Car.
3. Add new Bike.
4. Add new Truck.
5. Filter by Brand.
6. Save all current vehicles.

Input Format/Validation Rules:
1. Registration number must follow the format (ABC-1234), 3 uppercase, one dash and 4 digits.
2. Manufacturing year must be between 1980 and 2025.
3. Mileage must be between 0 - 100 Km/l.
4. Bike Engine cannot exceed 2500 CC.
5. Truck shipment capacity must be less than it's weight.

OOP Design note:
The Project is made using OOP principles.
1. Inheritance: Motorvehicle base class with car, bike and truck subclasses.
2. Polymorphism: Uses Virtual Functions.
3. Manual Dynamic memory management with proper destructor cleanup.
