using ASPTemp.Models;
using ASPTemp.Services;
using Microsoft.AspNetCore.Mvc;

namespace ASPTemp.Controllers
{
    public class AuthentificationController : Controller
    {
        private readonly AuthService _authService;
        public AuthentificationController(AuthService authService)
        {
            _authService = authService;
        }
        public IActionResult Index()
        {
            return View();
        }
        public IActionResult Login()
        {
            return View();
        }
        public IActionResult Register()
        {
            return View();
        }
        [HttpPost]
        public IActionResult Login(LoginViewModel model)
        {
            if(ModelState.IsValid)
            {
                try
                {
                    var userExists = _authService.validateCredentials(model.Name);
                    if (userExists)
                    {
                        HttpContext.Session.SetString("Name", model.Name);
                        HttpContext.Session.SetInt32("Id", _authService.getUserId(model.Name));
                        Console.WriteLine("User logged in");
                        return RedirectToAction("Index", "Home");
                    }
                    else
                    {
                        TempData["ErrorMessage"] = "Invalid credentials. Please try again.";
                    }
                }
                catch (Exception ex) 
                { 
                    Console.WriteLine("User not logged in");
                    TempData["ErrorMessage"] = ex.Message;
                }
            }
            else
            {
                TempData["ErrorMessage"] = "Please fill in all required fields.";
            }
            Console.WriteLine("User not logged in");
            return View(model);
        }

        [HttpPost]
        public IActionResult Register(RegisterViewModel model)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    _authService.RegisterUser(model.Name, model.Password, model.Age, model.Skills);              
                    TempData["SuccessMessage"] = $"Registration successful for {model.Name}!";
                    TempData["RegisterData"] = $"Name: {model.Name}, Age: {model.Age}, Skills: {model.Skills}";
                    return RedirectToAction("Login");
                }
                catch (Exception ex)
                {
                    TempData["ErrorMessage"] = ex.Message;
                }
            }
            else
            {
                TempData["ErrorMessage"] = "Please fill in all required fields correctly.";
            }
            return View(model);
        }
        public IActionResult Logout()
        {
            HttpContext.Session.Clear();
            return Redirect("Login");
        }
    }
}
