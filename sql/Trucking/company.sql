CREATE TABLE Drivers (
    DriverID INTEGER PRIMARY KEY AUTOINCREMENT,
    FirstName TEXT NOT NULL,
    LastName TEXT NOT NULL
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
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);

INSERT INTO Drivers (FirstName, LastName)
VALUES 
("Jake", "Wilson"),
("Sarah", "Lopez"),
("Micheal", "Brown"),
("Emma", "Davis"),
("Noah", "Garcia");

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

INSERT INTO Shipments (CustomerID)
VALUES
(1),
(2),
(1),
(3),
(4);

SELECT * FROM Drivers;
SELECT * FROM Drivers
WHERE DriverID = 3;
SELECT * FROM Drivers
WHERE LastName = 'Wilson';

SELECT * FROM Trucks;
SELECT MAX(CapacityLbs), UnitNumber FROM Trucks AS "Biggest Truck";
SELECT MIN(CapacityLbs), UnitNumber FROM Trucks AS "Smallest Truck";

SELECT * FROM Customers;
SELECT * FROM Customers
WHERE CompanyName = "Fresh Foods Inc.";

SELECT * FROM Shipments;
SELECT
    COUNT(Shipments.ShipmentID) AS "Amount of Shipments",
    Customers.CompanyName
FROM Shipments
INNER JOIN Customers ON Customers.CustomerID = Shipments.CustomerID
GROUP BY Customers.CompanyName
ORDER BY Customers.CompanyName;

