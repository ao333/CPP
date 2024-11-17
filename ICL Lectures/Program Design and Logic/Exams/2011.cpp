/*
1a
i) AX[PGD(X)->(SP(X)vWT(X))^~(SP(X)^WT(X))]

ii) AX(SP(X)^~EW(Weight(X,W)^(W<150))^
    AY(WT(Y)^~EW(Weight(X,W)^(W<100))

iii) AX,WX[(WT(X)^Weight(X,WX))^EY,WY(SP(Y)^Weight(Y,WY))->(W1<W2)]

iv) EB,S[B(B)^SP(S)^Has(B,S)]^
    EB,W[B(B)^WT(B)^Has(B,W)]^
	~EB,S,W[B(B)^SP(S)^WT(W)^Has(B,S)^Has(B,W)]

v) AB,D[B(B)^Pgd(D)->ADW,BW(Weight(D,DW)^Sup(B,BW)^(DW<BW)]

b
~AX[P(X)->EY(Q(X,Y))]^~AXEY[R(X,a,Y)] Demorgan
EX~[P(X)->EY(Q(X,Y))]^EX~EY[R(X,a,Y)] at least one false - not all true
EX~[P(X)->EY(Q(X,Y))]^EXAY~[R(X,a,Y)] all false - none true
EX~[~P(X)vEY(Q(X,Y))]^EXAY~[R(X,a,Y)] Implication
EX[P(X)^~EY(Q(X,Y))]^EXAY~R(X,a,Y)    Demorgan
EX[P(X)^AY~Q(X,Y)]^EXAY~R(X,a,Y)      all false - none true

c
1. EX[P(X)^AY~Q(X,Y)]^EXAY~R(X,a,Y) b
2. EX[P(X)^AY~Q(X,Y)]               ^E,1
3. EXAY~R(X,a,Y)                    ^E,1
  4. P(b)^AY~Q(b,Y)                 Assume
  5. P(b)                           ^E,4
  6. AY~Q(b,Y)                      ^E,4
  7. ~Q(b,a)                        AE,6
  8. EX[~Q(X,a)]                    EI,7
9. EX[~Q(X,a)]                      EE,3,4,8
*/