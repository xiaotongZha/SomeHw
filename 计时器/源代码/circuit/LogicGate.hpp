#ifndef LogicGate
#define LogicGate
#include <initializer_list>
using std::initializer_list;
//非门
bool NOT(bool f){
    return !f;
}
//与门
bool AND(initializer_list<bool>il){
    for(bool f:il)
        if(f==0)
            return 0;
    return 1;
}
bool AND(bool f1,bool f2){
    return f1 && f2;
}
//或门
bool OR(initializer_list<bool>il){
    for(bool f:il)
        if(f==1)
            return 1;
    return 0;
}
bool OR(bool f1,bool f2){
    return f1 || f2;
}
//与非门
bool NAND(initializer_list<bool>il){
    return NOT(AND(il));
}
bool NAND(bool i1,bool i2){
    return NOT(AND(i1,i2));
}
//或非门
bool NOR(initializer_list<bool>il){
    return NOT(OR(il));
}
bool NOR(bool i1,bool i2){
    return NOT(OR(i1,i2));
}
#endif
