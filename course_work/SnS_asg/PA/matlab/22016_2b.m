% Define the range of omega values
omega = linspace(-3*pi, 3*pi, 1000);

% Compute values of the function
X = (1/(2*pi)) * exp(-((omega - (3*pi/2)).^2)/2);

% Plot the function
plot(omega, X, 'LineWidth', 2);
title('$\frac{1}{2\pi} \cdot e^{\frac{- \left(\omega - \frac{3\pi}{2}\right)^2}{2}}$', 'Interpreter', 'latex');
xlabel('\omega');
ylabel('f(\omega)');
grid on;