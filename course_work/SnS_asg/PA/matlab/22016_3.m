omega_a = 10000;
omega = linspace(0, 100000, 2000);

function resp = compute_response(Q, omega_a, omega)
    resp = (1i .* omega) .^2 + (omega_a / Q) .* (1i .* omega) + omega_a^2;
    resp = abs(1 ./ resp);
    resp = 20 .* log10(resp);
end

resp1 = compute_response(2/5, omega_a, omega);
resp2 = compute_response(  1, omega_a, omega);
resp3 = compute_response(200, omega_a, omega);

set(gcf, 'Units', 'inches', 'Position', [0, 0, 9, 6]);
plot(omega, resp1, omega, resp2, omega, resp3);
legend('Q=2/5', 'Q=1', 'Q=200');
xlabel('\omega');
ylabel('Frequency response of the system');
title('Magnitute spectrum of frequency response of system');
grid on;