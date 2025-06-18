namespace ASPTemp.Models
{
    public class Hotel
    {
        public int HotelId { get; set; }
        public string HotelName { get; set; }
        public string Date { get; set; }
        public string City { get; set; }
        public int AvailableRooms { get; set; }
        
        public Hotel() { }
        public Hotel(int hotelId, string hotelName, string date, string city, int availableRooms) {
            HotelId = hotelId;
            HotelName = hotelName;
            Date = date;
            City = city;
            AvailableRooms = availableRooms;
        }
    }
}