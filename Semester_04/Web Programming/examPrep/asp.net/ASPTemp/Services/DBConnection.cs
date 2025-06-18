using MySql.Data.MySqlClient;
using Mysqlx.Crud;

namespace ASPTemp.Services
{
    public class DBConnection
    {
        private MySqlConnection _conn;
        public DBConnection()
        {
            OpenConnection();
        }

        private string GetConnectionString()
        {
            return "server=localhost;port=8889;database=webexam;user id=root;password=root;SslMode=none;AllowPublicKeyRetrieval=True;";
        }
        private void OpenConnection()
        {
            try
            {
                _conn = new MySqlConnection(GetConnectionString());
                _conn.Open();
            }
            catch (Exception ex)
            {
                throw new Exception("Could not open database connection: " + ex.Message);
            }
        }

        private void CloseConnection()
        {
            _conn.Close();
        }
        public void executeNonQuery(string SqlStatement, Dictionary<String, object> parameters)
        {
            try
            {
                var cmd = new MySqlCommand(SqlStatement, _conn);

                foreach (var param in parameters)
                    cmd.Parameters.AddWithValue(param.Key, param.Value);

                cmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public List<Dictionary<string, object>> executeReader(string sqlStatement, Dictionary<String, object> parameters)
        {
            var results = new List<Dictionary<string, object>>();

            try
            {
                var cmd = new MySqlCommand(sqlStatement, _conn);

                foreach (var param in parameters)
                    cmd.Parameters.AddWithValue(param.Key, param.Value);
                
                using (var reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        var row = new Dictionary<string, object>();
                        for (int i = 0; i < reader.FieldCount; i++)
                        {
                            row[reader.GetName(i)] = reader.GetValue(i);
                        }
                        results.Add(row);
                    }
                }
                return results;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
