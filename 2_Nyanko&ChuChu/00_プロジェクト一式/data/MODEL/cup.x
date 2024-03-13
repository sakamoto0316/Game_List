xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 288;
 -0.15250;4.95590;0.00000;,
 5.60590;4.95590;-13.90190;,
 -5.91080;4.95590;-13.90190;,
 13.74940;4.95590;-5.75840;,
 13.74940;4.95590;5.75830;,
 5.60590;4.95590;13.90190;,
 -5.91080;4.95590;13.90190;,
 -14.05430;4.95590;5.75840;,
 -14.05440;4.95590;-5.75830;,
 6.15680;37.17070;-15.23190;,
 -6.46170;37.17070;-15.23190;,
 15.07940;37.17070;-6.30930;,
 15.07940;37.17070;6.30930;,
 6.15680;37.17070;15.23190;,
 -6.46170;37.17070;15.23190;,
 -15.38430;37.17070;6.30930;,
 -15.38430;37.17070;-6.30930;,
 6.62380;36.35530;-16.35940;,
 -6.92880;36.35530;-16.35940;,
 16.20690;36.35530;-6.77630;,
 16.20690;36.35530;6.77630;,
 6.62380;36.35530;16.35940;,
 -6.92880;36.35530;16.35940;,
 -16.51190;36.35530;6.77630;,
 -16.51190;36.35530;-6.77630;,
 6.93590;35.13490;-17.11280;,
 -7.24080;35.13490;-17.11280;,
 16.96040;35.13490;-7.08840;,
 16.96040;35.13490;7.08840;,
 6.93590;35.13490;17.11280;,
 -7.24080;35.13490;17.11280;,
 -17.26530;35.13490;7.08840;,
 -17.26530;35.13490;-7.08840;,
 7.04550;33.69530;-17.37740;,
 -7.35040;33.69530;-17.37740;,
 17.22490;33.69530;-7.19790;,
 17.22490;33.69530;7.19790;,
 7.04550;33.69530;17.37740;,
 -7.35040;33.69530;17.37740;,
 -17.52980;33.69530;7.19790;,
 -17.52980;33.69530;-7.19790;,
 7.04550;3.60070;-17.37740;,
 -7.35040;3.60070;-17.37740;,
 17.22490;3.60070;-7.19790;,
 17.22490;3.60070;7.19790;,
 7.04550;3.60070;17.37740;,
 -7.35040;3.60070;17.37740;,
 -17.52980;3.60070;7.19790;,
 -17.52980;3.60070;-7.19790;,
 6.93590;2.16110;-17.11280;,
 -7.24080;2.16110;-17.11280;,
 16.96040;2.16110;-7.08840;,
 16.96040;2.16110;7.08840;,
 6.93590;2.16110;17.11280;,
 -7.24080;2.16110;17.11280;,
 -17.26530;2.16110;7.08840;,
 -17.26530;2.16110;-7.08840;,
 6.62380;0.94070;-16.35940;,
 -6.92880;0.94070;-16.35940;,
 16.20690;0.94070;-6.77630;,
 16.20690;0.94070;6.77630;,
 6.62380;0.94070;16.35940;,
 -6.92880;0.94070;16.35940;,
 -16.51190;0.94070;6.77630;,
 -16.51190;0.94070;-6.77630;,
 6.15680;0.12520;-15.23190;,
 -6.46170;0.12520;-15.23190;,
 15.07940;0.12520;-6.30930;,
 15.07940;0.12520;6.30930;,
 6.15680;0.12520;15.23190;,
 -6.46170;0.12520;15.23190;,
 -15.38430;0.12520;6.30930;,
 -15.38430;0.12520;-6.30930;,
 5.60590;-0.16120;-13.90190;,
 -5.91080;-0.16120;-13.90190;,
 13.74940;-0.16120;-5.75840;,
 13.74940;-0.16120;5.75830;,
 5.60590;-0.16120;13.90190;,
 -5.91080;-0.16120;13.90190;,
 -14.05430;-0.16120;5.75840;,
 -14.05440;-0.16120;-5.75830;,
 -0.15250;-0.16120;0.00000;,
 25.21200;16.82910;0.00000;,
 26.38020;16.82910;2.16530;,
 23.70150;22.85990;2.16530;,
 22.87550;22.08950;0.00000;,
 29.20070;16.82910;3.06220;,
 25.69590;24.71970;3.06220;,
 32.02110;16.82910;2.16530;,
 27.69020;26.57950;2.16530;,
 33.18940;16.82910;0.00000;,
 28.51630;27.34990;0.00000;,
 32.02110;16.82910;-2.16530;,
 27.69020;26.57950;-2.16530;,
 29.20070;16.82910;-3.06220;,
 25.69590;24.71970;-3.06220;,
 26.38020;16.82910;-2.16530;,
 23.70150;22.85990;-2.16530;,
 25.21200;16.82910;0.00000;,
 22.87550;22.08950;0.00000;,
 17.23460;25.35790;2.16530;,
 17.23460;24.26850;0.00000;,
 17.23460;27.98810;3.06220;,
 17.23460;30.61830;2.16530;,
 17.23460;31.70780;0.00000;,
 17.23460;30.61830;-2.16530;,
 17.23460;27.98810;-3.06220;,
 17.23460;25.35790;-2.16530;,
 17.23460;24.26850;0.00000;,
 17.23460;9.38980;0.00000;,
 17.23460;8.30030;2.16530;,
 23.70150;10.79830;2.16530;,
 22.87550;11.56870;0.00000;,
 17.23460;5.67010;3.06220;,
 25.69590;8.93850;3.06220;,
 17.23460;3.03990;2.16530;,
 27.69020;7.07870;2.16530;,
 17.23460;1.95050;0.00000;,
 28.51630;6.30830;0.00000;,
 17.23460;3.03990;-2.16530;,
 27.69020;7.07870;-2.16530;,
 17.23460;5.67010;-3.06220;,
 25.69590;8.93850;-3.06220;,
 17.23460;8.30030;-2.16530;,
 23.70150;10.79830;-2.16530;,
 17.23460;9.38980;0.00000;,
 22.87550;11.56870;0.00000;,
 26.38020;16.82910;2.16530;,
 25.21200;16.82910;0.00000;,
 29.20070;16.82910;3.06220;,
 32.02110;16.82910;2.16530;,
 33.18940;16.82910;0.00000;,
 32.02110;16.82910;-2.16530;,
 29.20070;16.82910;-3.06220;,
 26.38020;16.82910;-2.16530;,
 25.21200;16.82910;0.00000;,
 -10.97570;32.74630;10.97570;,
 -5.31820;32.74630;15.95470;,
 -5.31820;32.74630;5.31820;,
 -15.95470;32.74630;5.31820;,
 5.31820;32.74630;15.95470;,
 5.31820;32.74630;5.31820;,
 10.97570;32.74630;10.97570;,
 15.95470;32.74630;5.31820;,
 -5.31820;32.74630;-5.31820;,
 -15.95470;32.74630;-5.31820;,
 5.31820;32.74630;-5.31820;,
 15.95470;32.74630;-5.31820;,
 -5.31820;32.74630;-15.95470;,
 -10.97570;32.74630;-10.97570;,
 5.31820;32.74630;-15.95470;,
 10.97570;32.74630;-10.97570;,
 0.05507;3.45983;0.00000;,
 -6.33907;3.45983;-15.43695;,
 6.44931;3.45983;-15.43695;,
 15.49202;3.45983;-6.39424;,
 15.49202;3.45983;6.39413;,
 6.44931;3.45983;15.43695;,
 -6.33907;3.45983;15.43695;,
 -15.38177;3.45983;6.39424;,
 -15.38189;3.45983;-6.39413;,
 -6.95080;39.23179;-16.91381;,
 7.06104;39.23179;-16.91381;,
 16.96888;39.23179;-7.00598;,
 16.96888;39.23179;7.00598;,
 7.06104;39.23179;16.91381;,
 -6.95080;39.23179;16.91381;,
 -16.85863;39.23179;7.00598;,
 -16.85863;39.23179;-7.00598;,
 -7.46947;38.32637;-18.16580;,
 7.57961;38.32637;-18.16580;,
 18.22088;38.32637;-7.52454;,
 18.22088;38.32637;7.52454;,
 7.57961;38.32637;18.16580;,
 -7.46947;38.32637;18.16580;,
 -18.11074;38.32637;7.52454;,
 -18.11074;38.32637;-7.52454;,
 -7.81592;36.97121;-19.00240;,
 7.92617;36.97121;-19.00240;,
 19.05758;36.97121;-7.87110;,
 19.05758;36.97121;7.87110;,
 7.92617;36.97121;19.00240;,
 -7.81592;36.97121;19.00240;,
 -18.94733;36.97121;7.87110;,
 -18.94733;36.97121;-7.87110;,
 -7.93762;35.37264;-19.29622;,
 8.04787;35.37264;-19.29622;,
 19.35128;35.37264;-7.99269;,
 19.35128;35.37264;7.99269;,
 8.04787;35.37264;19.29622;,
 -7.93762;35.37264;19.29622;,
 -19.24103;35.37264;7.99269;,
 -19.24103;35.37264;-7.99269;,
 -7.93762;1.95500;-19.29622;,
 8.04787;1.95500;-19.29622;,
 19.35128;1.95500;-7.99269;,
 19.35128;1.95500;7.99269;,
 8.04787;1.95500;19.29622;,
 -7.93762;1.95500;19.29622;,
 -19.24103;1.95500;7.99269;,
 -19.24103;1.95500;-7.99269;,
 -7.81592;0.35643;-19.00240;,
 7.92617;0.35643;-19.00240;,
 19.05758;0.35643;-7.87110;,
 19.05758;0.35643;7.87110;,
 7.92617;0.35643;19.00240;,
 -7.81592;0.35643;19.00240;,
 -18.94733;0.35643;7.87110;,
 -18.94733;0.35643;-7.87110;,
 -7.46947;-0.99872;-18.16580;,
 7.57961;-0.99872;-18.16580;,
 18.22088;-0.99872;-7.52454;,
 18.22088;-0.99872;7.52454;,
 7.57961;-0.99872;18.16580;,
 -7.46947;-0.99872;18.16580;,
 -18.11074;-0.99872;7.52454;,
 -18.11074;-0.99872;-7.52454;,
 -6.95080;-1.90427;-16.91381;,
 7.06104;-1.90427;-16.91381;,
 16.96888;-1.90427;-7.00598;,
 16.96888;-1.90427;7.00598;,
 7.06104;-1.90427;16.91381;,
 -6.95080;-1.90427;16.91381;,
 -16.85863;-1.90427;7.00598;,
 -16.85863;-1.90427;-7.00598;,
 -6.33907;-2.22230;-15.43695;,
 6.44931;-2.22230;-15.43695;,
 15.49202;-2.22230;-6.39424;,
 15.49202;-2.22230;6.39413;,
 6.44931;-2.22230;15.43695;,
 -6.33907;-2.22230;15.43695;,
 -15.38177;-2.22230;6.39424;,
 -15.38189;-2.22230;-6.39413;,
 0.05507;-2.22230;-0.00000;,
 27.14176;17.58567;0.00000;,
 24.27511;24.03965;0.00000;,
 25.28852;24.98485;2.65660;,
 28.57503;17.58567;2.65660;,
 27.73546;27.26663;3.75701;,
 32.03549;17.58567;3.75701;,
 30.18226;29.54842;2.65660;,
 35.49582;17.58567;2.65660;,
 31.19580;30.49363;0.00000;,
 36.92921;17.58567;0.00000;,
 30.18226;29.54842;-2.65660;,
 35.49582;17.58567;-2.65660;,
 27.73546;27.26663;-3.75701;,
 32.03549;17.58567;-3.75701;,
 25.28852;24.98485;-2.65660;,
 28.57503;17.58567;-2.65660;,
 24.27511;24.03965;0.00000;,
 27.14176;17.58567;0.00000;,
 17.35430;26.71306;0.00000;,
 17.35430;28.04964;2.65660;,
 17.35430;31.27663;3.75701;,
 17.35430;34.50361;2.65660;,
 17.35430;35.84033;0.00000;,
 17.35430;34.50361;-2.65660;,
 17.35430;31.27663;-3.75701;,
 17.35430;28.04964;-2.65660;,
 17.35430;26.71306;0.00000;,
 17.35430;8.45841;0.00000;,
 24.27511;11.13170;0.00000;,
 25.28852;10.18650;2.65660;,
 17.35430;7.12170;2.65660;,
 27.73546;7.90471;3.75701;,
 17.35430;3.89472;3.75701;,
 30.18226;5.62293;2.65660;,
 17.35430;0.66773;2.65660;,
 31.19580;4.67772;0.00000;,
 17.35430;-0.66886;-0.00000;,
 30.18226;5.62293;-2.65660;,
 17.35430;0.66773;-2.65660;,
 27.73546;7.90471;-3.75701;,
 17.35430;3.89472;-3.75701;,
 25.28852;10.18650;-2.65660;,
 17.35430;7.12170;-2.65660;,
 24.27511;11.13170;0.00000;,
 17.35430;8.45841;0.00000;,
 27.14176;17.58567;0.00000;,
 28.57503;17.58567;2.65660;,
 32.03549;17.58567;3.75701;,
 35.49582;17.58567;2.65660;,
 36.92921;17.58567;0.00000;,
 35.49582;17.58567;-2.65660;,
 32.03549;17.58567;-3.75701;,
 28.57503;17.58567;-2.65660;,
 27.14176;17.58567;0.00000;;
 
 249;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;,
 4;82,83,84,85;,
 4;83,86,87,84;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;85,84,100,101;,
 4;84,87,102,100;,
 4;87,89,103,102;,
 4;89,91,104,103;,
 4;91,93,105,104;,
 4;93,95,106,105;,
 4;95,97,107,106;,
 4;97,99,108,107;,
 4;109,110,111,112;,
 4;110,113,114,111;,
 4;113,115,116,114;,
 4;115,117,118,116;,
 4;117,119,120,118;,
 4;119,121,122,120;,
 4;121,123,124,122;,
 4;123,125,126,124;,
 4;112,111,127,128;,
 4;111,114,129,127;,
 4;114,116,130,129;,
 4;116,118,131,130;,
 4;118,120,132,131;,
 4;120,122,133,132;,
 4;122,124,134,133;,
 4;124,126,135,134;,
 4;136,137,138,139;,
 4;137,140,141,138;,
 4;140,142,143,141;,
 4;139,138,144,145;,
 4;138,141,146,144;,
 4;141,143,147,146;,
 4;145,144,148,149;,
 4;144,146,150,148;,
 4;146,147,151,150;,
 3;152,153,154;,
 3;152,154,155;,
 3;152,155,156;,
 3;152,156,157;,
 3;152,157,158;,
 3;152,158,159;,
 3;152,159,160;,
 3;152,160,153;,
 4;153,161,162,154;,
 4;154,162,163,155;,
 4;155,163,164,156;,
 4;156,164,165,157;,
 4;157,165,166,158;,
 4;158,166,167,159;,
 4;159,167,168,160;,
 4;160,168,161,153;,
 4;161,169,170,162;,
 4;162,170,171,163;,
 4;163,171,172,164;,
 4;164,172,173,165;,
 4;165,173,174,166;,
 4;166,174,175,167;,
 4;167,175,176,168;,
 4;168,176,169,161;,
 4;169,177,178,170;,
 4;170,178,179,171;,
 4;171,179,180,172;,
 4;172,180,181,173;,
 4;173,181,182,174;,
 4;174,182,183,175;,
 4;175,183,184,176;,
 4;176,184,177,169;,
 4;177,185,186,178;,
 4;178,186,187,179;,
 4;179,187,188,180;,
 4;180,188,189,181;,
 4;181,189,190,182;,
 4;182,190,191,183;,
 4;183,191,192,184;,
 4;184,192,185,177;,
 4;185,193,194,186;,
 4;186,194,195,187;,
 4;187,195,196,188;,
 4;188,196,197,189;,
 4;189,197,198,190;,
 4;190,198,199,191;,
 4;191,199,200,192;,
 4;192,200,193,185;,
 4;193,201,202,194;,
 4;194,202,203,195;,
 4;195,203,204,196;,
 4;196,204,205,197;,
 4;197,205,206,198;,
 4;198,206,207,199;,
 4;199,207,208,200;,
 4;200,208,201,193;,
 4;201,209,210,202;,
 4;202,210,211,203;,
 4;203,211,212,204;,
 4;204,212,213,205;,
 4;205,213,214,206;,
 4;206,214,215,207;,
 4;207,215,216,208;,
 4;208,216,209,201;,
 4;209,217,218,210;,
 4;210,218,219,211;,
 4;211,219,220,212;,
 4;212,220,221,213;,
 4;213,221,222,214;,
 4;214,222,223,215;,
 4;215,223,224,216;,
 4;216,224,217,209;,
 4;217,225,226,218;,
 4;218,226,227,219;,
 4;219,227,228,220;,
 4;220,228,229,221;,
 4;221,229,230,222;,
 4;222,230,231,223;,
 4;223,231,232,224;,
 4;224,232,225,217;,
 3;225,233,226;,
 3;226,233,227;,
 3;227,233,228;,
 3;228,233,229;,
 3;229,233,230;,
 3;230,233,231;,
 3;231,233,232;,
 3;232,233,225;,
 4;234,235,236,237;,
 4;237,236,238,239;,
 4;239,238,240,241;,
 4;241,240,242,243;,
 4;243,242,244,245;,
 4;245,244,246,247;,
 4;247,246,248,249;,
 4;249,248,250,251;,
 4;235,252,253,236;,
 4;236,253,254,238;,
 4;238,254,255,240;,
 4;240,255,256,242;,
 4;242,256,257,244;,
 4;244,257,258,246;,
 4;246,258,259,248;,
 4;248,259,260,250;,
 4;261,262,263,264;,
 4;264,263,265,266;,
 4;266,265,267,268;,
 4;268,267,269,270;,
 4;270,269,271,272;,
 4;272,271,273,274;,
 4;274,273,275,276;,
 4;276,275,277,278;,
 4;262,279,280,263;,
 4;263,280,281,265;,
 4;265,281,282,267;,
 4;267,282,283,269;,
 4;269,283,284,271;,
 4;271,284,285,273;,
 4;273,285,286,275;,
 4;275,286,287,277;;
 
 MeshMaterialList {
  4;
  249;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.571200;0.254400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.380000;0.122400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.109600;0.740000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  245;
  0.000000;1.000000;0.000000;,
  0.382302;0.044642;0.922958;,
  -0.382302;0.044642;0.922958;,
  -0.922958;0.044642;0.382302;,
  -0.922959;0.044643;-0.382300;,
  -0.382303;0.044643;-0.922958;,
  0.382302;0.044642;-0.922958;,
  0.922958;0.044642;-0.382304;,
  0.922959;0.044642;0.382300;,
  -0.269775;0.709247;-0.651299;,
  0.269774;0.709250;-0.651296;,
  0.651285;0.709260;-0.269774;,
  0.651285;0.709260;0.269774;,
  0.269774;0.709250;0.651296;,
  -0.269775;0.709247;0.651299;,
  -0.651290;0.709255;0.269776;,
  -0.651290;0.709255;-0.269776;,
  -0.353256;0.384559;-0.852833;,
  0.353252;0.384569;-0.852830;,
  0.852830;0.384567;-0.353255;,
  0.852830;0.384568;0.353255;,
  0.353252;0.384569;0.852830;,
  -0.353256;0.384559;0.852833;,
  -0.852840;0.384543;0.353258;,
  -0.852840;0.384543;-0.353258;,
  -0.380837;0.098157;-0.919417;,
  0.380837;0.098157;-0.919417;,
  0.919420;0.098139;-0.380835;,
  0.919420;0.098139;0.380835;,
  0.380837;0.098157;0.919417;,
  -0.380837;0.098157;0.919417;,
  -0.919420;0.098139;0.380835;,
  -0.919420;0.098139;-0.380835;,
  -0.380837;-0.098156;-0.919417;,
  0.380837;-0.098157;-0.919417;,
  0.919420;-0.098139;-0.380835;,
  0.919420;-0.098139;0.380835;,
  0.380837;-0.098157;0.919417;,
  -0.380837;-0.098156;0.919417;,
  -0.919420;-0.098138;0.380835;,
  -0.919420;-0.098138;-0.380835;,
  -0.353256;-0.384559;-0.852833;,
  0.353252;-0.384569;-0.852830;,
  0.852830;-0.384568;-0.353255;,
  0.852830;-0.384568;0.353255;,
  0.353252;-0.384569;0.852830;,
  -0.353256;-0.384559;0.852833;,
  -0.852840;-0.384543;0.353258;,
  -0.852840;-0.384543;-0.353258;,
  -0.269783;-0.709227;-0.651318;,
  0.269782;-0.709229;-0.651315;,
  0.651304;-0.709240;-0.269782;,
  0.651304;-0.709240;0.269782;,
  0.269782;-0.709229;0.651315;,
  -0.269783;-0.709227;0.651318;,
  -0.651309;-0.709234;0.269784;,
  -0.651309;-0.709235;-0.269784;,
  -0.145662;-0.924725;-0.351663;,
  0.145666;-0.924722;-0.351668;,
  0.351668;-0.924722;-0.145666;,
  0.351667;-0.924723;0.145665;,
  0.145665;-0.924723;0.351667;,
  -0.145662;-0.924725;0.351663;,
  -0.351654;-0.924728;0.145661;,
  -0.351655;-0.924728;-0.145661;,
  -0.037455;-0.995199;-0.090424;,
  0.037455;-0.995199;-0.090424;,
  0.090424;-0.995199;-0.037455;,
  0.090423;-0.995199;0.037454;,
  0.037454;-0.995199;0.090423;,
  -0.037455;-0.995199;0.090424;,
  -0.090426;-0.995199;0.037455;,
  -0.090426;-0.995199;-0.037455;,
  0.000000;-1.000000;-0.000000;,
  -0.212593;0.831489;-0.513254;,
  0.212602;0.831481;-0.513263;,
  0.513263;0.831481;-0.212602;,
  0.513263;0.831481;0.212602;,
  0.212602;0.831481;0.513263;,
  -0.212593;0.831489;0.513254;,
  -0.513236;0.831501;0.212593;,
  -0.513236;0.831501;-0.212593;,
  -1.000000;0.000000;0.000000;,
  -0.628338;-0.000000;0.777940;,
  0.000005;-0.000000;1.000000;,
  0.628329;0.000000;0.777948;,
  1.000000;0.000000;0.000000;,
  0.628329;0.000000;-0.777948;,
  0.000005;-0.000000;-1.000000;,
  -0.628338;-0.000000;-0.777940;,
  -0.688049;-0.725664;0.000000;,
  -0.438905;-0.464702;0.769035;,
  0.000003;0.000002;1.000000;,
  0.438899;0.464697;0.769041;,
  0.688046;0.725667;0.000000;,
  0.438899;0.464697;-0.769041;,
  0.000003;0.000002;-1.000000;,
  -0.438905;-0.464702;-0.769035;,
  -0.360332;-0.932824;0.000000;,
  -0.243292;-0.629835;0.737643;,
  0.000001;0.000001;1.000000;,
  0.243290;0.629827;0.737650;,
  0.360332;0.932824;0.000000;,
  0.243290;0.629827;-0.737650;,
  0.000001;0.000001;-1.000000;,
  -0.243292;-0.629835;-0.737643;,
  -0.360324;0.932827;0.000000;,
  -0.243286;0.629830;0.737649;,
  0.000001;-0.000001;1.000000;,
  0.243290;-0.629833;0.737645;,
  0.360328;-0.932826;-0.000000;,
  0.243290;-0.629833;-0.737645;,
  0.000001;-0.000001;-1.000000;,
  -0.243286;0.629830;-0.737649;,
  -0.688047;0.725666;0.000000;,
  -0.438902;0.464700;0.769038;,
  0.000003;-0.000002;1.000000;,
  0.438900;-0.464700;0.769039;,
  0.688043;-0.725670;-0.000000;,
  0.438900;-0.464700;-0.769039;,
  0.000003;-0.000002;-1.000000;,
  -0.438902;0.464700;-0.769038;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.382302;-0.044642;-0.922959;,
  0.382302;-0.044642;-0.922959;,
  0.922958;-0.044642;-0.382302;,
  0.922959;-0.044643;0.382301;,
  0.382303;-0.044643;0.922958;,
  -0.382302;-0.044642;0.922958;,
  -0.922958;-0.044642;0.382304;,
  -0.922959;-0.044642;-0.382300;,
  0.269774;-0.709250;0.651296;,
  -0.269773;-0.709253;0.651294;,
  -0.651282;-0.709263;0.269773;,
  -0.651282;-0.709263;-0.269773;,
  -0.269773;-0.709253;-0.651294;,
  0.269774;-0.709250;-0.651296;,
  0.651287;-0.709258;-0.269775;,
  0.651287;-0.709258;0.269775;,
  0.353256;-0.384558;0.852834;,
  -0.353252;-0.384569;0.852830;,
  -0.852830;-0.384566;0.353256;,
  -0.852830;-0.384566;-0.353256;,
  -0.353252;-0.384569;-0.852830;,
  0.353256;-0.384558;-0.852834;,
  0.852840;-0.384540;-0.353259;,
  0.852840;-0.384540;0.353259;,
  0.380838;-0.098156;0.919417;,
  -0.380838;-0.098157;0.919417;,
  -0.919420;-0.098138;0.380835;,
  -0.919420;-0.098138;-0.380835;,
  -0.380838;-0.098157;-0.919417;,
  0.380838;-0.098156;-0.919417;,
  0.919421;-0.098136;-0.380835;,
  0.919421;-0.098136;0.380835;,
  0.380838;0.098156;0.919417;,
  -0.380838;0.098157;0.919417;,
  -0.919420;0.098137;0.380835;,
  -0.919420;0.098137;-0.380835;,
  -0.380838;0.098157;-0.919417;,
  0.380838;0.098156;-0.919417;,
  0.919421;0.098135;-0.380835;,
  0.919421;0.098135;0.380835;,
  0.353256;0.384560;0.852833;,
  -0.353252;0.384570;0.852830;,
  -0.852830;0.384567;0.353255;,
  -0.852830;0.384567;-0.353255;,
  -0.353252;0.384570;-0.852830;,
  0.353256;0.384560;-0.852833;,
  0.852840;0.384542;-0.353259;,
  0.852840;0.384542;0.353259;,
  0.269782;0.709228;0.651317;,
  -0.269782;0.709230;0.651315;,
  -0.651304;0.709240;0.269782;,
  -0.651304;0.709240;-0.269782;,
  -0.269782;0.709230;-0.651315;,
  0.269782;0.709228;-0.651317;,
  0.651308;0.709235;-0.269784;,
  0.651308;0.709235;0.269784;,
  0.145662;0.924724;0.351664;,
  -0.145667;0.924722;0.351669;,
  -0.351669;0.924722;0.145667;,
  -0.351668;0.924722;-0.145666;,
  -0.145666;0.924722;-0.351668;,
  0.145662;0.924724;-0.351664;,
  0.351656;0.924727;-0.145662;,
  0.351656;0.924727;0.145662;,
  0.037455;0.995199;0.090426;,
  -0.037455;0.995199;0.090425;,
  -0.090425;0.995199;0.037455;,
  -0.090424;0.995199;-0.037454;,
  -0.037455;0.995199;-0.090424;,
  0.037455;0.995199;-0.090425;,
  0.090427;0.995199;-0.037456;,
  0.090427;0.995198;0.037455;,
  0.000000;1.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.628338;-0.000000;-0.777941;,
  -0.000005;-0.000000;-1.000000;,
  -0.628328;0.000000;-0.777948;,
  -1.000000;0.000000;0.000000;,
  -0.628328;0.000000;0.777948;,
  -0.000005;-0.000000;1.000000;,
  0.628338;-0.000000;0.777941;,
  0.688048;0.725665;0.000000;,
  0.438905;0.464702;-0.769035;,
  -0.000003;-0.000002;-1.000000;,
  -0.438899;-0.464696;-0.769042;,
  -0.688046;-0.725667;0.000000;,
  -0.438899;-0.464696;0.769042;,
  -0.000003;-0.000002;1.000000;,
  0.438905;0.464702;0.769035;,
  0.360332;0.932824;0.000000;,
  0.243292;0.629835;-0.737643;,
  -0.000001;-0.000001;-1.000000;,
  -0.243289;-0.629826;-0.737651;,
  -0.360332;-0.932824;0.000000;,
  -0.243289;-0.629826;0.737651;,
  -0.000001;-0.000001;1.000000;,
  0.243292;0.629835;0.737643;,
  0.360325;-0.932827;-0.000000;,
  0.243286;-0.629830;-0.737649;,
  -0.000001;0.000001;-1.000000;,
  -0.243290;0.629834;-0.737645;,
  -0.360328;0.932826;0.000000;,
  -0.243290;0.629834;0.737645;,
  -0.000001;0.000001;1.000000;,
  0.243286;-0.629830;0.737649;,
  0.688047;-0.725666;-0.000000;,
  0.438902;-0.464700;-0.769038;,
  -0.000003;0.000002;-1.000000;,
  -0.438900;0.464700;-0.769039;,
  -0.688043;0.725670;0.000000;,
  -0.438900;0.464700;0.769039;,
  -0.000003;0.000002;1.000000;,
  0.438902;-0.464700;0.769038;,
  0.212590;-0.831494;0.513247;,
  -0.212599;-0.831486;0.513256;,
  -0.513257;-0.831486;0.212599;,
  -0.513257;-0.831486;-0.212599;,
  -0.212599;-0.831486;-0.513256;,
  0.212590;-0.831494;-0.513247;,
  0.513229;-0.831505;-0.212590;,
  0.513229;-0.831505;0.212590;;
  249;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  4;74,75,10,9;,
  4;75,76,11,10;,
  4;76,77,12,11;,
  4;77,78,13,12;,
  4;78,79,14,13;,
  4;79,80,15,14;,
  4;80,81,16,15;,
  4;81,74,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  3;65,66,73;,
  3;66,67,73;,
  3;67,68,73;,
  3;68,69,73;,
  3;69,70,73;,
  3;70,71,73;,
  3;71,72,73;,
  3;72,65,73;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,82,90,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;113,106,114,121;,
  4;114,115,83,82;,
  4;115,116,84,83;,
  4;116,117,85,84;,
  4;117,118,86,85;,
  4;118,119,87,86;,
  4;119,120,88,87;,
  4;120,121,89,88;,
  4;121,114,82,89;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  4;122,122,122,122;,
  3;123,123,123;,
  3;123,123,123;,
  3;123,123,123;,
  3;123,123,123;,
  3;123,123,123;,
  3;123,123,123;,
  3;123,123,123;,
  3;123,123,123;,
  4;124,124,125,125;,
  4;125,125,126,126;,
  4;126,126,127,127;,
  4;127,127,128,128;,
  4;128,128,129,129;,
  4;129,129,130,130;,
  4;130,130,131,131;,
  4;131,131,124,124;,
  4;237,132,133,238;,
  4;238,133,134,239;,
  4;239,134,135,240;,
  4;240,135,136,241;,
  4;241,136,137,242;,
  4;242,137,138,243;,
  4;243,138,139,244;,
  4;244,139,132,237;,
  4;132,140,141,133;,
  4;133,141,142,134;,
  4;134,142,143,135;,
  4;135,143,144,136;,
  4;136,144,145,137;,
  4;137,145,146,138;,
  4;138,146,147,139;,
  4;139,147,140,132;,
  4;140,148,149,141;,
  4;141,149,150,142;,
  4;142,150,151,143;,
  4;143,151,152,144;,
  4;144,152,153,145;,
  4;145,153,154,146;,
  4;146,154,155,147;,
  4;147,155,148,140;,
  4;148,156,157,149;,
  4;149,157,158,150;,
  4;150,158,159,151;,
  4;151,159,160,152;,
  4;152,160,161,153;,
  4;153,161,162,154;,
  4;154,162,163,155;,
  4;155,163,156,148;,
  4;156,164,165,157;,
  4;157,165,166,158;,
  4;158,166,167,159;,
  4;159,167,168,160;,
  4;160,168,169,161;,
  4;161,169,170,162;,
  4;162,170,171,163;,
  4;163,171,164,156;,
  4;164,172,173,165;,
  4;165,173,174,166;,
  4;166,174,175,167;,
  4;167,175,176,168;,
  4;168,176,177,169;,
  4;169,177,178,170;,
  4;170,178,179,171;,
  4;171,179,172,164;,
  4;172,180,181,173;,
  4;173,181,182,174;,
  4;174,182,183,175;,
  4;175,183,184,176;,
  4;176,184,185,177;,
  4;177,185,186,178;,
  4;178,186,187,179;,
  4;179,187,180,172;,
  4;180,188,189,181;,
  4;181,189,190,182;,
  4;182,190,191,183;,
  4;183,191,192,184;,
  4;184,192,193,185;,
  4;185,193,194,186;,
  4;186,194,195,187;,
  4;187,195,188,180;,
  3;188,196,189;,
  3;189,196,190;,
  3;190,196,191;,
  3;191,196,192;,
  3;192,196,193;,
  3;193,196,194;,
  3;194,196,195;,
  3;195,196,188;,
  4;197,205,206,198;,
  4;198,206,207,199;,
  4;199,207,208,200;,
  4;200,208,209,201;,
  4;201,209,210,202;,
  4;202,210,211,203;,
  4;203,211,212,204;,
  4;204,212,205,197;,
  4;205,213,214,206;,
  4;206,214,215,207;,
  4;207,215,216,208;,
  4;208,216,217,209;,
  4;209,217,218,210;,
  4;210,218,219,211;,
  4;211,219,220,212;,
  4;212,220,213,205;,
  4;221,229,230,222;,
  4;222,230,231,223;,
  4;223,231,232,224;,
  4;224,232,233,225;,
  4;225,233,234,226;,
  4;226,234,235,227;,
  4;227,235,236,228;,
  4;228,236,229,221;,
  4;229,197,198,230;,
  4;230,198,199,231;,
  4;231,199,200,232;,
  4;232,200,201,233;,
  4;233,201,202,234;,
  4;234,202,203,235;,
  4;235,203,204,236;,
  4;236,204,197,229;;
 }
 MeshTextureCoords {
  288;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.750000;0.125000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.875000;,
  0.750000;0.875000;,
  0.875000;1.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;;
 }
}
