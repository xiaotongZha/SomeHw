#ifndef _74LS47
#define _74LS47

#include "mytype.hpp"
#include "LogicGate.hpp"

//定义BCD-七段显示译码器的功能函数
out7447 func_7447(bcd8421_t A){
    out7447 Y;
    Y[0]=OR({
        AND(NOT(A[3]),A[1]),
        AND(A[2],A[1]),
        AND(A[3],NOT(A[0])),
        AND(NOT(A[2]),NOT(A[0])),
        AND({NOT(A[3]),A[2],A[0]}),
        AND({A[3],NOT(A[2]),NOT(A[1])})
    });

    Y[1]=OR({
        AND(NOT(A[3]),NOT(A[2])),
        AND(NOT(A[2]),NOT(A[0])),
        AND({NOT(A[3]),NOT(A[1]),NOT(A[0])}),
        AND({NOT(A[3]),A[1],A[0]}),
        AND({A[3],NOT(A[1]),A[0]})    
    });
    Y[2]=OR({
        AND(NOT(A[1]),A[0]),
        AND(NOT(A[3]),A[2]),
        AND(A[3],NOT(A[2])),
        AND(NOT(A[3]),NOT(A[1])),
        AND(NOT(A[3]),A[0])
    });
    Y[3]=OR({
        AND(A[3],NOT(A[1])),
        AND({NOT(A[3]),NOT(A[2]),A[1]}),
        AND({NOT(A[3]),NOT(A[2]),NOT(A[0])}),
        AND({A[3],A[2],NOT(A[0])}),
        AND({A[3],NOT(A[2]),A[0]}),
        AND({NOT(A[3]),A[1],NOT(A[0])}),
        AND({A[2],NOT(A[1]),A[0]})
    });
    Y[4]=OR({
        AND(A[1],NOT(A[0])),
        AND(A[3],A[2]),
        AND(A[3],A[1]),
        AND(NOT(A[2]),NOT(A[0]))
    });
    Y[5]=OR({
       AND(NOT(A[1]),NOT(A[0])),
       AND(A[3],NOT(A[2])),
       AND(A[2],NOT(A[0])),
       AND(A[3],A[1]),
       AND({NOT(A[3]),A[2],NOT(A[1])})
    });
    Y[6]=OR({
        AND(A[1],NOT(A[0])),
        AND(A[3],NOT(A[2])),
        AND(A[3],A[0]),
        AND(NOT(A[2]),A[1]),
        AND({NOT(A[3]),A[2],NOT(A[1])})
    });
    return Y;
}

#endif