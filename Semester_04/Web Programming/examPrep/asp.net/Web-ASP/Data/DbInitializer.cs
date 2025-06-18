using WEBASP.Models;
using Microsoft.EntityFrameworkCore;
using System.Security.Cryptography;
using System.Text;

namespace WEBASP.Data
{
    public static class DbInitializer
    {
        public static void Initialize(ApplicationDbContext context)
        {
            context.Database.EnsureDeleted();
            context.Database.EnsureCreated();

            var documents = new Documents[]
            {
                new Documents {DocumentId = 1, Name = "test document", Contents = "test"},
                new Documents {DocumentId = 2, Name = "Java Documentation", Contents = "Documentation for Java programming language"},
                new Documents {DocumentId = 3, Name = "C# Documentation", Contents = "Documentation for C# programming language"},
                new Documents {DocumentId = 4, Name = "Python Documentation", Contents = "Documentation for Python programming language"},
                new Documents {DocumentId = 5, Name = "JavaScript Documentation", Contents = "Documentation for JavaScript programming language"},
            };
            
            context.Documents.AddRange(documents);
            context.SaveChanges();

            var movies = new Movies[]
            {
                new Movies {MovieId = 1, Title = "Titanic", Duration = 200},
                new Movies {MovieId = 2, Title = "Harry Potter 1", Duration = 148},
                new Movies {MovieId = 3, Title = "Harry Potter 2", Duration = 161},
                new Movies {MovieId = 4, Title = "Harry Potter 3", Duration = 142},
                new Movies {MovieId = 5, Title = "Harry Potter 4", Duration = 157},
            };
            
            context.Movies.AddRange(movies);
            context.SaveChanges();

            var authors = new Authors[]
            {
                new Authors {AuthorId = 1, AuthorName = "Vlad", DocumentList = "1,2", MovieList = "1,3" },
                new Authors {AuthorId = 2, AuthorName = "Alex", DocumentList = "2", MovieList = "1,5" },
                new Authors {AuthorId = 3, AuthorName = "Rares", DocumentList = "3,4", MovieList = "3" },
                new Authors {AuthorId = 4, AuthorName = "Dani", DocumentList = "2,3,4", MovieList = "2,3" },
                new Authors {AuthorId = 5, AuthorName = "Test", DocumentList = "1,2, 5", MovieList = "1,4" },
            };
            
            context.Authors.AddRange(authors);
            context.SaveChanges();
            
        }
    }
} 