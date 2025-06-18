// index.php

<?php
    session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Document</title>
</head>

<body>
<form action="index.php" method="post">
    username:
    <input type="text" name="username"><br>
    password:
    <input type="password" name="password"><br>
    <input type="submit" name = "login" value="login">
</form>
</body>
</html>

<?php
    if (isset($_POST['login'])) {
        if (!empty($_POST['username']) && !empty($_POST['password'])) {
            $_SESSION['username'] = $_POST['username'];
            $_SESSION['password'] = $_POST['password'];

            header("Location: home.php");
        }
    }
?>



// home.php

<?php
session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Document</title>
</head>

<body>
This is the home page.

<form action = "home.php" method = "post">
    <input type = "submit" name = "logout" value = "logout">
</form>
</body>
</html>

<?php

echo $_SESSION["username"] . "<br>";
echo $_SESSION["password"] . "<br>";

if (isset($_POST["logout"])){
    session_destroy();
    header("location:index.php");
}

?>

