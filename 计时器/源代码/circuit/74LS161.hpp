#ifndef _74LS161
#define _74LS161
#include "mytype.hpp"
#include "LogicGate.hpp"

bool func_JK(bool J,bool K,bool Q,bool R){
    return AND(OR(AND(J,NOT(Q)),AND(NOT(K),Q)),R);
}

void func_74161(cir_74161& t){
    bitset<4>&Q=t.Q,&D=t.D;
    bool &LD=t.LD,&EP=t.EP,&ET=t.ET,&RD=t.RD,&C=t.C;
    bool G1=NOT(LD),
        G4=AND(EP,ET),
        G5=AND(Q[0],G4),
        G6=AND({Q[0],Q[1],G4}),
        G7=AND({Q[0],Q[1],Q[2],G4}),
        G9=NAND(G1,D[0]),
        G8=NAND(G1,G9),
        G11=NAND(G1,D[1]),
        G10=NAND(G1,G11),
        G13=NAND(G1,D[2]),
        G12=NAND(G1,G13),
        G15=NAND(G1,D[3]),
        G14=NAND(G1,G15),
        G16=OR(G1,G4),
        G17=OR(G1,G5),
        G18=OR(G1,G6),
        G19=OR(G1,G7);
    bool J[4]={AND(G8,G16),AND(G10,G17),AND(G12,G18),AND(G14,G19)};
    bool K[4]={AND(G9,G16),AND(G11,G17),AND(G13,G18),AND(G15,G19)};

    C=AND({ET,Q[0],Q[1],Q[2],Q[3]});
    Q[0]=func_JK(J[0],K[0],Q[0],RD);
    Q[1]=func_JK(J[1],K[1],Q[1],RD);
    Q[2]=func_JK(J[2],K[2],Q[2],RD);
    Q[3]=func_JK(J[3],K[3],Q[3],RD);
}

void start_74161(cir_74161& t){
    t.RD=1;
}
void start_74161(initializer_list<cir_74161*>il){
    for(cir_74161* cptr:il)
        cptr->RD=1;
}
void reset_74161(cir_74161& t){
    t.RD=0;
    func_74161(t);
}
void reset_74161(initializer_list<cir_74161*>il){
    for(cir_74161* cptr:il){
        cptr->RD=0;
        func_74161(*cptr);
    }
}

void preset_74161(cir_74161& t,bit4 D){
    t.LD=0;
    t.D=D;
    func_74161(t);
    t.LD=1;
}

#endif