class CurrencyConverter {
    public:

        double convertUsdToEur(double usd) {
            return usd * usdToEurRate;
        }

        double convertEurToUsd(double eur) {
            return eur / usdToEurRate;
        }
        void updateExchangeRate(double newRate) {
            usdToEurRate = newRate;
        }
    private:
        double usdToEurRate=0.85;
    };

    CurrencyConverter currency;


