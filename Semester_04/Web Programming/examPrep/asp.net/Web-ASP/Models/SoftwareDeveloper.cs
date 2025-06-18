using System.ComponentModel.DataAnnotations;

namespace WEBASP.Models
{
  public class SoftwareDeveloper
  {
    [Required]
    public int Id { get; set; }

    public string Name { get; set; } = string.Empty;

    public int Age { get; set; }

    public string Skills { get; set; } = string.Empty;

  }
}