<?php
session_start();
include("database.php");

if (!isset($_SESSION["username"])) {
    header("location: index.php");
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Home</title>
</head>
<body>
<h2>Welcome back, <?php echo $_SESSION["username"] ?> !</h2>

<h4>You can see the available rooms in date range</h4>

<form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
    Enter check in date: <br>
    <input type="date" name="firstDate"><br>
    Enter check out date: <br>
    <input type="date" name="secondDate"><br>
    <input type="submit" name = "seeAvailableRooms" value="Submit">
</form>

<?php

if (isset($_POST["seeAvailableRooms"])) {
    $currentCheckInDate = filter_input(INPUT_POST, "firstDate", FILTER_SANITIZE_SPECIAL_CHARS);
    $currentCheckOutDate = filter_input(INPUT_POST, "secondDate", FILTER_SANITIZE_SPECIAL_CHARS);

    $sqlRooms = "SELECT * FROM HotelRoom";
    $allRooms = mysqli_query($conn, $sqlRooms);

    $availableRooms = array();

    echo "<h4>Here are all the available rooms in the specified time period:</h4>";
    echo "<table border='1'>
                <tr>
                    <th>Room ID</th>
                    <th>Room Number</th>
                    <th>Capacity</th>
                    <th>Base Price</th>
                </tr>
        ";

    for ($i = 0; $i < mysqli_num_rows($allRooms); $i++) {
        $currentRoom = mysqli_fetch_assoc($allRooms);
        $available = true;
        $sqlReservations = "SELECT * FROM Reservation";
        $allReservations = mysqli_query($conn, $sqlReservations);
        for ($j = 0; $j < mysqli_num_rows($allReservations); $j++) {
            $currentReservation = mysqli_fetch_assoc($allReservations);
            if ($currentReservation["roomId"] == $currentRoom["id"] &&
                (($currentCheckInDate > $currentReservation["checkInDate"] && $currentCheckInDate < $currentReservation["checkOutDate"])
                 || ($currentCheckOutDate > $currentReservation["checkInDate"] && $currentCheckOutDate < $currentReservation["checkOutDate"]))){
                    $available = false;
            }
        }
        if ($available) {
            $availableRooms[] = $currentRoom["id"];
            echo "<tr>
                    <td>" . $currentRoom["id"] . "</td>
                    <td>" . $currentRoom["roomNumber"] . "</td>
                    <td>" . $currentRoom["capacity"] . "</td>
                    <td>" . $currentRoom["basePrice"] . "</td>
                  </tr>";
        }
    }
    echo "</table>";
    $_SESSION["availableRooms"] = $availableRooms;
}
?>

<h2>You can reserve one of the available rooms (please see them before)</h2>
<form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
    Enter check in date: <br>
    <input type="date" name="firstDateAgain"><br>
    Enter check out date: <br>
    <input type="date" name="secondDateAgain"><br>
    Enter room in for reservation: <br>
    <input type="number" name="toReserveRoom"><br>
    Enter number of persons for reservation: <br>
    <input type="number" name="numberOfPersonsToReserve"><br>
    <input type="submit" name = "reserveRoom" value="Submit">
</form>

<?php
if (isset($_POST["reserveRoom"])){
    $roomToReserve = filter_input(INPUT_POST, "toReserveRoom", FILTER_SANITIZE_SPECIAL_CHARS);
    if (!in_array($roomToReserve, $_SESSION["availableRooms"])){
        echo 'The room you selected is not available in that period of time!';
    }
    else{
        $currentCheckInDate = filter_input(INPUT_POST, "firstDateAgain", FILTER_SANITIZE_SPECIAL_CHARS);
        $currentCheckOutDate = filter_input(INPUT_POST, "secondDateAgain", FILTER_SANITIZE_SPECIAL_CHARS);
        $numerOfPersonsToReserve = filter_input(INPUT_POST, "numberOfPersonsToReserve", FILTER_SANITIZE_SPECIAL_CHARS);

        //if user has already a reservation in that time
        $hasReservation = false;
        $sqlReservations = "SELECT * FROM Reservation";
        $allReservations = mysqli_query($conn, $sqlReservations);
        for ($j = 0; $j < mysqli_num_rows($allReservations); $j++) {
            $currentReservation = mysqli_fetch_assoc($allReservations);
            if ($currentReservation["userId"] == $_SESSION["userId"] &&
                (($currentCheckInDate > $currentReservation["checkInDate"] && $currentCheckInDate < $currentReservation["checkOutDate"])
                    || ($currentCheckOutDate > $currentReservation["checkInDate"] && $currentCheckOutDate < $currentReservation["checkOutDate"]))){
                        $hasReservation = true;
            }
        }
        if ($hasReservation)
            echo 'You already have a reservation for the selected period of time!';
        else {
            // reservatiom
            $toReserveRoomSql = "SELECT * FROM HotelRoom WHERE id = '$roomToReserve'";
            $toReserveRoomResult = mysqli_query($conn, $toReserveRoomSql);
            $toReserveRoom = mysqli_fetch_assoc($toReserveRoomResult);

            $freeRooms = count($_SESSION["availableRooms"]);
            $sqlRooms = "SELECT * FROM HotelRoom";
            $allRooms = mysqli_query($conn, $sqlRooms);
            $totalRooms = mysqli_num_rows($allRooms);

            $occupiedRooms = $totalRooms - $freeRooms;
            $percantageOccupied = (float)($occupiedRooms * 100) / $totalRooms;
            $priceForReservation = 0;
            if ($percantageOccupied <= 50) {
                $priceForReservation = $toReserveRoom["basePrice"];
            } else if ($percantageOccupied > 50 && $percantageOccupied <= 80) {
                $priceForReservation = $toReserveRoom["basePrice"] + (20 * $toReserveRoom["basePrice"]) / 100;
            } else if ($percantageOccupied > 80) {
                $priceForReservation = $toReserveRoom["basePrice"] + (50 * $toReserveRoom["basePrice"]) / 100;
            }
            $userId = $_SESSION["userId"];
            $reservationQuery = "INSERT INTO Reservation (userId, roomId, checkInDate, checkOutDate, numberOfGuests, totalPrice)
                                VALUES ($userId, $roomToReserve, '$currentCheckInDate', '$currentCheckOutDate', '$numerOfPersonsToReserve', $priceForReservation)";
            if (mysqli_query($conn, $reservationQuery)) {
                echo 'Your reservation was created succesfully!';
            } else {
                echo "Error creating reservation: " . mysqli_error($conn) . "<br>";
            }
        }
    }
}
?>

<h2>You can see the number of guests in a specific date</h2>
<form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
    Please select the date: <br>
    <input type="date" name="guestsInThatDate"><br>
    <input type="submit" name = "seeGuestsInDate" value="Submit">
</form>

<?php
    if (isset($_POST["seeGuestsInDate"])) {
        $dateToSee = filter_input(INPUT_POST, "guestsInThatDate", FILTER_SANITIZE_SPECIAL_CHARS);
        $totalGuests = 0;
        $sqlReservations = "SELECT * FROM Reservation";
        $allReservations = mysqli_query($conn, $sqlReservations);
        for ($j = 0; $j < mysqli_num_rows($allReservations); $j++) {
            $currentReservation = mysqli_fetch_assoc($allReservations);
            if ($dateToSee >= $currentReservation["checkInDate"] && $dateToSee <= $currentReservation["checkOutDate"]){
                $totalGuests += $currentReservation["numberOfGuests"];
            }
        }
        echo 'In the specified date, the number of guests is: ';
        echo $totalGuests;
    }

?>

<h2>All your current reservations are:</h2>

<?php
    echo "<table border='1'>
                <tr>
                    <th>Reservation ID</th>
                    <th>Room ID</th>
                    <th>Check In Date</th>
                    <th>Check Out Date</th>
                    <th>Number of Guests</th>
                    <th>Total Price</th>
                </tr>
        ";
    $sqlReservations = "SELECT * FROM Reservation";
    $allReservations = mysqli_query($conn, $sqlReservations);
    for ($j = 0; $j < mysqli_num_rows($allReservations); $j++) {
        $currentReservation = mysqli_fetch_assoc($allReservations);
        if ($_SESSION["userId"] == $currentReservation["userId"]){
            echo "<tr>
                    <td>" . $currentReservation["id"] . "</td>
                    <td>" . $currentReservation["roomId"] . "</td>
                    <td>" . $currentReservation["checkInDate"] . "</td>
                    <td>" . $currentReservation["checkOutDate"] . "</td>
                    <td>" . $currentReservation["numberOfGuests"] . "</td>
                    <td>" . $currentReservation["totalPrice"] . "</td>
                  </tr>";
        }

    }
?>

<form action="home.php" method="post">
    <input type="submit" name="logout" value="logout">
</form>

<?php
if (isset($_POST["logout"])) {
    session_destroy();
    header("location:index.php");
}
mysqli_close($conn);
?>


</body>
</html>
