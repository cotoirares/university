clear All
clc
standard = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37];
new = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31];
alpha = 0.05;
[h, p, ci, stats] = vartest2(standard, new, alpha, 0);
fprintf('Point a.\n');

if h == 0
        fprintf('H0 is not rejected - sigmas are equal\n');
else
        fprintf('H0 is rejected - population variances differ \n');
end

q1 = finv(alpha/2, stats.df1, stats.df2);
q2 = finv(alpha/2, stats.df2, stats.df1);

fprintf("Observed value %f\n", stats.fstat);
fprintf('P-value is %f\n', p);
fprintf('Rejection region R is (-inf, %f) + (%f, inf)\n', q1, q2);

[h1, p1, ci1, stats1] = ttest2(standard, new, alpha, 1, 'equal');

fprintf('\nPOINT b.\n');

if h1 == 0
    fprintf("H0 is not rejected. The average assembling times are equal.\n");
else
    fprintf("H0 is rejected. The average assembling times are not equal.\n");
end

ci = [stats1.tstat - tinv(1-alpha/2, stats1.df)*stats1.sd/sqrt(length(standard)), stats1.tstat + tinv(1-alpha/2, stats1.df)*stats1.sd/sqrt(length(standard))];
fprintf('Confidence interval for the difference of the average assembling times is (%f, %f)\n', ci(1), ci(2));

