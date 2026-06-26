CREATE TABLE Drivers (
    DriverID INTEGER PRIMARY KEY AUTOINCREMENT,
    TruckID INTEGER NOT NULL,
    FirstName TEXT NOT NULL,
    LastName TEXT NOT NULL,
    FOREIGN KEY (TruckID) REFERENCES Trucks(TruckID)
);
CREATE TABLE Trucks (
    TruckID INTEGER PRIMARY KEY AUTOINCREMENT,
    UnitNumber TEXT NOT NULL,
    CapacityLbs INTEGER NOT NULL
);
CREATE TABLE Customers (
    CustomerID INTEGER PRIMARY KEY AUTOINCREMENT,
    CompanyName TEXT NOT NULL
);
CREATE TABLE Shipments (
    ShipmentID INTEGER PRIMARY KEY AUTOINCREMENT,
    CustomerID INTEGER NOT NULL,
    TruckID INTEGER NOT NULL,
    Revenue INTEGER NOT NULL,
    Status TEXT NOT NULL CHECK(Status IN ('Delivered', 'Enroute', 'Delayed', 'Loading')),
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID),
    FOREIGN KEY (TruckID) REFERENCES Trucks(TruckID)
);
CREATE TABLE Packages (
    PackageID INTEGER PRIMARY KEY AUTOINCREMENT,
    ShipmentID INTEGER NOT NULL,
    Item TEXT NOT NULL,
    Weight INTEGER NOT NULL,
    FOREIGN KEY (ShipmentID) REFERENCES Shipments(ShipmentID)
);
CREATE TABLE Maintenance (
    MaintenanceID INTEGER PRIMARY KEY AUTOINCREMENT,
    TruckID INTEGER NOT NULL,
    Cost INTEGER NOT NULL,
    FOREIGN KEY (TruckID) REFERENCES Trucks(TruckID)
);

INSERT INTO Drivers (TruckID, FirstName, LastName)
VALUES 
(1, "Jake", "Wilson"),
(2, "Sarah", "Lopez"),
(3, "Micheal", "Brown"),
(4, "Emma", "Davis"),
(0, "Noah", "Garcia");

INSERT INTO Trucks (UnitNumber, CapacityLbs)
VALUES
("TRK-101", 40000),
("TRK-102", 45000),
("TRK-103", 35000),
("TRK-104", 50000);

INSERT INTO Customers (CompanyName)
VALUES
("Fresh Foods Inc."),
("Central Electronics"),
("Florida Furniture"),
("Southern Supplies");

INSERT INTO Shipments (CustomerID, TruckID, Revenue, Status)
VALUES
(1, 1, 1000, 'Delivered'),
(2, 1, 9200, 'Loading'),
(1, 2, 5000, 'Delivered'),
(3, 3, 2000, 'Enroute'),
(4, 4, 2500, 'Delayed');

INSERT INTO Packages (ShipmentID, Item, Weight)
VALUES
(1, 'Apples', 800),
(2, 'Oranges', 700),
(3, 'Peaches', 1000),
(1, 'Oranges', 900),
(1, 'Pears', 500);

INSERT INTO Maintenance (TruckID, Cost)
VALUES
(1, 800),
(2, 700),
(3, 1000),
(1, 900),
(1, 500);

-- Phase 2
SELECT * FROM Drivers;

-- Find Driver #3
SELECT * FROM Drivers
WHERE DriverID = 3;

-- Find driver by last name
SELECT * FROM Drivers
WHERE LastName = 'Wilson';

-- Phase 3
SELECT * FROM Trucks;

-- Find largest truck
SELECT MAX(CapacityLbs), UnitNumber FROM Trucks AS "Biggest Truck";

-- Find smallest truck
SELECT MIN(CapacityLbs), UnitNumber FROM Trucks AS "Smallest Truck";

-- Phase 4
SELECT * FROM Customers;

-- Find a specific company
SELECT * FROM Customers
WHERE CompanyName = "Fresh Foods Inc.";

-- Phase 5
SELECT * FROM Shipments;

-- How many shipments has each customer made?
SELECT
    COUNT(Shipments.ShipmentID) AS "Amount of Shipments",
    Customers.CompanyName
FROM Shipments
INNER JOIN Customers ON Customers.CustomerID = Shipments.CustomerID
GROUP BY Customers.CompanyName
ORDER BY Customers.CompanyName;

-- Phase 6
SELECT * FROM Packages;

-- What is inside Shipment #1?
SELECT
    SUM(Packages.Weight) AS "Shipment Weight",
    Shipments.CustomerID,
    Shipments.ShipmentID
FROM Packages
INNER JOIN Shipments ON Shipments.ShipmentID = Packages.ShipmentID
GROUP BY Shipments.CustomerID;

-- What freight belongs to Fresh Foods?
SELECT
    SUM(Packages.Weight) AS "Shipment Weight",
    Customers.CompanyName,
    Shipments.ShipmentID
FROM Shipments
INNER JOIN Packages ON Shipments.ShipmentID = Packages.ShipmentID
INNER JOIN Customers ON Shipments.CustomerID = Customers.CustomerID
GROUP BY Customers.CompanyName;

-- Phase 7
SELECT 
    Shipments.ShipmentID,
    Trucks.UnitNumber,
    Drivers.FirstName
FROM Drivers
INNER JOIN Trucks ON Trucks.TruckID = Drivers.TruckID
INNER JOIN Shipments ON Trucks.TruckID = Shipments.TruckID
GROUP BY Drivers.DriverID;

-- Which shipments is Jake handling?
SELECT 
    Shipments.ShipmentID,
    Trucks.UnitNumber,
    Drivers.FirstName
FROM Drivers
INNER JOIN Trucks ON Trucks.TruckID = Drivers.TruckID
INNER JOIN Shipments ON Trucks.TruckID = Shipments.TruckID
WHERE Drivers.FirstName = 'Jake'
GROUP BY Drivers.DriverID;

-- Who handled Shipment #3?
SELECT 
    Shipments.ShipmentID,
    Trucks.UnitNumber,
    Drivers.FirstName
FROM Drivers
INNER JOIN Trucks ON Trucks.TruckID = Drivers.TruckID
INNER JOIN Shipments ON Trucks.TruckID = Shipments.TruckID
WHERE Shipments.ShipmentID = 3
GROUP BY Drivers.DriverID;

-- Phase 8
SELECT
    Shipments.ShipmentID,
    Trucks.UnitNumber
FROM Trucks
INNER JOIN Shipments ON Trucks.TruckID = Shipments.TruckID
GROUP BY Trucks.UnitNumber;

-- Which shipments used TRK-101?
SELECT
    Shipments.ShipmentID,
    Trucks.UnitNumber
FROM Trucks
INNER JOIN Shipments ON Trucks.TruckID = Shipments.TruckID
WHERE Trucks.UnitNumber = 'TRK-101'
GROUP BY Trucks.UnitNumber;

-- Which truck hauled Shipment #2?
SELECT
    Shipments.ShipmentID,
    Trucks.UnitNumber
FROM Trucks
INNER JOIN Shipments ON Trucks.TruckID = Shipments.TruckID
WHERE Shipments.ShipmentID = 2
GROUP BY Trucks.UnitNumber;

-- Show all shipment details & Show customer, driver, and truck together
SELECT
    Shipments.ShipmentID,
    Customers.CompanyName AS 'Customer',
    Drivers.FirstName AS 'Driver',
    Trucks.UnitNumber AS 'Truck'
FROM Shipments
INNER JOIN Customers ON Shipments.CustomerID = Customers.CustomerID
INNER JOIN Trucks ON Shipments.TruckID = Trucks.TruckID
INNER JOIN Drivers ON Trucks.TruckID = Drivers.TruckID
GROUP BY Shipments.ShipmentID;

-- Phase 10
SELECT * FROM Shipments;

-- Total company revenue
SELECT SUM(Shipments.Revenue) AS 'Company Revenue'
FROM Shipments;

-- Average shipment value
SELECT AVG(Shipments.Revenue) AS 'Average Shipment Revenue'
FROM Shipments;

-- Highest-paying shipment
SELECT
    MAX(Shipments.Revenue) AS 'Highest Shipment Revenue',
    Shipments.ShipmentID
FROM Shipments;

-- Phase 11
SELECT * FROM Drivers;

-- Most deliveries
SELECT
    Drivers.FirstName,
    Drivers.LastName,
    COUNT(Shipments.ShipmentID)
FROM Shipments
INNER JOIN Drivers ON Shipments.TruckID = Drivers.TruckID
GROUP BY Drivers.DriverID;

-- Most revenue generated
SELECT
    Drivers.FirstName,
    Drivers.LastName,
    SUM(Shipments.Revenue) AS Revenue_Sum
FROM Shipments
INNER JOIN Drivers ON Shipments.TruckID = Drivers.TruckID
GROUP BY Drivers.DriverID;

-- Phase 12 (cant do geographic so skipping)

-- Phase 13
SELECT * FROM Shipments;

-- All delayed shipments
SELECT * FROM Shipments
WHERE Status = 'Delayed';

-- All active shipments
SELECT * FROM Shipments
WHERE Status IN ('Enroute', 'Loading');

-- Phase 14
SELECT * FROM Maintenance;

-- Total maintenance cost & Most expensive truck to maintain
SELECT 
    SUM(Cost) AS 'Total Maintenance Costs',
    Maintenance.TruckID,
    Trucks.UnitNumber
FROM Maintenance
INNER JOIN Trucks ON Trucks.TruckID = Maintenance.TruckID
GROUP BY Maintenance.TruckID;