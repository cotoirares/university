using WEBASP.Data;
using WEBASP.Models;
using Microsoft.EntityFrameworkCore;
using System.Text;

namespace WEBASP.Services
{
    public class AuthService
    {
        private readonly ApplicationDbContext _context;
        private readonly IHttpContextAccessor _httpContextAccessor;

        public AuthService(ApplicationDbContext context, IHttpContextAccessor httpContextAccessor)
        {
            _context = context;
            _httpContextAccessor = httpContextAccessor;
        }

        public async Task<Authors?> AuthenticateAsync(string username, string authoredDocumentOrMovie)
        {
            var user = await _context.Authors
                .FirstOrDefaultAsync(u => u.AuthorName == username);

            if (user == null)
                return null;

            var document = await _context.Documents
                .FirstOrDefaultAsync(d => d.Name == authoredDocumentOrMovie);
            
            var movie = await _context.Movies
                .FirstOrDefaultAsync(m => m.Title == authoredDocumentOrMovie);
            
            var authoredDocuments = user.DocumentList?.Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse).ToList() ?? new List<int>();
            var authoredMovies = user.MovieList?.Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse).ToList() ?? new List<int>();

            bool isDocumentAuthor = document != null && authoredDocuments.Contains(document.DocumentId);
            bool isMovieAuthor = movie != null && authoredMovies.Contains(movie.MovieId);

            if (isDocumentAuthor || isMovieAuthor)
            {
                return user;
            }

            return null;
        }

        public Task<bool> SignInAsync(Authors user)
        {
            if (user == null)
                return Task.FromResult(false);

            var session = _httpContextAccessor.HttpContext?.Session;
            if (session == null)
                return Task.FromResult(false);

            session.SetInt32("AuthorId", user.AuthorId);
            session.SetString("AuthorName", user.AuthorName);
            session.SetString("DocumentList", user.DocumentList);
            session.SetString("MovieList", user.MovieList);

            return Task.FromResult(true);
        }
        
        public string GetCurrentUserName()
        {
            return _httpContextAccessor.HttpContext?.Session.GetString("AuthorName") ?? string.Empty;
        }
        
        public bool IsLoggedIn()
        {
            return _httpContextAccessor.HttpContext?.Session.GetInt32("AuthorId") != null;
        }

    }
} 