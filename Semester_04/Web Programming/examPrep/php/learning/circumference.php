<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
<form action="index.php" method="post">
    <label> radius: </label> <br>
    <input type = "text" name = "radius">
    <input type = "submit" value = "calculate">
</form>
</body>

<?php
    $radius = $_POST["radius"];
    $circumference = 2 * pi() * $radius;

    echo "Circumference = {$circumference}cm <br>";
?>
