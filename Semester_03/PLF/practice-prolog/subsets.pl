% Base case - empty set has empty subset
subset([], []).

% For each element, we either include it or we don't
subset([H|T], [H|R]) :- subset(T, R).  % Include H
subset([H|T], R) :- subset(T, R).      % Skip H

% Usage:
% ?- subset([1,2,3], X).
% Will generate: [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]
