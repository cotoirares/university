% Our two datasets:
A = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023];
B = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975];

alpha = 0.05;  % significance level

% 2-sample t-test. By default, ttest2 uses the 'unequal' variance assumption (Welch).
[H, P, CI, STATS] = ttest2(A, B, "alpha", alpha);
disp("Reject H0 that means are equal (two-sided)?: "), disp(H)
disp("p-value (two-sided): "), disp(P)
disp("95% CI for (mean(A) - mean(B)) (two-sided): "), disp(CI)
disp("Test statistic info:"), disp(STATS)

% Interpretation:
% - If H=1, we reject the hypothesis "mean(A)=mean(B)" in favor of "mean(A) != mean(B)".
% - The confidence interval for mean(A)-mean(B). If it doesn't contain 0, that also indicates difference.
% - For a one-sided scenario (say "Is mean(A) < mean(B)?"), interpret carefully the sign of STATS.tstat.

