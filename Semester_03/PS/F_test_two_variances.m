A = [ ... ];  % sample for group A
B = [ ... ];  % sample for group B

alpha = 0.05;
varA = var(A);      % sample variance
varB = var(B);
nA = length(A);
nB = length(B);

Fstat = varA/varB;  % test statistic
% We want the p-value for H0: sigmaA^2 = sigmaB^2 (two-sided)

% The two-sided test basically checks
% P = 2 * min( P(F >= Fstat), P(F <= Fstat) ),
% where F ~ F_{nA-1, nB-1}.

p_one_tail = 1 - fcdf(Fstat, nA - 1, nB - 1);
% If Fstat>1 => we check the upper tail
if (Fstat >= 1)
   pval = 2 * p_one_tail;   % symmetrical
else
   pval = 2 * (1 - p_one_tail); 
end

disp("F statistic: "), disp(Fstat)
disp("p-value (two-sided): "), disp(pval)

% Decision
if pval < alpha
  disp("Reject H0: the variances differ significantly.")
else
  disp("Fail to reject H0: no evidence that variances differ.")
end

