% replaceAll(E1-elem to replace, E2-replacer, L-list, R-result list)
% flow model(i,i,i,i),  (i,i,i,o)
replaceAll(_,_,[],[], 0).
replaceAll(E1,E2,[E1|T],[E2|R], C):-
    replaceAll(E1,E2,T,R, C1),
    C is C1 + 1,
    !.
replaceAll(E1,E2,[H|T],[H|R], C):-
    replaceAll(E1,E2,T,R, C).
 
% maxList(L-list, M-max, R-result)
% flow model (i,i,i),   (i,i,o)
maxList([],M,M).
maxList([H|T],M,R):-
    H>M,
    NewM=H,
    maxList(T,NewM,R),!.
maxList([H|T],M,R):-
    M>=H,
    maxList(T,M,R).
mainMaxList(L,R):-
    maxList(L,0,R).
 
% maxHeteroList(L-list, M-max, R-result)
% flow model (i,i,i),   (i,i,o)
maxHeteroList([],M,M).
maxHeteroList([H|T],M,R):-
    is_list(H),
    maxHeteroList(T,M,R).
maxHeteroList([H|T],M,R):-
    \+ is_list(H),
    H>M,
    NewM=H,
    maxHeteroList(T,NewM,R),!.
maxHeteroList([H|T],M,R):-
    \+ is_list(H),
    M>=H,
    maxHeteroList(T,M,R).
mainMaxHeteroList(L,R):-
    maxHeteroList(L,0,R).
 
% replaceMax(L-list, M-max, R-result list)
% flow model (i,i,i),   (i,i,o)
replaceMax([],_, []).
replaceMax([H|T], M,[NewH|R]) :-
    is_list(H),
    mainMaxList(H, Max),
    replaceAll(M, Max, H, NewH, 0),
    replaceMax(T,M,R),!.
replaceMax([H|T],M, [H|R]) :-
    \+ is_list(H), 
    replaceMax(T,M,R).
mainReplaceMax(L,R):-
    mainMaxHeteroList(L,M),
    replaceMax(L,M,R).

%Test examples:
%mainReplaceMax([1,[2,5,7],4,5,[1,4],3,[1,3,5,8,5,4],5,[5,9,1],2],R). -> R = [1, [2, 7, 7], 4, 5, [1, 4], 3, [1, 3, 8, 8, 8, 4], 5, [9, 9, 1], 2]
%replaceAll(1,3,[1,7,8,1,2,5,1],R). -> R=[3,7,8,3,2,5,3]

