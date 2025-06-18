namespace ASPTemp.Models
{
    public class Project
    {
        public Project(string name, string description, string members)
        {
            Name = name;
            Description = description;
            Members = members;
        }
        public Project(string name)
        {
            Name = name;
            Description = "no description";
            Members = "no members";
        }

        public string Name { get; set; }
        public string Description { get; set; }
        public string Members { get; set; }
    }
}
