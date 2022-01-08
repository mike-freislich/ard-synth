#include <Arduino.h>

const byte sinWave[] = {
    128, 130, 132, 135, 137, 139, 141, 143, 146, 148, 150, 152, 154, 157,
    159,
    161,
    163,
    165,
    167,
    169,
    171,
    174,
    176,
    178,
    180,
    182,
    184,
    186,
    188,
    190,
    192,
    193,
    195,
    197,
    199,
    201,
    203,
    204,
    206,
    208,
    210,
    211,
    213,
    215,
    216,
    218,
    219,
    221,
    222,
    224,
    225,
    227,
    228,
    229,
    231,
    232,
    233,
    235,
    236,
    237,
    238,
    239,
    240,
    241,
    242,
    243,
    244,
    245,
    246,
    247,
    247,
    248,
    249,
    249,
    250,
    251,
    251,
    252,
    252,
    253,
    253,
    253,
    254,
    254,
    254,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    255,
    254,
    254,
    254,
    253,
    253,
    253,
    252,
    252,
    251,
    251,
    250,
    249,
    249,
    248,
    247,
    247,
    246,
    245,
    244,
    243,
    242,
    241,
    240,
    239,
    238,
    237,
    236,
    235,
    233,
    232,
    231,
    229,
    228,
    227,
    225,
    224,
    222,
    221,
    219,
    218,
    216,
    215,
    213,
    211,
    210,
    208,
    206,
    204,
    203,
    201,
    199,
    197,
    195,
    193,
    192,
    190,
    188,
    186,
    184,
    182,
    180,
    178,
    176,
    174,
    171,
    169,
    167,
    165,
    163,
    161,
    159,
    157,
    154,
    152,
    150,
    148,
    146,
    143,
    141,
    139,
    137,
    135,
    132,
    130,
    128,
    126,
    124,
    121,
    119,
    117,
    115,
    113,
    110,
    108,
    106,
    104,
    102,
    99,
    97,
    95,
    93,
    91,
    89,
    87,
    85,
    82,
    80,
    78,
    76,
    74,
    72,
    70,
    68,
    66,
    64,
    63,
    61,
    59,
    57,
    55,
    53,
    52,
    50,
    48,
    46,
    45,
    43,
    41,
    40,
    38,
    37,
    35,
    34,
    32,
    31,
    29,
    28,
    27,
    25,
    24,
    23,
    21,
    20,
    19,
    18,
    17,
    16,
    15,
    14,
    13,
    12,
    11,
    10,
    9,
    9,
    8,
    7,
    7,
    6,
    5,
    5,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    2,
    2,
    2,
    3,
    3,
    3,
    4,
    4,
    5,
    5,
    6,
    7,
    7,
    8,
    9,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    23,
    24,
    25,
    27,
    28,
    29,
    31,
    32,
    34,
    35,
    37,
    38,
    40,
    41,
    43,
    45,
    46,
    48,
    50,
    52,
    53,
    55,
    57,
    59,
    61,
    63,
    64,
    66,
    68,
    70,
    72,
    74,
    76,
    78,
    80,
    82,
    85,
    87,
    89,
    91,
    93,
    95,
    97,
    99,
    102,
    104,
    106,
    108,
    110,
    113,
    115,
    117,
    119,
    121,
    124,
    126};

const byte triWave[] = {128,
                        153,
                        179,
                        204,
                        230,
                        255,
                        230,
                        204,
                        179,
                        153,
                        128,
                        103,
                        77,
                        52,
                        26,
                        1,
                        26,
                        52,
                        77,
                        103,
                        128};

const byte sqrWave[] = {0, 255};