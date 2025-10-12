% Base case - empty list has one permutation
permutation([], []).

% Select any element and permute the rest
permutation(List, [H|T]) :-
    select(H, List, Rest),    % Select any element H from List
    permutation(Rest, T).     % Permute the remaining elements

% select/3 predicate definition
select(X, [X|T], T).
select(X, [H|T], [H|R]) :- select(X, T, R).

% Usage:
% ?- permutation([1,2,3], X).
% Will generate all possible orderings
