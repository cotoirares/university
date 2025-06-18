using WEBASP.Models;
using Microsoft.EntityFrameworkCore;

namespace WEBASP.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Movies> Movies { get; set; }
        public DbSet<Documents> Documents { get; set; }
        public DbSet<Authors> Authors { get; set; }

        
    }
} 