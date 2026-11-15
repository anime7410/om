
clc;
clear;
close all;

% Okumura-Hata Path Loss Calculator

fprintf('========== Okumura-Hata Path Loss Calculator ==========\n\n');

% Input Parameters
f = input('Enter Frequency (150 - 1500 MHz): ');
hb = input('Enter Base Station Height hb (30 - 200 m): ');
hm = input('Enter Mobile Station Height hm (1 - 10 m): ');
d = input('Enter Distance d (1 - 20 km): ');

% Environment Selection
fprintf('\nSelect Environment\n');
fprintf('1. Urban\n');
fprintf('2. Suburban\n');
fprintf('3. Open / Rural\n');

env_type = input('Enter Choice: ');

city_size = 0;

if env_type == 1
    fprintf('\nSelect City Size\n');
    fprintf('0. Small / Medium City\n');
    fprintf('1. Large City\n');
    city_size = input('Enter Choice: ');
end

% Calculate Mobile Antenna Height Correction Factor
if city_size == 0

    ahm = (1.1 * log10(f) - 0.7) * hm ...
          - (1.56 * log10(f) - 0.8);

else

    if f <= 300
        ahm = 8.29 * (log10(1.54 * hm))^2 - 1.1;
    else
        ahm = 3.2 * (log10(11.75 * hm))^2 - 4.97;
    end

end

% Urban Path Loss Calculation
L_urban = 69.55 + 26.16 * log10(f) ...
          - 13.82 * log10(hb) ...
          - ahm ...
          + (44.9 - 6.55 * log10(hb)) * log10(d);

% Environment Based Path Loss
switch env_type

    case 1
        % Urban
        path_loss = L_urban;

    case 2
        % Suburban
        path_loss = L_urban ...
                    - 2 * (log10(f / 28))^2 - 5.4;

    case 3
        % Open / Rural
        path_loss = L_urban ...
                    - 4.78 * (log10(f))^2 ...
                    + 18.33 * log10(f) - 40.94;

    otherwise
        fprintf('\nInvalid Environment Selection.\n');
        return;

end

% Input Validation Warning
if f < 150 || f > 1500 || ...
   hb < 30 || hb > 200 || ...
   hm < 1 || hm > 10 || ...
   d < 1 || d > 20

    fprintf('\nWarning: One or more inputs are outside the standard Hata Model limits.\n');

end

% Display Result
fprintf('\n=====================================\n');
fprintf('Calculated Path Loss = %.2f dB\n', path_loss);
fprintf('=====================================\n');
