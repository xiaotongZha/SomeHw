#ifndef mytype
#define mytype
#include <bitset>
using std::bitset;

//定义bcd8421码类型
typedef bitset<4> bcd8421_t;
typedef bitset<4> bit4;
typedef bitset<8> bit8;

struct cir_74161{
    bitset<4>Q;
    bitset<4>D;
    bool RD=0;
    bool LD=1;
    bool EP=1;
    bool ET=1;
    bool C=0;
    cir_74161():Q("0000"),D("0000"){}
};

struct cir_8bitCounter{
    cir_74161 low4;
    cir_74161 high4;
    cir_8bitCounter(){
        high4.EP=low4.C;
        high4.ET=low4.C;
    }
};

typedef bitset<7> out7447;

#endif