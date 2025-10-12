% remove_doubles(L1...Ln, R) = 
% 				[], n = 0
% 				remove_doubles(L2...Ln, L1 U R), if no_occ(L1...Ln, L1) = 1
% 				remove_doubles(L2...Ln, R), if no_occ(L1...Ln, L1) > 1
%	
%	no_occ(L1...Ln, e, C) = 
%				0, n = 0
%				no_occ(L2...Ln, e, C+1), L1 = e
%				no_occ(L2...Ln, e, C), L1 != e
%				

no_occ([], _, 0).
no_occ([H|T], E, C):-
    H = E,
    no_occ(T, E, C1),
    C is C1 + 1.

no_occ([H|T], E, C):-
    H \= E,
    no_occ(T, E, C).

remove_doubles([], []).
remove_doubles([H|T], R) :-
    no_occ(T, H, C),
    C =:= 0, % Keep the element if it is not a duplicate
    remove_doubles(T, RT),
    R = [H|RT].
remove_doubles([H|T], R) :-
    no_occ(T, H, C),
    C > 0, % Skip the element if it has duplicates
    remove_doubles(T, R).

merge_sort([], []).
merge_sort([X], [X]).

merge_sort(List, Sorted) :-
  split_list(List, Left, Right),
  merge_sort(Left, SortedLeft),
  merge_sort(Right, SortedRight),
  merge(SortedLeft, SortedRight, Sorted).

split_list([], [], []).
split_list([X], [X], []).
split_list([X,Y|Tail], [X|Left], [Y|Right]) :-
  split_list(Tail, Left, Right).

merge([], List2, List2).
merge(List1, [], List1).
merge([H1|T1], [H2|T2], [H1|Merged]) :-
  H1 =< H2,
  !,
  merge(T1, [H2|T2], Merged).
merge([H1|T1], [H2|T2], [H2|Merged]) :-
  merge([H1|T1], T2, Merged).

main_method([], []).
main_method(L, R):-
    remove_doubles(L, R1),
    merge_sort(R1, R).
