Unit cacceptlib;

    Interface

Function makeAttempt(a, b, c, d, e: Char): Integer;

    Implementation

Uses caccept;

Var
    s: String;
    totCases, succCases: Integer;
    curAtts: Int64;
    curSucc: Boolean;
    atts: Array [1 .. 32] of Int64;

Function makeAttempt(a, b, c, d, e: Char): Integer;
Var
    t: String;
    i, j, distinct, matched: Integer;
Begin
    inc(curAtts);
    t := upcase(a) + upcase(b) + upcase(c) + upcase(d) + upcase(e);

    distinct := 0; matched := 0;
    For i := 1 to 5 Do
        If s[i] = t[i] Then inc(matched);
    For i := 1 to 5 Do Begin
        For j := 1 to 5 Do
            If s[i] = t[j] Then Begin
                inc(distinct); Break;
            End;
    End;
    If matched = 5 Then curSucc := True;
    Exit(matched * 10 + (distinct - matched));
End;

Function ValidateInput: Boolean;
Var
    i, j: Integer;
Begin
    If Length(s) <> 5 Then Begin
        WriteLn(StdErr, 'Invalid input: incorrect string length, should be 5');
        Exit(False);
    End;
    For i := 1 to 5 Do
        For j := 1 to 5 Do
            If (i <> j) and (s[i] = s[j]) Then Begin
                WriteLn(StdErr, 'Invalid input: duplicate characters (''', s[i], ''')');
                Exit(False);
            End;
    Exit(True);
End;

Var
    i: Integer;
Begin
    totCases := 0;
    succCases := 0;
    While not EOF(Input) Do Begin
        ReadLn(s); s := Upcase(s);
        If not ValidateInput Then Continue;

        inc(totCases);
        WriteLn(StdErr, 'Test case #', totCases);
        curAtts := 0;
        curSucc := False;
        newGame;
        If curSucc Then Begin
            inc(succCases);
            atts[totCases] := curAtts;
        End;
    End;

    WriteLn('mekkadondondondondon');
    WriteLn(totCases, ' ', succCases);
    For i := 1 to totCases Do Write(atts[i], ' ');
    WriteLn;
    Close(Output);
End.

