is_sorted([]).
is_sorted([_]).
is_sorted([X, Y | T]):- X=<Y, is_sorted([Y|T]).
