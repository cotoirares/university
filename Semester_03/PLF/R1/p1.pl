% transform a list in a set, in the order of last occurences of elements

elem_in_list(X, [X|_]).
elem_in_list(X, [_|T]) :- elem_in_list(X, T).

unique_elems([], S, S).

unique_elems([H|T], S, R) :-
    \+ elem_in_list(H, S),
    unique_elems(T, [H|S], R).

unique_elems([H|T], S, R) :-
    elem_in_list(H, S),
    unique_elems(T, S, R).

reverse_list([], R, R).
reverse_list([H|T], Acc, R) :-
    reverse_list(T, [H|Acc], R).

last_occurrence_set(L, R) :-
    reverse_list(L, [], RevL),
    unique_elems(RevL, [], UniqueL),
    reverse_list(UniqueL, [], R).

