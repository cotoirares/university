#########################
#  COMMON SETUP
#########################
clear; clc;

#########################
#  PROBLEM 1 EXAMPLE
#  (Water bottles from two suppliers)
#########################
printf("\n===== PROBLEM 1: Water bottles =====\n");

## Suppose the store owner has data from Supplier A and B:
A = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023];
B = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975];

alpha = 0.05;

##
## (a) At the 5% level, do the population variances differ? 
##     --> F-test
##
nA = length(A);
nB = length(B);
varA = var(A);
varB = var(B);
Fstat = varA / varB;

% Two-sided p-value for an F-test
p_upper = 1 - fcdf(Fstat, nA-1, nB-1);
if (Fstat >= 1)
   pVal = 2 * p_upper;
else
   pVal = 2 * (1 - p_upper);
end

fprintf("F statistic (A vs B) = %.4f\n", Fstat);
fprintf("p-value (two-sided)  = %.4f\n", pVal);
if pVal < alpha
   fprintf("=> Reject H0 => The variances differ at %g%% significance.\n", alpha*100);
else
   fprintf("=> Fail to reject H0 => No evidence of different variances.\n");
end

##
## (b) At 5% significance, does Supplier A seem more “accurate” (or different on average) than B?
##     Often we do a 2-sample t-test for difference in means.
##
[H, P, CI, STATS] = ttest2(A, B, "alpha", alpha);
fprintf("\nTwo-sample t-test results (A vs B):\n");
fprintf("Test statistic t = %.4f, df=%.4f\n", STATS.tstat, STATS.df);
fprintf("p-value (two-sided) = %.4f\n", P);
fprintf("95%% CI for mean(A)-mean(B) is [%.4f, %.4f]\n", CI(1), CI(2));
if H==1
   fprintf("=> Reject H0 => The means differ significantly at the 5%% level.\n");
   if mean(A) < mean(B)
     printf("   (Supplier A is *lower* on average.)\n");
   else
     printf("   (Supplier A is *higher* on average.)\n");
   end
else
   fprintf("=> Fail to reject H0 => No significant difference in means at 5%%.\n");
end


#########################
#  PROBLEM 2 EXAMPLE
#  (Nickel powders: 1-sample t-test & CIs)
#########################
printf("\n===== PROBLEM 2: Nickel powders =====\n");

## Data on nickel particle sizes:
x = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, ...
     3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

n  = length(x);
xbar = mean(x);
s  =  std(x);

printf("Sample mean = %.4f, Sample std dev = %.4f, n=%d\n", xbar, s, n);

##
## (a)  Find a 95% CI for the average particle size
##
alpha_CI = 0.05;
tcrit = tinv(1 - alpha_CI/2, n - 1);
MoE = tcrit * s / sqrt(n);
CI_lower = xbar - MoE;
CI_upper = xbar + MoE;
fprintf("95%% CI for the mean: [%.4f, %.4f]\n", CI_lower, CI_upper);

##
## (b)  At (say) the 5% significance level, test if the mean is smaller than 3
##      => One-sample t-test
##
mu0 = 3;  % hypothesized mean
[H_one, P_one, CI_one, STATS_one] = ttest(x, mu0, "alpha", 0.05);
fprintf("\nOne-sample t-test vs mu=3 (two-sided by default):\n");
fprintf("T statistic = %.4f, df=%.4f\n", STATS_one.tstat, STATS_one.df);
fprintf("p-value (two-sided) = %.4f\n", P_one);

if H_one == 1
  % We rejected mean=3 in a two-sided sense.
  if STATS_one.tstat < 0
     fprintf("=> The sample mean is significantly *less* than 3 (at 5%%, two-sided).\n");
  else
     fprintf("=> The sample mean is significantly *greater* than 3 (at 5%%, two-sided).\n");
  end
else
  fprintf("=> Fail to reject H0 => No evidence that mean != 3.\n");
end

% For strictly one-sided: if we want "mean < 3" we check that
% STATS_one.tstat < 0 *and* P_one/2 < alpha.  See notes.

##
## (c)  (Alternate version) 99% CI for the standard deviation
##
alpha_sd = 0.01;
chi2_left  = chi2inv(alpha_sd/2, n-1);
chi2_right = chi2inv(1 - alpha_sd/2, n-1);
var_lower = (n-1)*s^2 / chi2_right;
var_upper = (n-1)*s^2 / chi2_left;
fprintf("\n99%% CI for the variance: [%.4f, %.4f]\n", var_lower, var_upper);
fprintf("99%% CI for the std dev: [%.4f, %.4f]\n", sqrt(var_lower), sqrt(var_upper));


#########################
#  PROBLEM 3 EXAMPLE
#  (Assembling times: 2-sample F-test + difference of means)
#########################
printf("\n===== PROBLEM 3: Assembling times =====\n");

## Standard method vs. New method
Standard = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37];
New      = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31];

varS = var(Standard);
varN = var(New);
nS  = length(Standard);
nN  = length(New);

Fstat = varS / varN;
p_upper = 1 - fcdf(Fstat, nS-1, nN-1);
if (Fstat >= 1)
   pVal = 2 * p_upper;
else
   pVal = 2 * (1 - p_upper);
end

fprintf("F statistic (Standard vs New) = %.4f\n", Fstat);
fprintf("p-value (two-sided) = %.4f\n", pVal);

alpha_asm = 0.05;
if pVal < alpha_asm
   fprintf("=> Reject H0 => The variances differ (5%% level).\n");
else
   fprintf("=> Fail to reject H0 => No evidence of different variances (5%%).\n");
end

##
## Now a 95% CI for the difference of means (Standard - New).
## ttest2() returns the 95% CI for mean(Standard) - mean(New).
##
[H_asm, P_asm, CI_asm, STATS_asm] = ttest2(Standard, New, "alpha", 0.05);
fprintf("\nTwo-sample t-test (Standard vs New):\n");
fprintf("Test statistic t=%.4f, df=%.4f\n", STATS_asm.tstat, STATS_asm.df);
fprintf("p-value (two-sided) = %.4f\n", P_asm);
fprintf("95%% CI for mean(Standard) - mean(New): [%.3f, %.3f]\n", CI_asm(1), CI_asm(2));

if H_asm == 1
   fprintf("=> Reject H0 => The means differ at 5%%.\n");
else
   fprintf("=> Fail to reject H0 => No significant difference in means at 5%%.\n");
end

printf("\n===== END OF SCRIPT =====\n");

