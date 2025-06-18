using WEBASP.Data;
using WEBASP.Models;
using Microsoft.EntityFrameworkCore;
using System.Text;
using Microsoft.AspNetCore.Http.Metadata;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore.Internal;

namespace WEBASP.Services
{
    public class ProjectService
    {
        private readonly ApplicationDbContext _context;

        public ProjectService(ApplicationDbContext context, IHttpContextAccessor httpContextAccessor)
        {
            _context = context;
        }

        public async Task<List<Documents>> GetAllDocuments()
        {
            return await _context.Documents.ToListAsync();
        }
        public async Task<List<Movies>> GetAllMovies()
        {
            return await _context.Movies.ToListAsync();
        }


        public async Task<bool> AddDocument(string DocumentTitle, string DocumentContent)
        {
            try
            {
                var toAddDocument = new Documents
                {
                    Name = DocumentTitle,
                    Contents = DocumentContent
                };

                _context.Documents.Add(toAddDocument);
                await _context.SaveChangesAsync();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error adding document: {ex.Message}");
                return false;
            }
        }

        // get all movies and documents authored by current user
        public async Task<List<Documents>> GetUserDocumentsAsync(string documentList)
        {
            if (string.IsNullOrEmpty(documentList))
                return new List<Documents>();

            var docIds = documentList.Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse).ToList();

            return await _context.Documents
                .Where(d => docIds.Contains(d.DocumentId))
                .ToListAsync();
        }

        public async Task<List<Movies>> GetUserMoviesAsync(string movieList)
        {
            if (string.IsNullOrEmpty(movieList))
                return new List<Movies>();

            var movieIds = movieList.Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse).ToList();

            return await _context.Movies
                .Where(m => movieIds.Contains(m.MovieId))
                .ToListAsync();
        }
    }
} 