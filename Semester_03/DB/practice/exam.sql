
-- create table R(
--           FK1 INT NOT NULL,
--           FK2 INT NOT NULL,
--           PRIMARY KEY (FK1, FK2),
--           C1 VARCHAR(100),
--           C2 VARCHAR(100),
--           C3 VARCHAR(100),
--           C4 VARCHAR(100),
--           C5 FLOAT,
--           C6 INT
-- );

-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (1, 1, 'Oppenheimer', 'Cristopher Nolan',  'A1', 'Action', 7.7, 110);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (1, 2, 'Avatar', 'James Cameron',  'A1', 'Adventure', 7.9, 150);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (1, 3, 'Cairo Conspiracy', 'Tarik Saleh',  'A2', 'Drama', 8.1, 142);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (2, 1, 'Call Jane', 'Phyllis Nagy',  'B2', 'Drama', 8.4, 100);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (2, 2, 'Lyle, Lyle, Crocodile', 'Will Speck',  'B3', 'Animation', 9, 121);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (2, 3, 'Man of God', 'Yelena Popovic',  'C1', 'Biography', 6, 133);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (2, 4, 'Ratatouille', 'Brad Bird',  'C2', 'Animation', 8, 96);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (3, 1, 'Killers of the Flower Moon', 'Martin Scorsese',  'C2', 'Western', 8.6, 141);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (3, 2, 'Teambuilding', 'Matei Dima',  'A2', 'Comedy', 6.8, 110);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (3, 3, 'Cinderella', 'Cecile Mosli',  'D2', 'Family', 6.3, 120);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (4, 1, 'Alcarras', 'Carla Simon',  'D2', 'Drama', 8.4, 131);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (4, 2, 'Official Competition', 'Gaston Duprat',  'D1', 'Comedy', 5.1, 106);
-- INSERT INTO R (FK1, FK2, C1, C2, C3, C4, C5, C6) VALUES (4, 3, 'Inglourious Basterds', 'Quentin Tarantino',  'A2', 'Drama', 7.8, 199);



--SELECT C3, C2, AVG(C5) AvgC5, COUNT(C4) C4
--FROM R
--WHERE C3 LIKE '%b_' or C5<5
--GROUP BY C3
--HAVING SUM(C6)<200

-- SELECT * FROM (
--     SELECT FK1, FK2, C6*100 C6
--     FROM R
--     WHERE FK1>FK2
--               ) r1
-- RIGHT JOIN (SELECT FK1, FK2, C5 FROM R WHERE C6%2!=0) r2 on r1.FK1 = r2.FK1 AND r1.FK2 = r2.FK2
--
--
-- CREATE OR ALTER TRIGGER TrOnUpdate
--     ON R
--     FOR UPDATE
--     AS
--     DECLARE @total INT = 0
--     SELECT @total = SUM(i.FK2 + d.FK1)
--     FROM deleted d INNER JOIN inserted i ON d.FK1 = i.FK1 AND d.FK2 = i.FK2
--     WHERE d.C6 >= i.C6
--     PRINT @total
--
-- UPDATE R
-- SET C6 = 500
-- WHERE FK1 > FK2


-- part 2 task 1
create table Customer(
    CustomerID int primary key identity (1,1),
    CustomerNationality VARCHAR(100),
    CustomerDateOfBirth DATE,
);

create table ContactPreferences(
    PreferenceID int primary key identity (1,1),
    PreferenceDescription varchar(100),
    Customer INT REFERENCES Customer(CustomerID)
);

create table Property(
    PropertyID int primary key identity (1,1),
    PropertyDescription varchar(100),
    PropertyAddress varchar(100),
    CheckInTime varchar(100),
    CheckOutTime varchar(100),
    PersonsCapacity INT,
    PricePerNight INT,
    FreeCancelation BIT
);

create table Bookings(
    BookingID int primary key identity (1,1),
    Customer INT REFERENCES Customer(CustomerID),
    Property INT REFERENCES Property(PropertyID),
    NumberOfPersons INT,
    StartDate DATE,
    EndDate DATE
);

create table Payments(
    PaymentID int primary key identity (1,1),
    Amount int,
    DateOfPayment DATE,
    TypeOfPayment VARCHAR(100),
    CONSTRAINT TypeOfPayment CHECK(TypeOfPayment = 'PayPal' or TypeOfPayment = 'Credit Card'),
    BookingID INT REFERENCES Bookings(BookingID),
)

-- task 2
create or alter procedure sp_AddBooking (@CustomerID INT, @PropertyID INT, @Persons INT, @StartDate INT, @EndDate INT) AS
BEGIN
    IF NOT EXISTS(SELECT PropertyID from Property WHERE PropertyID = @PropertyID)
    BEGIN
        PRINT 'Property not found'
        RETURN
    end
    IF NOT EXISTS(SELECT PropertyID from Property WHERE PropertyID = @PropertyID AND PersonsCapacity >= @Persons)
    BEGIN
        PRINT 'Property does not have enough capacity'
        RETURN
    END
    INSERT INTO Bookings(Customer, Property, NumberOfPersons, StartDate, EndDate) VALUES (@CustomerID, @PropertyID, @Persons, @StartDate, @EndDate)
end
GO;

-- task c
CREATE VIEW vw_MostUsedPaymentType as
SELECT TOP 1 TypeOfPayment
FROM Payments
GROUP BY TypeOfPayment
ORDER BY COUNT(TypeOfPayment) DESC

-- task d
create or alter function fn_CountBookingsWithPaymentsLessThan(@R INT, @V INT)
    RETURNS INT
    AS
    BEGIN
        DECLARE @count INT
        SELECT @count = COUNT(BookingID)
        FROM Payments
        WHERE Amount < @V
        GROUP BY BookingID
        HAVING COUNT(BookingID) > @R
        RETURN @count
    END
GO




