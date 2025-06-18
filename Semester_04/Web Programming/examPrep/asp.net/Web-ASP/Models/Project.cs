using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;


namespace WEBASP.Models
{
  public class Project
  {
    [Required]
    public int Id { get; set; }

    public int ProjectManagerID {get; set; } 

    public SoftwareDeveloper? ProjectManager {get; set; }

    public string Name { get; set; } = string.Empty;

    public string Description { get; set; } = string.Empty;

    public string Members { get; set; } = string.Empty;



  }
}