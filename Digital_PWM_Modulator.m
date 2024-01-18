clear all;
clc;

%% Hyperparameters
n_bit   = 4;
Fs      = 781000;
F0      = 35000;
fs_duty = 10e4;

%% Seed and Noise Generator
rnd_gen = rng(0);
noise_ext   = 0.05 * randn(1, fs_duty);

%% Frequency Response
K    = 2*cos(2*pi*F0/Fs);
tf1  = [1, -1];
tf2  = [1, -2, 1];
tf3  = [1, -3, 3, -1];
tf3m = [1, -(1+K), (1+K), -1];

[h1,w1]   = freqz(tf1);
h1        = mag2db(abs(h1));
[h2,w2]   = freqz(tf2);
h2        = mag2db(abs(h2));
[h3,w3]   = freqz(tf3);
h3        = mag2db(abs(h3));
[h3m,w3m] = freqz(tf3m);
h3m       = mag2db(abs(h3m));

figure(1)
hold on
grid on
plot(w1/pi, h1, color='red')
plot(w2/pi, h2, color='green')
plot(w3/pi, h3, color='blue')
plot(w3m/pi, h3m, color='black')
ylim([-120 20])
title('Frequency Response')
xlabel('\omega / \pi')
ylabel('Magnitude (dB)')
legend('1st Order', '2nd Order', '3rd Order', '3rd Order Modified')
hold off
saveas(gcf, 'Plots\Frequency Response.png')

%% Power Spectral Density
output1  = filter(tf1, 1, noise_ext);
output2  = filter(tf2, 1, noise_ext);
output3  = filter(tf3, 1, noise_ext);
output3m = filter(tf3m, 1, noise_ext);

[psd_1, f1]   = periodogram(output1, kaiser(length(output1), 38), 4096, Fs);
[psd_2, f2]   = periodogram(output2, kaiser(length(output2), 38), 4096, Fs);
[psd_3, f3]   = periodogram(output3, kaiser(length(output3), 38), 4096, Fs);
[psd_3m, f3m] = periodogram(output3m, kaiser(length(output3m), 38), 4096, Fs);

figure(2)
sgtitle('Periodograms')

subplot(221)
hold on
grid on
plot(f1, 10*log10(psd_1), color='red')
title('1st Order')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

subplot(222)
hold on
grid on
plot(f2, 10*log10(psd_2), color='green')
title('2nd Order')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

subplot(223)
hold on
grid on
plot(f3, 10*log10(psd_3), color='blue')
title('3rd Order')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

subplot(224)
hold on
grid on
plot(f3m, 10*log10(psd_3m), color='black')
title('3rd Order Modified')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

saveas(gcf, 'Plots\Periodograms.png')

%% Square Wave Duty Cycle
duty_cycle = zeros(1,fs_duty);
t          = linspace(0,1,fs_duty);
cycles     = 5;

onePeriod    = 0.7 * [ones(1, fs_duty/(2*cycles)), -ones(1, fs_duty/(2*cycles))];
fullWaveForm = repmat(onePeriod, [1, cycles]);

d_noisy = fullWaveForm + noise_ext;

% Quantization
d_quant = round((2^n_bit) * d_noisy);
noise_quant0 = d_quant/(2^n_bit) - d_noisy;

figure(3)
sgtitle('Modulating Wave')

subplot(211)
hold on
grid on
plot(t, d_noisy, color='blue')
title('with External Noise')
xlabel('Time (s)')
ylabel('Amplitude')
hold off

subplot(212)
hold on
grid on
plot(t, d_noisy, color='blue')
plot(t, d_quant/(2^n_bit), color='red');
title('with External Noise and Quantization')
xlabel('Time (s)')
ylabel('Amplitude')
legend('Noisy', 'Quantized')
hold off

saveas(gcf, 'Plots\Duty Cycle.png')

%% Input Wave Generation
sine   = sin(2*pi*50*t);
sine_q = round((2^n_bit)*sine);

saw_thd0   = sawtooth(2*pi*50*t);
saw_q = round((2^n_bit)*saw_thd0);

%% DPWM
dpwm_sine0 = dpwm(d_quant, sine_q, fs_duty);
dpwm_saw0  = dpwm(d_quant, saw_q, fs_duty);

figure(4)
sgtitle('Carrier Wave')

subplot(221)
hold on
plot(t, sine_q/(2^n_bit), color='red')
plot(t, sine, color='blue')
title('Sine')
xlabel('Time (s)')
ylabel('Amplitude')
hold off

subplot(222)
plot(t, dpwm_sine0)
ylim([-0.1, 1.1])
title('DPWM of Sine Wave')
xlabel('Time (s)')
ylabel('Amplitude')
hold off

subplot(223)
hold on
plot(t, saw_thd0, color='blue')
plot(t, saw_q/(2^n_bit), color='red')
title('Sawtooth')
xlabel('Time (s)')
ylabel('Amplitude')
hold off

subplot(224)
plot(t, dpwm_saw0)
ylim([-0.1, 1.1])
title('DPWM of Sawtooth Wave')
xlabel('Time (s)')
ylabel('Amplitude')
hold off

saveas(gcf, 'Plots\Carrier Wave.png')

%% Unfiltered DPWM
[psd_sine0, freq_sine0] = periodogram(dpwm_sine0, kaiser(length(dpwm_sine0), 38), 4096, Fs, 'psd');

sine_snr0 = snr(dpwm_sine0, noise_ext + noise_quant0);
sine_thd0 = thd(dpwm_sine0);
%sine_sndr0 = sinad(dpwm_sine0);
sine_sndr0 = (10^(-sine_snr0/10) + 10^(-sine_thd0/10))^(1/2);

[psd_saw0, freq_saw0] = periodogram(dpwm_saw0,kaiser(length(dpwm_saw0), 38), 4096, Fs, 'psd');

saw_snr0 = snr(dpwm_saw0, noise_ext + noise_quant0);
saw_thd0 = thd(dpwm_saw0);
%saw_sndr0 = sinad(dpwm_saw0);
saw_sndr0 = (10^(-saw_snr0/10) + 10^(-saw_thd0/10))^(1/2);

figure(5)
sgtitle('Unfiltered DPWM Spectral Analysis')

subplot(211)
hold on
grid on
plot(freq_sine0, 10*log10(psd_sine0))
title('PSD with Sine Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

subplot(212)
hold on
grid on
plot(freq_saw0, 10*log10(psd_saw0))
title('PSD with Sawtooth Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

saveas(gcf, 'Plots\Unfiltered DPWM Spectral Analysis.png')

%% 1st Order Sigma-Delta
[SD1_signal, noise_quant1] = sigma_delta1(d_noisy, fs_duty, n_bit);
dpwm_sine1 = dpwm(SD1_signal, sine_q, fs_duty);
dpwm_saw1  = dpwm(SD1_signal, saw_q, fs_duty);

[psd_sine1, freq_sine1] = periodogram(dpwm_sine1, kaiser(length(dpwm_sine1), 38), 4096, Fs, 'psd');

sine_snr1 = snr(dpwm_sine1, noise_ext + noise_quant1);
sine_thd1 = thd(dpwm_sine1);
%sine_sndr1 = sinad(dpwm_sine1);
sine_sndr1 = (10^(-sine_snr1/10) + 10^(-sine_thd1/10))^(1/2);

[psd_saw1, freq_saw1] = periodogram(dpwm_saw1, kaiser(length(dpwm_sine1), 38), 4096, Fs, 'psd');

saw_snr1 = snr(dpwm_saw1, noise_ext + noise_quant1);
saw_thd1 = thd(dpwm_saw1);
%saw_sndr1 = sinad(dpwm_saw1);
saw_sndr1 = (10^(-saw_snr1/10) + 10^(-saw_thd1/10))^(1/2);

figure(6)
sgtitle('1st Order Sigma-Delta Spectral Analysis')

subplot(211)
hold on
grid on
plot(freq_sine1, 10*log10(psd_sine1))
title('PSD with Sine Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

subplot(212)
hold on
grid on
plot(freq_saw1, 10*log10(psd_saw1))
title('PSD with Sawtooth Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

saveas(gcf, 'Plots\1st Order Sigma-Delta Spectral Analysis.png')

%% 2nd Order Sigma-Delta
[SD2_signal, noise_quant2] = sigma_delta2(d_noisy, fs_duty, n_bit);
dpwm_sine2 = dpwm(SD2_signal, sine_q, fs_duty);
dpwm_saw2  = dpwm(SD2_signal, saw_q, fs_duty);

[psd_sine2, freq_sine2] = periodogram(dpwm_sine2, kaiser(length(dpwm_sine2), 38), 4096, Fs, 'psd');

sine_snr2 = snr(dpwm_sine2, noise_ext + noise_quant2);
sine_thd2 = thd(dpwm_sine2);
%sine_sndr2 = sinad(dpwm_sine2);
sine_sndr2 = (10^(-sine_snr2/10) + 10^(-sine_thd2/10))^(1/2);

[psd_saw2, freq_saw2] = periodogram(dpwm_saw2, kaiser(length(dpwm_saw2), 38), 4096, Fs, 'psd');

saw_snr2 = snr(dpwm_saw2, noise_ext + noise_quant2);
saw_thd2 = thd(dpwm_saw2);
%saw_sndr2 = sinad(dpwm_saw2);
saw_sndr2 = (10^(-saw_snr2/10) + 10^(-saw_thd2/10))^(1/2);

figure(7)
sgtitle('2nd Order Sigma-Delta Spectral Analysis')

subplot(211)
hold on
grid on
plot(freq_sine2, 10*log10(psd_sine2))
title('PSD with Sine Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

subplot(212)
hold on
grid on
plot(freq_saw2, 10*log10(psd_saw2))
title('PSD with Sawtooth Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

saveas(gcf, 'Plots\2nd Order Sigma-Delta Spectral Analysis.png')

%% 3rd Order Sigma-Delta
[SD3_signal, noise_quant3] = sigma_delta3(d_noisy, fs_duty, n_bit);
dpwm_sine3 = dpwm(SD3_signal, sine_q, fs_duty);
dpwm_saw3  = dpwm(SD3_signal, saw_q, fs_duty);

[psd_sine3, freq_sine3] = periodogram(dpwm_sine3, kaiser(length(dpwm_sine3), 38), 4096, Fs, 'psd');

sine_snr3 = snr(dpwm_sine3, noise_ext + noise_quant3);
sine_thd3 = thd(dpwm_sine3);
%sine_sndr3 = sinad(dpwm_sine3);
sine_sndr3 = (10^(-sine_snr3/10) + 10^(-sine_thd3/10))^(1/2);

[psd_saw3, freq_saw3] = periodogram(dpwm_saw3, kaiser(length(dpwm_saw3), 38), 4096, Fs, 'psd');

saw_snr3 = snr(dpwm_saw3, noise_ext + noise_quant3);
saw_thd3 = thd(dpwm_saw3);
%saw_sndr3 = sinad(dpwm_saw3);
saw_sndr3 = (10^(-saw_snr3/10) + 10^(-saw_thd3/10))^(1/2);

figure(8)
sgtitle('3rd Order Sigma-Delta Spectral Analysis')

subplot(211)
hold on
grid on
plot(freq_sine3, 10*log10(psd_sine3))
title('PSD with Sine Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

subplot(212)
hold on
grid on
plot(freq_saw3, 10*log10(psd_saw3))
title('PSD with Sawtooth Carrier')
xlabel('Frequency (Hz)')
ylabel('PSD')
hold off

saveas(gcf, 'Plots\3rd Order Sigma-Delta Spectral Analysis.png')

%% THD, SNDR
varnames = {'Unfiltered', '1st_Order', '2nd_Order', '3rd_Order'};
rownames = {'THD_Sine', 'THD_Sawtooth', 'SNDR_Sine', 'SNDR_Sawtooth'};

unf    = [sine_thd0, saw_thd0, sine_sndr0, saw_sndr0];
first  = [sine_thd1, saw_thd1, sine_sndr1, saw_sndr1];
second = [sine_thd2, saw_thd2, sine_sndr2, saw_sndr2];
third  = [sine_thd3, saw_thd3, sine_sndr3, saw_sndr3];

table = table(unf', first', second', third', 'VariableNames', varnames, 'RowNames', rownames);

figure(9)
stackedplot(rows2vars(table), LineStyle="-", Color='k', Marker=".", MarkerEdgeColor='r', MarkerSize=20);
title('THD and SNDR Behaviour')
xlabel('Unfiltered                        1st Order                        2nd Order                        3rd Order')

saveas(gcf, 'Plots\THD and SNDR Behaviour.png')

%% Functions
% Digital Pulse Width Modulator
function dpwm_signal = dpwm(duty_cycle, modulating_wave, duty_sampling_time)
    dpwm_signal = zeros(1,duty_sampling_time);
    for i = 1:duty_sampling_time
        if modulating_wave(i) <= duty_cycle(i)
            dpwm_signal(i) = 1;
        else
            dpwm_signal(i) = 0;
        end
    end
end

% 1st Order Filter
function [SD1_signal, quantiz_err1] = sigma_delta1(duty_cycle, duty_sample_time, Nbits)
    quantiz_err1 = zeros(1,duty_sample_time);
    tmp         = zeros(1, duty_sample_time);
    SD1_signal  = zeros(1,duty_sample_time);
    
    for i = 1:duty_sample_time
        if i==1
            tmp(i)         = duty_cycle(i);
            SD1_signal(1)  = round((2^Nbits) * tmp(1));
            quantiz_err1(i) = (duty_cycle(i) - SD1_signal(i) / 2^Nbits);
        else
            tmp(i)         = duty_cycle(i) + quantiz_err1(i-1);
            SD1_signal(i)  = round((2^Nbits) * tmp(i));
            quantiz_err1(i) = (tmp(i) - SD1_signal(i) / 2^Nbits);
        end
    end
end

% 2nd Order Filter
function [SD2_signal, quantiz_err2] = sigma_delta2(duty_cycle, duty_sample_time, Nbits)
    quantiz_err2 = zeros(1,duty_sample_time);
    tmp         = zeros(1,duty_sample_time);
    SD2_signal  = zeros(1,duty_sample_time);
    
    for i = 1:duty_sample_time
        if i==1
            tmp(i)         = duty_cycle(i);
            SD2_signal(i)  = round(2^Nbits * tmp(i));
            quantiz_err2(i) = (tmp(i) - SD2_signal(i) / 2^Nbits);
        elseif i==2
            tmp(i)         = duty_cycle(i)-2 * quantiz_err2(1);
            SD2_signal(i)  = round(2^Nbits * tmp(i));
            quantiz_err2(i) = (tmp(i) - SD2_signal(i) / 2^Nbits);
        else
            tmp(i)         = duty_cycle(i) - 2*quantiz_err2(i-1) + quantiz_err2(i-2);
            SD2_signal(i)  = round(2^Nbits * tmp(i));
            quantiz_err2(i) = (tmp(i) - SD2_signal(i) / 2^Nbits);
        end
    end
end

% 3rd Order Filter
function [SD3_signal, quantiz_err3] = sigma_delta3(duty_cycle, duty_sample_time, Nbits)
    quantiz_err3 = zeros(1,duty_sample_time);
    tmp         = zeros(1,duty_sample_time);
    SD3_signal  = zeros(1,duty_sample_time);
    
    for i = 1:duty_sample_time
        if i==1
            tmp(i)         = duty_cycle(i);
            SD3_signal(i)  = round(2^Nbits * tmp(i));
            quantiz_err3(i) = (tmp(i) - SD3_signal(i) / 2^Nbits);
        elseif i==2
            tmp(i)         = duty_cycle(i) - 3*quantiz_err3(1);
            SD3_signal(i)  = round(2^Nbits * tmp(i));
            quantiz_err3(i) = (tmp(i) - SD3_signal(i) / 2^Nbits);
        elseif i==3
            tmp(i)         = duty_cycle(i) - 3*quantiz_err3(2) + 3*quantiz_err3(1);
            SD3_signal(i)  = round(2^Nbits * tmp(i));
            quantiz_err3(i) = (tmp(i) - SD3_signal(i) / 2^Nbits);
        else
            tmp(i)         = duty_cycle(i) - 3*quantiz_err3(i-1) + 3*quantiz_err3(i-2) - quantiz_err3(i-3);
            SD3_signal(i)  = round(2^Nbits * tmp(i));
            quantiz_err3(i) = (tmp(i) - SD3_signal(i) / 2^Nbits);
        end
    end
end