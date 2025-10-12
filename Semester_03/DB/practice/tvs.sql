create table TV(
          FK1 INT NOT NULL,
          FK2 INT NOT NULL,
          PRIMARY KEY (FK1, FK2),
          C1 VARCHAR(100),
          C2 VARCHAR(100),
          C3 INT,
          C4 INT,
          C5 NVARCHAR(100)
);

INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (3, 2, 'Samsung', 'QLED', 120, 100, 'SS');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (1, 3, 'LG', 'OLED', 50, 50, 'CD');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (2, 1, 'Sony', 'Cognitive Processor XR Chip', 80, 30, 'EF');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (3, 3, 'TCL', 'Value', 10, 20, 'AA');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (1, 2, 'Hisense', 'Variety', 80, 120, 'FS');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (5, 4, 'Vizio', 'Quantum', 150, 20, 'GA');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (2, 2, 'Roku-made TVs', 'Value', 10, 150, 'QS');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (3, 4, 'Panasonic', 'QLED', 50, 30, 'EQ');
INSERT INTO TV (FK1, FK2, C1, C2, C3, C4, C5) VALUES (4, 2, 'Philips', 'OLED', 80, 10, 'EO');



SELECT C2, SUM(C3) TotalC3, AVG(C3) AvgC3
From TV
WHERE C3<50 OR C4<30
GROUP BY C2
HAVING SUM(C3) > 80


SELECT * FROM (
    SELECT FK1, FK2, C3 FROM TV WHERE FK1 = FK2
              ) r1
    LEFT JOIN
    (SELECT FK1, FK2, C3, C5 FROM TV WHERE C4<50 AND C5 LIKE '%A') r2
    on r1.FK1 = r2.FK2 AND r1.FK1 = r2.FK2;

CREATE OR ALTER TRIGGER TrOnUpdateTV
    ON TV
    FOR UPDATE
    AS
    DECLARE @total INT = 0
    SELECT @total = SUM(i.C3 + d.C3)
    FROM deleted d INNER JOIN inserted i ON d.FK1 = i.FK1 AND d.FK2 = i.FK2
    WHERE i.C3 < d.C3
    PRINT @total

UPDATE TV
SET C3 = 20
WHERE FK1 < FK2

DROP TABLE TV;
