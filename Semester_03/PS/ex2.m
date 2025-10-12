% a manufacturer of gunpowder has developed a new powder which was tested in 12 shells. the resulting muzzle velocities in m/s are (they are assumed to be approximately normally distributed)
% [1001.7, 975.0, 978.3, 988.3, 978.7, 988.9, 1000.3, 979.2, 968.9, 983.5, 999.2, 985.6]

% task a: at the 5% significance leve, does the data suggest that, on average, the muzzles are faster than 995 m/s?
% task b: find a 99% confidence interval for the standard deviation of the velocity of shells of this type

clear All
clc

a = [1001.7, 975.0, 978.3, 988.3, 978.7, 988.9, 1000.3, 979.2, 968.9, 983.5, 999.2, 985.6];

alpha = 0.05;

[h, p, ci, stats] = ttest(a, 995, alpha, 1);

fprintf('POINT a.\n');

if h == 0
    fprintf('H0 is not rejected, the muzzles are not faster than 995 m/s\n');
else
    fprintf('H0 is rejected, the muzzles are faster than 995 m/s\n');
end

fprintf('P-value is %f\n', p);

fprintf('\nPOINT b.\n');

alpha = 0.01;
n = length(a);
s = std(a);
q1 = chi2inv(alpha/2, n-1);
q2 = chi2inv(1-alpha/2, n-1);

ci = [sqrt((n-1)*s^2/q2), sqrt((n-1)*s^2/q1)];

fprintf('Confidence interval for the standard deviation is (%f, %f)\n', ci(1), ci(2));

