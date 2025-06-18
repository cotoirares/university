<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>Authors</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f2f5;
        }
        .container {
            background-color: white;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
            width: 300px;
        }
        .form-group {
            margin-bottom: 15px;
        }
        label {
            display: block;
            margin-bottom: 5px;
        }
        input {
            width: 100%;
            padding: 8px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }
        button {
            width: 100%;
            padding: 10px;
            background-color: #1877f2;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        button:hover {
            background-color: #166fe5;
        }
        .register-link {
            text-align: center;
            margin-top: 15px;
        }
        .error {
            color: red;
            margin-bottom: 10px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2 style="text-align: center;">Login</h2>
        <% if (request.getAttribute("error") != null) { %>
            <div class="error">${error}</div>
        <% } %>
        <form action="login" method="post" onsubmit="return validateForm()">
            <div class="form-group">
                <label for="username">Your Name:</label>
                <input type="text" id="username" name="username" required>
            </div>
            <button type="submit">Login</button>
        </form>
    </div>

    <script>
        function validateForm() {
            var username = document.getElementById("username").value;
            
            if (username.trim() === "") {
                alert("Author Name cannot be empty");
                return false;
            }
            return true;
        }
    </script>
</body>
</html> 