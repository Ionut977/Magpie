// SSSR varH

cbuffer constants : register(b0) {
    int2 srcSize : packoffset(c0.x);
};


#define MAGPIE_INPUT_COUNT 1
#define MAGPIE_NO_CHECK
#include "common.hlsli"



#define spread      1.0 / 1000.0

#define sqr(x)      pow(x, 2.0)
#define GetH(x,y)   SampleInputOff(0, float2(x, y)).rgb

#define Luma(rgb)   ( dot(rgb*rgb, float3(0.2126, 0.7152, 0.0722)) )



D2D_PS_ENTRY(main) {
    int X, Y;
    float3 meanH = 0;
    for (X = -1; X <= 1; X++) {
        for (Y = -1; Y <= 1; Y++) {
            meanH += GetH(X, Y) * pow(spread, sqr(float(X)) + sqr(float(Y)));
        }
    }
    meanH /= (1.0 + 4.0 * spread + 4.0 * spread * spread);

    float varH = 0.0;
    for (X = -1; X <= 1; X++) {
        for (Y = -1; Y <= 1; Y++) {
            varH += Luma(abs(GetH(X, Y) - meanH)) * pow(spread, sqr(float(X)) + sqr(float(Y)));
        }
    }
    varH /= (spread + 4.0 * spread + 4.0 * spread * spread);

    varH *= 8;
    float x = floor(varH * 10) / 10;
    float y = ((varH - x) * 100) / 10;
    return float4(x, y, 0, 1);
}
