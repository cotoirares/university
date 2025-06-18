using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;


namespace WEBASP.Models
{
  public class Movies
  {
    [Key]
    public int MovieId { get; set; }
    
    [Required]
    public string Title { get; set; } 

    [Required]
    public int Duration { get; set; }
  }
}