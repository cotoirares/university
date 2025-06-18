using ASPTemp.Models;
using ASPTemp.Services;
using Microsoft.AspNetCore.Mvc;

namespace ASPTemp.Controllers
{
    public class ProjectController : Controller
    {
        private readonly ProjectService _projectService;
        private readonly AuthService _authService;
        public ProjectController(ProjectService projectService, AuthService authService)
        {
            _projectService = projectService;
            _authService = authService;
        }

        public IActionResult Index()
        {
            return View();
        }
        public IActionResult Assign()
        {
            return View();
        }

        [HttpPost]
        public IActionResult AssignDevs(AssignViewModel model)
        {
            try
            {
                int devId = _authService.getUserId(model.developerName);
                //parse projects
                string[] projList;
                projList = model.projects.Split(',');

                _projectService.assignProjects(devId, projList);
                TempData["SuccessMessage"] = "Developer successfully assigned to projects!";
                return RedirectToAction("Assign");
            }
            catch (Exception ex)
            {
                TempData["ErrorMessage"] = "Developer does not exist";
                return RedirectToAction("Assign");
            }
        }
    }
}
