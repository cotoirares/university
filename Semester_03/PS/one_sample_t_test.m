% Suppose our data are stored in a vector x
x = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, ...
     2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

mu0 = 3;            % The value we want to test against
alpha = 0.05;       % Significance level

% 1) One-sample t-test. By default, ttest() in Octave is a two-sided test,
% so we’ll do a small trick for a one-sided test.

[H, P, CI, STATS] = ttest(x, mu0, "alpha", alpha); 
% The above is a two-sided test of H0: mean(x)=3
% If H=1, you reject H0 in favor of mean(x) != 3

% If you want to see whether mean(x) < 3, you can inspect the sign of the test statistic:
% STATS.tstat < 0 and H=1 would indicate mean(x) is significantly less than 3.

% Let's print out some results:
disp("Test decision (two-sided):"), disp(H)
disp("p-value (two-sided):"), disp(P)
disp("95% CI for the mean (two-sided):"), disp(CI)
disp("Test statistic info:"), disp(STATS)

% For a truly one-sided test in code, you can do:
% (Alternatively, you can just interpret the two-sided result.)

