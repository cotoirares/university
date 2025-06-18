namespace ASPTemp.Models
{
    public class Flight
    {
        public int FlightId { get; set; }
        public string Date { get; set; }
        public string DestinationCity { get; set; }
        public int AvailableSeats { get; set; }
        
        public Flight() { }
        public Flight(int flightId, string date, string destinationCity, int availableSeats) {
            FlightId = flightId;
            Date = date;
            DestinationCity = destinationCity;
            AvailableSeats = availableSeats;
        }
    }
}