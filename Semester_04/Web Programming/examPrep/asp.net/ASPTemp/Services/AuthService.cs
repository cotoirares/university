using Microsoft.AspNetCore.Mvc;
using MySql.Data.MySqlClient;

namespace ASPTemp.Services
{
    public class AuthService
    {
        DBConnection _DBConnection;
        public AuthService(DBConnection DBConnection)
        {
            _DBConnection = DBConnection;
        }
        public bool validateCredentials(String Name)
        {
            String Query = "SELECT * FROM SoftwareDeveloper WHERE Name = @Name";
            var parameters = new Dictionary<String, object>
            {
                {"@Name", Name }
            };

            List<Dictionary<string, object>> res = _DBConnection.executeReader(Query, parameters);

            if (res.Count > 0) return true;
            return false;
        }
        public void RegisterUser(String Name, String Password, int Age, String Skills)
        {
            String Query = "INSERT INTO SoftwareDeveloper (Name, Password, Age, Skills) VALUES (@Name, @Password, @Age, @Skills)";

            var parameters = new Dictionary<String, object>
            {
                {"@Name", Name },
                {"@Password", Password },
                {"@Age", Age },
                {"@Skills", Skills }
            };

            try
            {
                _DBConnection.executeNonQuery(Query, parameters);
            } catch (Exception ex)
            {
                throw ex;
            }
        }
        public int getUserId(String Name)
        {
            var SqlQuery = "SELECT Id FROM SoftwareDeveloper WHERE Name = @name LIMIT 1";

            var parameters = new Dictionary<string, object>
            {
                { "@name", Name },
            };

            var queryResult = _DBConnection.executeReader(SqlQuery, parameters);

            if (queryResult.Count > 0)
                return (int)queryResult[0]["Id"];
            else throw new Exception("User do not exist");
        }
    }
}
