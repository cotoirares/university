x = [3.26, 1.89, 2.42, ...];  
n = length(x);
alpha = 0.01;  % say 99% CI => alpha=0.01
s2 = var(x);  % sample variance

chi2_left  = chi2inv(alpha/2, n-1);
chi2_right = chi2inv(1 - alpha/2, n-1);

var_lower = (n-1)*s2 / chi2_right;
var_upper = (n-1)*s2 / chi2_left;
sd_lower  = sqrt(var_lower);
sd_upper  = sqrt(var_upper);

fprintf("99%% CI for variance: [%.4f, %.4f]\n", var_lower, var_upper);
fprintf("99%% CI for std dev: [%.4f, %.4f]\n", sd_lower, sd_upper);

