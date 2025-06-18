using WEBASP.Services;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc;
using WEBASP.Models;

namespace WEBASP.Pages;

public class IndexModel : PageModel
{
    private readonly AuthService _authService;

    private readonly ProjectService _projectService;

    public IndexModel(AuthService authService, ProjectService projectService)
    {
        _authService = authService;
        _projectService = projectService;
    }

    public class AddDocumentModel
    {
        public string Title { get; set; } = string.Empty;
        public string Content { get; set; } = string.Empty;
    }

    public string CurrentUserName { get; private set; } = string.Empty;

    public bool IsLoggedIn { get; private set; }

    public List<Project> CurrentProjects { get; set; } = new List<Project>();

    public List<Documents> CurrentDocuments { get; set; } = new List<Documents>();

    public List<Movies> CurrentMovies { get; set; } = new List<Movies>();

    public List<Documents> MyDocuments { get; set; } = new List<Documents>();
    public List<Movies> MyMovies { get; set; } = new List<Movies>();



    [BindProperty]
    public AddDocumentModel NewDocument { get; set; } = new();


    public async Task<IActionResult> OnGetAsync()
    {
        CurrentUserName = _authService.GetCurrentUserName();

        IsLoggedIn = _authService.IsLoggedIn();

        CurrentDocuments = await _projectService.GetAllDocuments();
        CurrentMovies = await _projectService.GetAllMovies();

        var documentList = HttpContext.Session.GetString("DocumentList") ?? "";
        var movieList = HttpContext.Session.GetString("MovieList") ?? "";
        MyDocuments = await _projectService.GetUserDocumentsAsync(documentList);
        MyMovies = await _projectService.GetUserMoviesAsync(movieList);


        return Page();
    }


    public async Task<IActionResult> OnPostAddDocumentAsync()
    {
        await _projectService.AddDocument(NewDocument.Title, NewDocument.Content);
        return RedirectToPage("/Index");
    }
    
    public List<object> GetInterleavedWorks()
    {
        var result = new List<object>();
        int maxCount = Math.Max(MyDocuments.Count, MyMovies.Count);

        for (int i = 0; i < maxCount; i++)
        {
            // Add document if available
            if (i < MyDocuments.Count)
                result.Add(MyDocuments[i]);
            
            // Add movie if available  
            if (i < MyMovies.Count)
                result.Add(MyMovies[i]);
        }

        return result;
    }
}
