x = [3.26, 1.89, 2.42, ...];  % your sample
n = length(x);
xbar = mean(x);
s = std(x);
alpha = 0.05;
tcrit = tinv(1 - alpha/2, n - 1);

margin_of_error = tcrit * s / sqrt(n);
CI_lower = xbar - margin_of_error;
CI_upper = xbar + margin_of_error;
fprintf("95%% CI for the mean: [%.4f, %.4f]\n", CI_lower, CI_upper);
es; sleep 1; done
:
