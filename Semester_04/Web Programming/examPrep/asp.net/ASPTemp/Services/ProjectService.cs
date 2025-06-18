using ASPTemp.Models;
using MySql.Data.MySqlClient;
using System.Diagnostics;

namespace ASPTemp.Services
{
    public class ProjectService
    {
        DBConnection _conn;
        public ProjectService(DBConnection conn) {
            _conn = conn;
        }
        public List<Project> getAllProjects(int projectManagerId)
        {
            String Sql = "SELECT * FROM Project WHERE ProjectManagerId = @projectManagerId";
            var parameters = new Dictionary<string, object>()
            {
                { "@ProjectManagerId", projectManagerId }
            };

            var queryResult = _conn.executeReader(Sql, parameters);
            var result = new List<Project>();

            foreach (var item in queryResult)
            {
                var project = new Project(
                    item["name"].ToString(),
                    item["description"].ToString(),
                    item["members"].ToString()
                );
                result.Add(project);
            }
            return result;
        }
        public List<Developer> getAllDevelopers()
        {
            String Sql = "SELECT * FROM SoftwareDeveloper";
            var parameters = new Dictionary<string, object>();

            var queryResult = _conn.executeReader(Sql, parameters);
            var result = new List<Developer>();

            foreach (var item in queryResult)
            {
                var project = new Developer(
                    item["name"].ToString(),
                    item["skills"].ToString(),
                    (int)item["age"]
                );
                result.Add(project);
            }
            return result;
        }
        bool isProject(string ProjectName)
        {
            String Sql = "SELECT * FROM Project WHERE name = @ProjectName";

            var parameters = new Dictionary<string, object>()
            {
                {"@ProjectName", ProjectName }
            };

            var queryResult = _conn.executeReader(Sql, parameters);
            return queryResult.Count > 0;
        }
        public void assignProjects(int devId, String[] ProjectNames)
        {
            foreach (String project in ProjectNames)
            {
                var parameters = new Dictionary<string, object>() {
                    { "@id", devId },
                    { "@name", project }
                };
                string sqlCommand = "";

                if (isProject(project))
                {
                    sqlCommand = "UPDATE Project SET ProjectManagerId = @id WHERE name = @name";
                    Console.WriteLine("Update");
                }
                else
                {
                    sqlCommand = "INSERT INTO Project (ProjectManagerId, name, description, members) VALUES (@name, @id, 'None', 'None')";
                    Console.WriteLine("Insert");
                }
                
                _conn.executeNonQuery(sqlCommand, parameters);
                Console.WriteLine("afterInsert");
            }
        }
    }
}
