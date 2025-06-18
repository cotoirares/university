<?php
include ("database.php");

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Login Hotel Calculator</title>
</head>

<body>
<form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
    <h2>Welcome to Hotel Dynamic Calculator!</h2>
    Username: <br>
    <input type="text" name="username"><br>
    Password: <br>
    <input type="text" name="password"><br>
    <input type="submit" name = "submit" value="login">
</form>
</body>
</html>


<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = filter_input(INPUT_POST, "username", FILTER_SANITIZE_SPECIAL_CHARS);
    $password = filter_input(INPUT_POST, "password", FILTER_SANITIZE_SPECIAL_CHARS);
    if (empty($username) || empty($password)) {
        echo "Username and password are required!";
    }
    else {
        $sql = "SELECT * FROM User WHERE username = '$username' AND password = '$password'";
        try {
            $result = mysqli_query($conn, $sql);
            if (mysqli_num_rows($result) > 0) {
                $currentUser = mysqli_fetch_assoc($result);
                echo "Welcome back, $username!";
                session_start();
                $_SESSION["userId"] = $currentUser["id"];
                $_SESSION["username"] = $username;
                $_SESSION["password"] = $password;
                header("location:home.php");
            } else {
                echo "Incorrect credentials!";
            }
        } catch (mysqli_sql_exception $e) {
            echo "Databse error: " . $e->getMessage();
        }
    }
}

mysqli_close($conn);
?>
