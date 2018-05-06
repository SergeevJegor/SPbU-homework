public class SportCar extends Auto {
    private double accelerationTo100;

    public SportCar(int maxSpeed, int weight, int horsepower, String model, int yearOfManufacture, String countryOfManufacture, int price, double accelerationTo100) {
        super(maxSpeed, weight, horsepower, model, yearOfManufacture, countryOfManufacture, price);
        this.accelerationTo100 = accelerationTo100;
    }

    @Override
    public String getDetailedInfo() {
        return ("Accelerates to 100km/h (sec): " + accelerationTo100 + "\n");
    }
}
