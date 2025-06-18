using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;


namespace WEBASP.Models
{
  public class Documents
  {
    [Key]
    public int DocumentId { get; set; }
    
    [Required]
    public string Name { get; set; } = string.Empty;

    [Required]
    public string Contents { get; set; } =  string.Empty;
  }
}