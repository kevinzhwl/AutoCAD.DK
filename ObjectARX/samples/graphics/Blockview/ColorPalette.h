//
// (C) Copyright 2002 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
#ifndef COLORPALETTE
#define COLORPALETTE
//////////////////////////////////////////////////////////////////////////////
// modified colour palette
static AcGsColor MyAcadColorPs [] = 
{
    {255, 0, 0, 255},    //----- 0 - lets make it red for an example
    //{255, 255, 255, 255},//----- 0 - ByBlock - White
    {255, 0, 0, 255},    //----- 1 - Red 
    {255, 255, 0, 255},    //----- 2 - Yellow
    {0, 255, 0, 255},    //----- 3 - Green
    {0, 255, 255, 255},    //----- 4 - Cyan
    {0, 0, 255, 255},    //----- 5 - Blue
    {255, 0, 255, 255},    //----- 6 - Magenta
    {255, 0, 0, 255},    //----- 7 - More red Red 
    {255, 0, 0, 255},    //----- 8 - More red Red 
    {255, 0, 0, 255},    //----- 9 - More red Red 
    /*{255, 255, 255, 255},//----- 7 - White
    {255, 255, 255, 255},//----- 8
    {255, 255, 255, 255},//----- 9*/
    {255, 0, 0, 255},    //----- 10
    {255, 127, 127, 255},//----- 11
    {165, 0, 0, 255},    //----- 12
    {165, 82, 82, 255},    //----- 13
    {127, 0, 0, 255},    //----- 14
    {127, 63, 63, 255},    //----- 15
    {76, 0, 0, 255},        //----- 16
    {76, 38, 38, 255},    //----- 17
    {38, 0, 0, 255},        //----- 18
    {38, 19, 19, 255},    //----- 19
    {255, 63, 0, 255},    //----- 20
    {255, 159, 127, 255},//----- 21
    {165, 41, 0, 255},    //----- 22
    {165, 103, 82, 255},    //----- 23
    {127, 31, 0, 255},    //----- 24
    {127, 79, 63, 255},    //----- 25
    {76, 19, 0, 255},    //----- 26
    {76, 47, 38, 255},    //----- 27
    {38, 9, 0, 255},        //----- 28
    {38, 23, 19, 255},    //----- 29
    {255, 127, 0, 255},    //----- 30
    {255, 191, 127, 255},//----- 31
    {165, 82, 0, 255},    //----- 32
    {165, 124, 82, 255},    //----- 33
    {127, 63, 0, 255},    //----- 34
    {127, 95, 63, 255},    //----- 35
    {76, 38, 0, 255},    //----- 36
    {76, 57, 38, 255},    //----- 37
    {38, 19, 0, 255},    //----- 38
    {38, 28, 19, 255},    //----- 39
    {255, 191, 0, 255},    //----- 40
    {255, 223, 127, 255},//----- 41
    {165, 124, 0, 255},    //----- 42
    {165, 145, 82, 255},    //----- 43
    {127, 95, 0, 255},    //----- 44
    {127, 111, 63, 255},    //----- 45
    {76, 57, 0, 255},    //----- 46
    {76, 66, 38, 255},    //----- 47
    {38, 28, 0, 255},    //----- 48
    {38, 33, 19, 255},    //----- 49
    {255, 255, 0, 255},    //----- 50
    {255, 255, 127, 255},//----- 51
    {165, 165, 0, 255},    //----- 52
    {165, 165, 82, 255},    //----- 53
    {127, 127, 0, 255},    //----- 54
    {127, 127, 63, 255},    //----- 55
    {76, 76, 0, 255},    //----- 56
    {76, 76, 38, 255},    //----- 57
    {38, 38, 0, 255},    //----- 58
    {38, 38, 19, 255},    //----- 59
    {191, 255, 0, 255},    //----- 60
    {223, 255, 127, 255},//----- 61
    {124, 165, 0, 255},    //----- 62
    {145, 165, 82, 255},    //----- 63
    {95, 127, 0, 255},    //----- 64
    {111, 127, 63, 255},    //----- 65
    {57, 76, 0, 255},    //----- 66
    {66, 76, 38, 255},    //----- 67
    {28, 38, 0, 255},    //----- 68
    {33, 38, 19, 255},    //----- 69
    {127, 255, 0, 255},    //----- 70
    {191, 255, 127, 255},//----- 71
    {82, 165, 0, 255},    //----- 72
    {124, 165, 82, 255},    //----- 73
    {63, 127, 0, 255},    //----- 74
    {95, 127, 63, 255},    //----- 75
    {38, 76, 0, 255},    //----- 76
    {57, 76, 38, 255},    //----- 77
    {19, 38, 0, 255},    //----- 78
    {28, 38, 19, 255},    //----- 79
    {63, 255, 0, 255},    //----- 80
    {159, 255, 127, 255},//----- 81
    {41, 165, 0, 255},    //----- 82
    {103, 165, 82, 255},    //----- 83
    {31, 127, 0, 255},    //----- 84
    {79, 127, 63, 255},    //----- 85
    {19, 76, 0, 255},    //----- 86
    {47, 76, 38, 255},    //----- 87
    {9, 38, 0, 255},        //----- 88
    {23, 38, 19, 255},    //----- 89
    {0, 255, 0, 255},    //----- 90
    {127, 255, 127, 255},//----- 91
    {0, 165, 0, 255},    //----- 92
    {82, 165, 82, 255},    //----- 93
    {0, 127, 0, 255},    //----- 94
    {63, 127, 63, 255},    //----- 95
    {0, 76, 0, 255},        //----- 96
    {38, 76, 38, 255},    //----- 97
    {0, 38, 0, 255},        //----- 98
    {19, 38, 19, 255},    //----- 99
    {0, 255, 63, 255},    //----- 100
    {127, 255, 159, 255},//----- 101
    {0, 165, 41, 255},    //----- 102
    {82, 165, 103, 255},    //----- 103
    {0, 127, 31, 255},    //----- 104
    {63, 127, 79, 255},    //----- 105
    {0, 76, 19, 255},    //----- 106
    {38, 76, 47, 255},    //----- 107
    {0, 38, 9, 255},        //----- 108
    {19, 38, 23, 255},    //----- 109
    {0, 255, 127, 255},    //----- 110
    {127, 255, 191, 255},//----- 111
    {0, 165, 82, 255},    //----- 112
    {82, 165, 124, 255},    //----- 113
    {0, 127, 63, 255},    //----- 114
    {63, 127, 95, 255},    //----- 115
    {0, 76, 38, 255},    //----- 116
    {38, 76, 57, 255},    //----- 117
    {0, 38, 19, 255},    //----- 118
    {19, 38, 28, 255},    //----- 119
    {0, 255, 191, 255},    //----- 120
    {127, 255, 223, 255},//----- 121
    {0, 165, 124, 255},    //----- 122
    {82, 165, 145, 255},    //----- 123
    {0, 127, 95, 255},    //----- 124
    {63, 127, 111, 255},    //----- 125
    {0, 76, 57, 255},    //----- 126
    {38, 76, 66, 255},    //----- 127
    {0, 38, 28, 255},    //----- 128
    {19, 38, 33, 255},    //----- 129
    {0, 255, 255, 255},    //----- 130
    {127, 255, 255, 255},//----- 131
    {0, 165, 165, 255},    //----- 132
    {82, 165, 165, 255},    //----- 133
    {0, 127, 127, 255},    //----- 134
    {63, 127, 127, 255},    //----- 135
    {0, 76, 76, 255},    //----- 136
    {38, 76, 76, 255},    //----- 137
    {0, 38, 38, 255},    //----- 138
    {19, 38, 38, 255},    //----- 139
    {0, 191, 255, 255},    //----- 140
    {127, 223, 255, 255},//----- 141
    {0, 124, 165, 255},    //----- 142
    {82, 145, 165, 255},    //----- 143
    {0, 95, 127, 255},    //----- 144
    {63, 111, 127, 255},    //----- 145
    {0, 57, 76, 255},    //----- 146
    {38, 66, 76, 255},    //----- 147
    {0, 28, 38, 255},    //----- 148
    {19, 33, 38, 255},    //----- 149
    {0, 127, 255, 255},    //----- 150
    {127, 191, 255, 255},//----- 151
    {0, 82, 165, 255},    //----- 152
    {82, 124, 165, 255},    //----- 153
    {0, 63, 127, 255},    //----- 154
    {63, 95, 127, 255},    //----- 155
    {0, 38, 76, 255},    //----- 156
    {38, 57, 76, 255},    //----- 157
    {0, 19, 38, 255},    //----- 158
    {19, 28, 38, 255},    //----- 159
    {0, 63, 255, 255},    //----- 160
    {127, 159, 255, 255},//----- 161
    {0, 41, 165, 255},    //----- 162
    {82, 103, 165, 255},    //----- 163
    {0, 31, 127, 255},    //----- 164
    {63, 79, 127, 255},    //----- 165
    {0, 19, 76, 255},    //----- 166
    {38, 47, 76, 255},    //----- 167
    {0, 9, 38, 255},        //----- 168
    {19, 23, 38, 255},    //----- 169
    {0, 0, 255, 255},    //----- 170
    {127, 127, 255, 255},//----- 171
    {0, 0, 165, 255},    //----- 172
    {82, 82, 165, 255},    //----- 173
    {0, 0, 127, 255},    //----- 174
    {63, 63, 127, 255},    //----- 175
    {0, 0, 76, 255},        //----- 176
    {38, 38, 76, 255},    //----- 177
    {0, 0, 38, 255},        //----- 178
    {19, 19, 38, 255},    //----- 179
    {63, 0, 255, 255},    //----- 180
    {159, 127, 255, 255},//----- 181
    {41, 0, 165, 255},    //----- 182
    {103, 82, 165, 255},    //----- 183
    {31, 0, 127, 255},    //----- 184
    {79, 63, 127, 255},    //----- 185
    {19, 0, 76, 255},    //----- 186
    {47, 38, 76, 255},    //----- 187
    {9, 0, 38, 255},        //----- 188
    {23, 19, 38, 255},    //----- 189
    {127, 0, 255, 255},    //----- 190
    {191, 127, 255, 255},//----- 191
    {82, 0, 165, 255},    //----- 192
    {124, 82, 165, 255},    //----- 193
    {63, 0, 127, 255},    //----- 194
    {95, 63, 127, 255},    //----- 195
    {38, 0, 76, 255},    //----- 196
    {57, 38, 76, 255},    //----- 197
    {19, 0, 38, 255},    //----- 198
    {28, 19, 38, 255},    //----- 199
    {191, 0, 255, 255},    //----- 200
    {223, 127, 255, 255},//----- 201
    {124, 0, 165, 255},    //----- 202
    {145, 82, 165, 255},    //----- 203
    {95, 0, 127, 255},    //----- 204
    {111, 63, 127, 255},    //----- 205
    {57, 0, 76, 255},    //----- 206
    {66, 38, 76, 255},    //----- 207
    {28, 0, 38, 255},    //----- 208
    {33, 19, 38, 255},    //----- 209
    {255, 0, 255, 255},    //----- 210
    {255, 127, 255, 255},//----- 211
    {165, 0, 165, 255},    //----- 212
    {165, 82, 165, 255},    //----- 213
    {127, 0, 127, 255},    //----- 214
    {127, 63, 127, 255},    //----- 215
    {76, 0, 76, 255},    //----- 216
    {76, 38, 76, 255},    //----- 217
    {38, 0, 38, 255},    //----- 218
    {38, 19, 38, 255},    //----- 219
    {255, 0, 191, 255},    //----- 220
    {255, 127, 223, 255},//----- 221
    {165, 0, 124, 255},    //----- 222
    {165, 82, 145, 255},    //----- 223
    {127, 0, 95, 255},    //----- 224
    {127, 63, 111, 255},    //----- 225
    {76, 0, 57, 255},    //----- 226
    {76, 38, 66, 255},    //----- 227
    {38, 0, 28, 255},    //----- 228
    {38, 19, 33, 255},    //----- 229
    {255, 0, 127, 255},    //----- 230
    {255, 127, 191, 255},//----- 231
    {165, 0, 82, 255},    //----- 232
    {165, 82, 124, 255},    //----- 233
    {127, 0, 63, 255},    //----- 234
    {127, 63, 95, 255},    //----- 235
    {76, 0, 38, 255},    //----- 236
    {76, 38, 57, 255},    //----- 237
    {38, 0, 19, 255},    //----- 238
    {38, 19, 28, 255},    //----- 239
    {255, 0, 63, 255},    //----- 240
    {255, 127, 159, 255},//----- 241
    {165, 0, 41, 255},    //----- 242
    {165, 82, 103, 255},    //----- 243
    {127, 0, 31, 255},    //----- 244
    {127, 63, 79, 255},    //----- 245
    {76, 0, 19, 255},    //----- 246
    {76, 38, 47, 255},    //----- 247
    {38, 0, 9, 255},        //----- 248
    {38, 19, 23, 255},    //----- 249
    {84, 84, 84, 255},    //----- 250
    {118, 118, 118, 255},//----- 251
    {152, 152, 152, 255},//----- 252
    {186, 186, 186, 255},//----- 253
    {220, 220, 220, 255},//----- 254
    {255, 255, 255, 255},//----- 255
    {255, 255, 255, 255}    //----- ByLayer - White
};

//////////////////////////////////////////////////////////////////////////////
// standard autocad colours
static AcGsColor MyAcadColorMs [] = 
{
    {255, 255, 255, 255},//----- 0 - ByBlock - White
    {255, 0, 0, 255},    //----- 1 - Red 
    {255, 255, 0, 255},    //----- 2 - Yellow
    {0, 255, 0, 255},    //----- 3 - Green
    {0, 255, 255, 255},    //----- 4 - Cyan
    {0, 0, 255, 255},    //----- 5 - Blue
    {255, 0, 255, 255},    //----- 6 - Magenta
    {255, 255, 255, 255},//----- 7 - White
    {255, 255, 255, 255},//----- 8
    {255, 255, 255, 255},//----- 9
    {255, 0, 0, 255},    //----- 10
    {255, 127, 127, 255},//----- 11
    {165, 0, 0, 255},    //----- 12
    {165, 82, 82, 255},    //----- 13
    {127, 0, 0, 255},    //----- 14
    {127, 63, 63, 255},    //----- 15
    {76, 0, 0, 255},        //----- 16
    {76, 38, 38, 255},    //----- 17
    {38, 0, 0, 255},        //----- 18
    {38, 19, 19, 255},    //----- 19
    {255, 63, 0, 255},    //----- 20
    {255, 159, 127, 255},//----- 21
    {165, 41, 0, 255},    //----- 22
    {165, 103, 82, 255},    //----- 23
    {127, 31, 0, 255},    //----- 24
    {127, 79, 63, 255},    //----- 25
    {76, 19, 0, 255},    //----- 26
    {76, 47, 38, 255},    //----- 27
    {38, 9, 0, 255},        //----- 28
    {38, 23, 19, 255},    //----- 29
    {255, 127, 0, 255},    //----- 30
    {255, 191, 127, 255},//----- 31
    {165, 82, 0, 255},    //----- 32
    {165, 124, 82, 255},    //----- 33
    {127, 63, 0, 255},    //----- 34
    {127, 95, 63, 255},    //----- 35
    {76, 38, 0, 255},    //----- 36
    {76, 57, 38, 255},    //----- 37
    {38, 19, 0, 255},    //----- 38
    {38, 28, 19, 255},    //----- 39
    {255, 191, 0, 255},    //----- 40
    {255, 223, 127, 255},//----- 41
    {165, 124, 0, 255},    //----- 42
    {165, 145, 82, 255},    //----- 43
    {127, 95, 0, 255},    //----- 44
    {127, 111, 63, 255},    //----- 45
    {76, 57, 0, 255},    //----- 46
    {76, 66, 38, 255},    //----- 47
    {38, 28, 0, 255},    //----- 48
    {38, 33, 19, 255},    //----- 49
    {255, 255, 0, 255},    //----- 50
    {255, 255, 127, 255},//----- 51
    {165, 165, 0, 255},    //----- 52
    {165, 165, 82, 255},    //----- 53
    {127, 127, 0, 255},    //----- 54
    {127, 127, 63, 255},    //----- 55
    {76, 76, 0, 255},    //----- 56
    {76, 76, 38, 255},    //----- 57
    {38, 38, 0, 255},    //----- 58
    {38, 38, 19, 255},    //----- 59
    {191, 255, 0, 255},    //----- 60
    {223, 255, 127, 255},//----- 61
    {124, 165, 0, 255},    //----- 62
    {145, 165, 82, 255},    //----- 63
    {95, 127, 0, 255},    //----- 64
    {111, 127, 63, 255},    //----- 65
    {57, 76, 0, 255},    //----- 66
    {66, 76, 38, 255},    //----- 67
    {28, 38, 0, 255},    //----- 68
    {33, 38, 19, 255},    //----- 69
    {127, 255, 0, 255},    //----- 70
    {191, 255, 127, 255},//----- 71
    {82, 165, 0, 255},    //----- 72
    {124, 165, 82, 255},    //----- 73
    {63, 127, 0, 255},    //----- 74
    {95, 127, 63, 255},    //----- 75
    {38, 76, 0, 255},    //----- 76
    {57, 76, 38, 255},    //----- 77
    {19, 38, 0, 255},    //----- 78
    {28, 38, 19, 255},    //----- 79
    {63, 255, 0, 255},    //----- 80
    {159, 255, 127, 255},//----- 81
    {41, 165, 0, 255},    //----- 82
    {103, 165, 82, 255},    //----- 83
    {31, 127, 0, 255},    //----- 84
    {79, 127, 63, 255},    //----- 85
    {19, 76, 0, 255},    //----- 86
    {47, 76, 38, 255},    //----- 87
    {9, 38, 0, 255},        //----- 88
    {23, 38, 19, 255},    //----- 89
    {0, 255, 0, 255},    //----- 90
    {127, 255, 127, 255},//----- 91
    {0, 165, 0, 255},    //----- 92
    {82, 165, 82, 255},    //----- 93
    {0, 127, 0, 255},    //----- 94
    {63, 127, 63, 255},    //----- 95
    {0, 76, 0, 255},        //----- 96
    {38, 76, 38, 255},    //----- 97
    {0, 38, 0, 255},        //----- 98
    {19, 38, 19, 255},    //----- 99
    {0, 255, 63, 255},    //----- 100
    {127, 255, 159, 255},//----- 101
    {0, 165, 41, 255},    //----- 102
    {82, 165, 103, 255},    //----- 103
    {0, 127, 31, 255},    //----- 104
    {63, 127, 79, 255},    //----- 105
    {0, 76, 19, 255},    //----- 106
    {38, 76, 47, 255},    //----- 107
    {0, 38, 9, 255},        //----- 108
    {19, 38, 23, 255},    //----- 109
    {0, 255, 127, 255},    //----- 110
    {127, 255, 191, 255},//----- 111
    {0, 165, 82, 255},    //----- 112
    {82, 165, 124, 255},    //----- 113
    {0, 127, 63, 255},    //----- 114
    {63, 127, 95, 255},    //----- 115
    {0, 76, 38, 255},    //----- 116
    {38, 76, 57, 255},    //----- 117
    {0, 38, 19, 255},    //----- 118
    {19, 38, 28, 255},    //----- 119
    {0, 255, 191, 255},    //----- 120
    {127, 255, 223, 255},//----- 121
    {0, 165, 124, 255},    //----- 122
    {82, 165, 145, 255},    //----- 123
    {0, 127, 95, 255},    //----- 124
    {63, 127, 111, 255},    //----- 125
    {0, 76, 57, 255},    //----- 126
    {38, 76, 66, 255},    //----- 127
    {0, 38, 28, 255},    //----- 128
    {19, 38, 33, 255},    //----- 129
    {0, 255, 255, 255},    //----- 130
    {127, 255, 255, 255},//----- 131
    {0, 165, 165, 255},    //----- 132
    {82, 165, 165, 255},    //----- 133
    {0, 127, 127, 255},    //----- 134
    {63, 127, 127, 255},    //----- 135
    {0, 76, 76, 255},    //----- 136
    {38, 76, 76, 255},    //----- 137
    {0, 38, 38, 255},    //----- 138
    {19, 38, 38, 255},    //----- 139
    {0, 191, 255, 255},    //----- 140
    {127, 223, 255, 255},//----- 141
    {0, 124, 165, 255},    //----- 142
    {82, 145, 165, 255},    //----- 143
    {0, 95, 127, 255},    //----- 144
    {63, 111, 127, 255},    //----- 145
    {0, 57, 76, 255},    //----- 146
    {38, 66, 76, 255},    //----- 147
    {0, 28, 38, 255},    //----- 148
    {19, 33, 38, 255},    //----- 149
    {0, 127, 255, 255},    //----- 150
    {127, 191, 255, 255},//----- 151
    {0, 82, 165, 255},    //----- 152
    {82, 124, 165, 255},    //----- 153
    {0, 63, 127, 255},    //----- 154
    {63, 95, 127, 255},    //----- 155
    {0, 38, 76, 255},    //----- 156
    {38, 57, 76, 255},    //----- 157
    {0, 19, 38, 255},    //----- 158
    {19, 28, 38, 255},    //----- 159
    {0, 63, 255, 255},    //----- 160
    {127, 159, 255, 255},//----- 161
    {0, 41, 165, 255},    //----- 162
    {82, 103, 165, 255},    //----- 163
    {0, 31, 127, 255},    //----- 164
    {63, 79, 127, 255},    //----- 165
    {0, 19, 76, 255},    //----- 166
    {38, 47, 76, 255},    //----- 167
    {0, 9, 38, 255},        //----- 168
    {19, 23, 38, 255},    //----- 169
    {0, 0, 255, 255},    //----- 170
    {127, 127, 255, 255},//----- 171
    {0, 0, 165, 255},    //----- 172
    {82, 82, 165, 255},    //----- 173
    {0, 0, 127, 255},    //----- 174
    {63, 63, 127, 255},    //----- 175
    {0, 0, 76, 255},        //----- 176
    {38, 38, 76, 255},    //----- 177
    {0, 0, 38, 255},        //----- 178
    {19, 19, 38, 255},    //----- 179
    {63, 0, 255, 255},    //----- 180
    {159, 127, 255, 255},//----- 181
    {41, 0, 165, 255},    //----- 182
    {103, 82, 165, 255},    //----- 183
    {31, 0, 127, 255},    //----- 184
    {79, 63, 127, 255},    //----- 185
    {19, 0, 76, 255},    //----- 186
    {47, 38, 76, 255},    //----- 187
    {9, 0, 38, 255},        //----- 188
    {23, 19, 38, 255},    //----- 189
    {127, 0, 255, 255},    //----- 190
    {191, 127, 255, 255},//----- 191
    {82, 0, 165, 255},    //----- 192
    {124, 82, 165, 255},    //----- 193
    {63, 0, 127, 255},    //----- 194
    {95, 63, 127, 255},    //----- 195
    {38, 0, 76, 255},    //----- 196
    {57, 38, 76, 255},    //----- 197
    {19, 0, 38, 255},    //----- 198
    {28, 19, 38, 255},    //----- 199
    {191, 0, 255, 255},    //----- 200
    {223, 127, 255, 255},//----- 201
    {124, 0, 165, 255},    //----- 202
    {145, 82, 165, 255},    //----- 203
    {95, 0, 127, 255},    //----- 204
    {111, 63, 127, 255},    //----- 205
    {57, 0, 76, 255},    //----- 206
    {66, 38, 76, 255},    //----- 207
    {28, 0, 38, 255},    //----- 208
    {33, 19, 38, 255},    //----- 209
    {255, 0, 255, 255},    //----- 210
    {255, 127, 255, 255},//----- 211
    {165, 0, 165, 255},    //----- 212
    {165, 82, 165, 255},    //----- 213
    {127, 0, 127, 255},    //----- 214
    {127, 63, 127, 255},    //----- 215
    {76, 0, 76, 255},    //----- 216
    {76, 38, 76, 255},    //----- 217
    {38, 0, 38, 255},    //----- 218
    {38, 19, 38, 255},    //----- 219
    {255, 0, 191, 255},    //----- 220
    {255, 127, 223, 255},//----- 221
    {165, 0, 124, 255},    //----- 222
    {165, 82, 145, 255},    //----- 223
    {127, 0, 95, 255},    //----- 224
    {127, 63, 111, 255},    //----- 225
    {76, 0, 57, 255},    //----- 226
    {76, 38, 66, 255},    //----- 227
    {38, 0, 28, 255},    //----- 228
    {38, 19, 33, 255},    //----- 229
    {255, 0, 127, 255},    //----- 230
    {255, 127, 191, 255},//----- 231
    {165, 0, 82, 255},    //----- 232
    {165, 82, 124, 255},    //----- 233
    {127, 0, 63, 255},    //----- 234
    {127, 63, 95, 255},    //----- 235
    {76, 0, 38, 255},    //----- 236
    {76, 38, 57, 255},    //----- 237
    {38, 0, 19, 255},    //----- 238
    {38, 19, 28, 255},    //----- 239
    {255, 0, 63, 255},    //----- 240
    {255, 127, 159, 255},//----- 241
    {165, 0, 41, 255},    //----- 242
    {165, 82, 103, 255},    //----- 243
    {127, 0, 31, 255},    //----- 244
    {127, 63, 79, 255},    //----- 245
    {76, 0, 19, 255},    //----- 246
    {76, 38, 47, 255},    //----- 247
    {38, 0, 9, 255},        //----- 248
    {38, 19, 23, 255},    //----- 249
    {84, 84, 84, 255},    //----- 250
    {118, 118, 118, 255},//----- 251
    {152, 152, 152, 255},//----- 252
    {186, 186, 186, 255},//----- 253
    {220, 220, 220, 255},//----- 254
    {255, 255, 255, 255},//----- 255
    {255, 255, 255, 255}    //----- ByLayer - White
};

#endif // COLOURPALETTE