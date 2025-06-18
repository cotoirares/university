using Microsoft.AspNetCore.Mvc;

namespace ASPTemp.Models
{
    public class HomeIndexViewModel
    {
        public List<Project> projects { get; set; }
        public List<Developer> developers { get; set; }

        public HomeIndexViewModel() { projects = new List<Project>(); developers = new List<Developer>(); }
    }
}
