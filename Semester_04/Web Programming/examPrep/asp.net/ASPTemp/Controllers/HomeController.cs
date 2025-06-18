using ASPTemp.Models;
using ASPTemp.Services;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace ASPTemp.Controllers
{
    public class HomeController : Controller
    {
        private readonly ProjectService _projectService;
        private readonly AuthService _authService;

        public HomeController(ILogger<HomeController> logger, ProjectService projectService, AuthService authService)
        {
            _projectService = projectService;
            _authService = authService;
        }

        public IActionResult Index()
        {
            var viewModel = new HomeIndexViewModel();
            var userId = HttpContext.Session.GetInt32("Id");

            if (userId.HasValue)
            {
                viewModel.projects = _projectService.getAllProjects(userId.Value);
                viewModel.developers = _projectService.getAllDevelopers();
            }
            else
            {
                // Handle the case where the userId is not valid
                TempData["ErrorMessage"] = " Please log in again.";
                return RedirectToAction("Login", "Authentification");
            }

            if (Request.Query.ContainsKey("json"))
            {
                return Json(viewModel);
            }

            return View(viewModel);
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
