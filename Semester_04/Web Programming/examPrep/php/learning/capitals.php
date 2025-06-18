<!--<!DOCTYPE html>-->
<!--<html lang="en">-->
<!--<head>-->
<!--    <meta charset="UTF-8">-->
<!--    <meta name="viewport" content="width=device-width, initial-scale=1.0">-->
<!--    <title>Document</title>-->
<!--</head>-->
<!---->
<!--<body>-->
<!--<form action="index.php" method="post">-->
<!--    <label> radius: </label> <br>-->
<!--    <input type = "text" name = "radius">-->
<!--    <input type = "submit" value = "calculate">-->
<!--</form>-->
<!--</body>-->

<?php
    //$foods = array("apple", "orange", "banana", "coconut");
    //array_push($foods,"pineapple");
    //array_pop($foods);
    //array_shift($foods);
    //$foods = array_reverse($foods);
//    foreach ($foods as $food) {
//        echo $food . "<br>";
//    }

    $capitals = array(
        "USA" => "Washington, D.C.",
        "Canada" => "Ottawa",
        "Mexico" => "Mexico City",
        "UK" => "London",
        "France" => "Paris"
    );

    echo $capitals["USA"];

    foreach ($capitals as $country => $capital) {
        echo "The capital of " . $country . " is " . $capital . "<br>";
    }
?>
