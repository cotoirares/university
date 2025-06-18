namespace ASPTemp.Models
{
    public class Reservation
    {
        public int Id { get; set; }
        public string Person { get; set; }
        public string Type { get; set; } // flight or hotel
        public int IdReservedResource { get; set; }
        
        public Reservation() { }
        public Reservation(int id, string person, string type, int idReservedResource) {
            Id = id;
            Person = person;
            Type = type;
            IdReservedResource = idReservedResource;
        }
    }
}