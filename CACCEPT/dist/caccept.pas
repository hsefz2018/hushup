Unit caccept;

    Interface

Procedure newGame;

    Implementation

Uses cacceptlib;

Procedure newGame;
Var
    a, b, c, d, e: Char;
Begin
    {For a := 'a' to 'z' Do inc(b);}
    {WriteLn(makeAttempt('a', 'b', 'c', 'd', 'e'));}
    For a := 'a' to 'z' Do
        For b := 'a' to 'z' Do
            For c := 'a' to 'z' Do
                For d := 'a' to 'z' Do
                    For e := 'a' to 'z' Do
                        If makeAttempt(a, b, c, d, e) = 50 Then Exit;
End;

End.

