% Define parameters
Am = 1;         % Amplitude of message signal
Ac = 1;         % Amplitude of carrier signal
fm = 2016/4.;   % Frequency of message signal (Hz)
fc = 2016/2.;   % Frequency of carrier signal (Hz)
fs = 2016;      % Sampling frequency (must satisfy Nyquist criterion)
T  = .01/fs;    % Sampling period
t  = 0:T:1;     % Time vector

% Define message signal m(t) and carrier signal c(t)
mt = Am*cos(2*pi*fm*t);
ct = Ac*cos(2*pi*fc*t);

% Calculate modulated signal s(t)
st = mt .* ct;

subplot(3,1,1);
plot(t, mt);
title('Message Signal m(t)');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(3,1,2);
plot(t, ct);
title('Carrier Signal c(t)');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(3,1,3);
plot(t, st);
title('Modulated Signal s(t)');
xlabel('Time (s)');
ylabel('Amplitude');

% Calculate and plot magnitude spectrum of modulated signal
figure;
L = length(st);
Y = fft(st);
P2 = abs(Y/L);
f = (0:L/190);
plot(f,P2(1:floor(L/190 + 1)));
title('Magnitude Spectrum of Modulated Signal');
xlabel('Frequency (Hz)');
ylabel('|S(f)|');