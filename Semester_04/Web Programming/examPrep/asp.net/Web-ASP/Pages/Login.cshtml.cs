using WEBASP.Services;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using System.ComponentModel.DataAnnotations;

namespace WEBASP.Pages
{
    public class LoginModel : PageModel
    {
        private readonly AuthService _authService;

        public LoginModel(AuthService authService)
        {
            _authService = authService;
        }

        [BindProperty]
        public InputModel Input { get; set; } = new InputModel();

        public string ErrorMessage { get; set; } = string.Empty;

        public class InputModel
        {
            [Required]
            public string Username { get; set; } = string.Empty;
            [Required]
            public string AuthoredMovieOrDocument { get; set; } = string.Empty;
        }

        public IActionResult OnGet()
        {
            if (_authService.IsLoggedIn())
            {
                return RedirectToPage("/Index");
            }

            return Page();
        }

        public async Task<IActionResult> OnPostAsync()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }

            var user = await _authService.AuthenticateAsync(Input.Username, Input.AuthoredMovieOrDocument);

            if (user == null)
            {
                ErrorMessage = "Invalid username or identification document.";
                return Page();
            }

            await _authService.SignInAsync(user);
            return RedirectToPage("/Index");
        }
    }
} 