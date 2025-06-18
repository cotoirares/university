<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
<form action="index.php" method="post">
    <label> quantity: </label> <br>
    <input type = "text" name = "quantity">
    <input type = "submit" value = "total">
</form>
</body>

<?php
    $item = "pizza";
    $price = 5.99;
    $quantity = $_POST['quantity'];
    $total = $price * $quantity;
    echo "You ordered {$quantity} x {$item}/s <br>";
    echo "Total: $total";
?>
