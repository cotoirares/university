% longest_seq(L1..Ln) = longest_seq(L1..Ln, [], 0, [], 0)
% longest_seq(L1..Ln, ResInter, Lung, Res, LungRes) =
% 			n = 0, []
% 			longest_seq(L2..Ln, L1 U ResInter, Lung + 1, Res, LungRes), if L1 % 2 = 0
% 			longest_seq(L2..Ln, [], 0, max_length(Res, ResInter), max(Lung, LungRes)), if L1 % 2 = 1		

lon([], _, _, Res, _, Res).
lon([H|T], ResInter, LenResInter, _, LenRes, Rez):-
    H mod 2 =:= 0,
    append(ResInter, [H], NewResInter),
    LenResInter1 is LenResInter + 1,
    LenResInter1 > LenRes,
    lon(T, NewResInter, LenResInter1, NewResInter, LenResInter1, Rez).

lon([H|T], ResInter, LenResInter, Res, LenRes, Rez):-
    H mod 2 =:= 0,
    append(ResInter, [H], NewResInter),
    LenResInter1 is LenResInter + 1,
    LenResInter1 =< LenRes,
    lon(T, NewResInter, LenResInter1, Res, LenRes, Rez).

lon([H|T], _, _, Res, LenRes, Rez):-
    H mod 2 =:= 1,
    lon(T, [], 0, Res, LenRes, Rez).

lon(L, R):- lon(L, [], 0, [], 0, R).
