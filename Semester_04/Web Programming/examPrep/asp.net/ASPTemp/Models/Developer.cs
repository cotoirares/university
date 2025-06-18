namespace ASPTemp.Models
{
    public class Developer
    {
        public Developer() { }
        public Developer(string name, string skills, int age) {
            Name = name;
            Skills = skills;
            Age = age;
        }
        public string Name { get; set; }
        public string Skills { get; set; }
        public int Age { get; set; }
    }
}
