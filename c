Okumura-Hata Path Loss Calculator (C)
#include <stdio.h>
#include <math.h>
// Function to calculate Mobile Antenna Height Correction Factor: a(hm)
double calculate_a_hm(double f, double hm, int city_size)
{
    if (city_size == 0)
    {
        // Small / Medium-sized city
        return (1.1 * log10(f) - 0.7) * hm - (1.56 * log10(f) - 0.8);
    }
    else
    {
        // Large City
        if (f <= 300)
        {
        }
        else
        {
        }
    }
}
            return 8.29 * pow(log10(1.54 * hm), 2) - 1.1;
            return 3.2 * pow(log10(11.75 * hm), 2) - 4.97;
// Function to calculate Path Loss
double calculate_path_loss(double f, double hb, double hm, double d,
                           int env_type, int city_size)
{
    double a_hm = calculate_a_hm(f, hm, city_size);
    // Urban Path Loss
    double L_urban = 69.55 + 26.16 * log10(f)
                     - 13.82 * log10(hb)
                     - a_hm
                     + (44.9 - 6.55 * log10(hb)) * log10(d);
    switch (env_type)
    {
    case 1: // Urban
        return L_urban;
    case 2: // Suburban
        return L_urban - 2 * pow(log10(f / 28.0), 2) - 5.4;
    case 3: // Open / Rural
        return L_urban - 4.78 * pow(log10(f), 2)
               + 18.33 * log10(f) - 40.94;
    default:
        return -1.0;
    }
}
int main()
{
    double f, hb, hm, d;
    int env_type, city_size = 0;
    printf("========== Okumura-Hata Path Loss Calculator ==========\n\n");
    printf("Enter Frequency (150 - 1500 MHz): ");
    scanf("%lf", &f);
    printf("Enter Base Station Height hb (30 - 200 m): ");
    scanf("%lf", &hb);
    printf("Enter Mobile Station Height hm (1 - 10 m): ");
    scanf("%lf", &hm);
    printf("Enter Distance d (1 - 20 km): ");
    scanf("%lf", &d);
    printf("\nSelect Environment\n");
    printf("1. Urban\n");
    printf("2. Suburban\n");
    printf("3. Open / Rural\n");
    printf("Enter Choice: ");
    scanf("%d", &env_type);
    if (env_type == 1)
    {
        printf("\nSelect City Size\n");
        printf("0. Small / Medium City\n");
        printf("1. Large City\n");
        printf("Enter Choice: ");
        scanf("%d", &city_size);
    }
    // Validation
    if (f < 150 || f > 1500 ||
        hb < 30 || hb > 200 ||
        hm < 1 || hm > 10 ||
        d < 1 || d > 20)
    {
        printf("\nWarning: One or more inputs are outside the standard Hata Model limits.\n");
    }
    double path_loss = calculate_path_loss(f, hb, hm, d,
                                           env_type, city_size);
    if (path_loss < 0)
    {
        printf("\nInvalid Environment Selection.\n");
    }
    else
    {
        printf("\n=====================================\n");
        printf("Calculated Path Loss = %.2f dB\n", path_loss);
        printf("=====================================\n");
    }
    return 0;
}
