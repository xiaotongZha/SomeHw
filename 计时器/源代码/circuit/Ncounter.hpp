#include "mytype.hpp"
#include "74LS161.hpp"

#define GET_HIGH4(I) (bit4((I.to_ulong() >> 4) & 0x0F))
#define GET_LOW4(I) (bit4((I.to_ulong() & 0x0F)))
#define COMBINE_8(HIGH, LOW) (bit8((HIGH.to_ulong() << 4) | LOW.to_ulong()))

void counter_second(cir_8bitCounter &ss){
        cir_74161 &cir_low = ss.low4;
        cir_74161 &cir_high = ss.high4;
        func_74161(cir_low);
        func_74161(cir_high);
        bool G1 = AND(cir_low.Q[3], cir_low.Q[0]);
        cir_low.LD = NOT(G1);
        cir_low.C = G1;
        cir_high.EP = cir_high.ET = cir_low.C;
        bool G2 = AND(cir_high.Q[0], cir_high.Q[2]);
        cir_high.LD = NAND(G1, G2);
        cir_high.C = AND(G1, G2);
}
void counter_minute(cir_8bitCounter &mm, cir_8bitCounter &ss){
        cir_74161 &cir_low = mm.low4;
        cir_74161 &cir_high = mm.high4;
       
        func_74161(cir_low);
        func_74161(cir_high);
        bool G0 = ss.high4.C;
        cir_low.EP = cir_low.ET = G0;
        bool G1 = AND(cir_low.Q[3], cir_low.Q[0]);
        cir_low.LD = NAND(G1, G0);
        cir_low.C = AND(G1, G0);
        cir_high.EP = cir_high.ET = cir_low.C;
        bool G2 = AND(cir_high.Q[0], cir_high.Q[2]);
        cir_high.LD = NAND({G1, G0, G2});
        cir_high.C = AND({G0, G1, G2});
}
void counter_hour(cir_8bitCounter &hh, cir_8bitCounter &mm, cir_8bitCounter &ss){
        cir_74161 &cir_low = hh.low4;
        cir_74161 &cir_high = hh.high4;
        func_74161(cir_low);
        func_74161(cir_high);
        bool G0 = AND(mm.high4.C,ss.high4.C);
        bool G1 = AND({cir_low.Q[0],cir_low.Q[3]});
        bool G2 = cir_high.Q[1];
        bool G3 = AND(cir_low.Q[0],cir_low.Q[1]);
        bool G4 = AND({G0,G2,G3});

        cir_low.EP = cir_low.ET = G0;
        cir_low.C = OR(AND(G1, G0),G4);
        cir_low.LD = NOR(AND(G1, G0),G4);

        cir_high.EP = cir_high.ET = cir_low.C;
        
        cir_high.LD = NOT(G4);
        cir_high.C = G4;
}