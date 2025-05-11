% Function that computes the sum of the given function for each omega value
function sum_results = compute_sum(omegas, Ts)
    n = -25:25;
    x_n = cos(3*pi/2 * n .* Ts) .* exp(-((n.*Ts).^2)/2);

    sum_results = zeros(size(omegas));

    % Compute the sum for each omega value
    for i = 1:length(omegas)
        sum_results(i) = sum(x_n .* exp(-1j * n * omegas(i) * Ts));
    end
end

omega = linspace(-3 * pi, 3 * pi, 500);
fs = 2016/1000;
Ts = 1 / Ts;
X = compute_sum(omega, Ts);

subplot(2,1,1);
plot(omega, abs(X));
title('Ts = 1000/2016');
xlabel('\omega');
ylabel('X_\delta(\omega)');

Ts = Ts / 2.;
X = compute_sum(omega, Ts);

subplot(2,1,2);
plot(omega, abs(X));
title('Ts = 500/2016');
xlabel('\omega');
ylabel('X_\delta(\omega)');

grid on;