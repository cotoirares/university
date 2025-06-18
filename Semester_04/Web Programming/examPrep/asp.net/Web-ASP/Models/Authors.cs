using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;


namespace WEBASP.Models
{
  public class Authors
  {
    [Key]
    public int AuthorId { get; set; }

    [Required]
    public string AuthorName { get; set; } = string.Empty;

    public string DocumentList { get; set; }

    public string MovieList { get; set; }
  }
}