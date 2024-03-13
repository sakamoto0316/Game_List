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
 58;
 -6.47899;1.00025;1.20148;,
 -6.47899;0.00000;1.61579;,
 -5.67770;0.00000;2.81501;,
 -5.67770;1.84823;2.04945;,
 -6.47899;-1.00025;1.20148;,
 -5.67770;-1.84822;2.04945;,
 -6.47899;-1.41457;0.20123;,
 -5.67770;-2.61378;0.20123;,
 -6.47899;-1.00025;-0.79903;,
 -5.67770;-1.84822;-1.64700;,
 -6.47899;0.00000;-1.21334;,
 -5.67770;0.00000;-2.41256;,
 -6.47899;1.00025;-0.79903;,
 -5.67770;1.84823;-1.64700;,
 -6.47899;1.41457;0.20123;,
 -5.67770;2.61378;0.20123;,
 -4.47849;0.00000;3.61630;,
 -4.47849;2.41482;2.61605;,
 -4.47849;-2.41482;2.61605;,
 -4.47849;-3.41507;0.20123;,
 -4.47849;-2.41482;-2.21360;,
 -4.47849;0.00000;-3.21385;,
 -4.47849;2.41482;-2.21360;,
 -4.47849;3.41508;0.20123;,
 -3.06392;0.00000;3.89767;,
 -3.06392;2.61378;2.81501;,
 -3.06392;-2.61378;2.81501;,
 -3.06392;-3.69644;0.20123;,
 -3.06392;-2.61378;-2.41256;,
 -3.06392;0.00000;-3.49522;,
 -3.06392;2.61378;-2.41256;,
 -3.06392;3.69645;0.20123;,
 -1.64935;0.00000;3.61630;,
 -1.64935;2.41482;2.61605;,
 -1.64935;-2.41482;2.61605;,
 -1.64935;-3.41507;0.20123;,
 -1.64935;-2.41482;-2.21360;,
 -1.64935;0.00000;-3.21385;,
 -1.64935;2.41482;-2.21360;,
 -1.64935;3.41508;0.20123;,
 -0.45014;0.00000;2.81501;,
 -0.45014;1.84823;2.04945;,
 -0.45014;-1.84822;2.04945;,
 -0.45014;-2.61378;0.20123;,
 -0.45014;-1.84822;-1.64700;,
 -0.45014;0.00000;-2.41256;,
 -0.45014;1.84823;-1.64700;,
 -0.45014;2.61378;0.20123;,
 0.35115;0.00000;1.61579;,
 0.35115;1.00025;1.20148;,
 0.35115;-1.00025;1.20148;,
 0.35115;-1.41457;0.20123;,
 0.35115;-1.00025;-0.79903;,
 0.35115;0.00000;-1.21334;,
 0.35115;1.00025;-0.79903;,
 0.35115;1.41457;0.20123;,
 -6.76037;0.00000;0.20123;,
 0.63253;0.00000;0.20123;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,17,25,31;,
 4;25,24,32,33;,
 4;24,26,34,32;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,25,33,39;,
 4;33,32,40,41;,
 4;32,34,42,40;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,33,41,47;,
 4;41,40,48,49;,
 4;40,42,50,48;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,41,49,55;,
 3;1,0,56;,
 3;4,1,56;,
 3;6,4,56;,
 3;8,6,56;,
 3;10,8,56;,
 3;12,10,56;,
 3;14,12,56;,
 3;0,14,56;,
 3;49,48,57;,
 3;48,50,57;,
 3;50,51,57;,
 3;51,52,57;,
 3;52,53,57;,
 3;53,54,57;,
 3;54,55,57;,
 3;55,49,57;;
 
 MeshMaterialList {
  1;
  64;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\murabito00_UV.png";
   }
  }
 }
 MeshNormals {
  58;
  -0.924735;0.269133;0.269134;,
  -0.924734;-0.000000;0.380613;,
  -0.924734;-0.269133;0.269134;,
  -0.924734;-0.380613;0.000001;,
  -0.924735;-0.269133;-0.269134;,
  -0.924735;-0.000000;-0.380612;,
  -0.924735;0.269133;-0.269133;,
  -0.924735;0.380612;0.000001;,
  -0.709232;0.498492;0.498493;,
  -0.709231;-0.000000;0.704976;,
  -0.709231;-0.498493;0.498493;,
  -0.709231;-0.704976;0.000001;,
  -0.709231;-0.498493;-0.498493;,
  -0.709231;-0.000000;-0.704976;,
  -0.709232;0.498493;-0.498493;,
  -0.709232;0.704976;0.000001;,
  -0.384551;0.652732;0.652734;,
  -0.384550;-0.000000;0.923104;,
  -0.384551;-0.652733;0.652733;,
  -0.384551;-0.923104;0.000001;,
  -0.384551;-0.652733;-0.652732;,
  -0.384550;-0.000000;-0.923104;,
  -0.384551;0.652733;-0.652733;,
  -0.384551;0.923104;0.000001;,
  -0.000000;0.707106;0.707108;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.707107;0.707107;,
  -0.000000;-1.000000;0.000001;,
  -0.000000;-0.707107;-0.707106;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.707106;-0.707108;,
  -0.000000;1.000000;0.000001;,
  0.384551;0.652732;0.652734;,
  0.384551;-0.000000;0.923104;,
  0.384551;-0.652733;0.652733;,
  0.384551;-0.923104;0.000001;,
  0.384551;-0.652733;-0.652732;,
  0.384551;-0.000000;-0.923104;,
  0.384551;0.652733;-0.652733;,
  0.384551;0.923104;0.000001;,
  0.709232;0.498493;0.498493;,
  0.709231;-0.000000;0.704976;,
  0.709231;-0.498493;0.498494;,
  0.709231;-0.704976;0.000001;,
  0.709231;-0.498494;-0.498493;,
  0.709231;-0.000000;-0.704976;,
  0.709232;0.498493;-0.498493;,
  0.709231;0.704976;0.000001;,
  0.924735;0.269133;0.269134;,
  0.924734;-0.000000;0.380613;,
  0.924734;-0.269133;0.269135;,
  0.924734;-0.380613;0.000001;,
  0.924735;-0.269133;-0.269134;,
  0.924735;-0.000000;-0.380612;,
  0.924735;0.269133;-0.269133;,
  0.924735;0.380613;0.000001;,
  -1.000000;-0.000000;0.000001;,
  1.000000;-0.000000;0.000001;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  3;1,0,56;,
  3;2,1,56;,
  3;3,2,56;,
  3;4,3,56;,
  3;5,4,56;,
  3;6,5,56;,
  3;7,6,56;,
  3;0,7,56;,
  3;48,49,57;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,48,57;;
 }
 MeshTextureCoords {
  58;
  0.786875;0.255039;,
  0.786875;0.264633;,
  0.779189;0.264633;,
  0.779189;0.246906;,
  0.786875;0.274227;,
  0.779189;0.282360;,
  0.786875;0.278201;,
  0.779189;0.289703;,
  0.786875;0.274227;,
  0.779189;0.282360;,
  0.786875;0.264633;,
  0.779189;0.264633;,
  0.786875;0.255039;,
  0.779189;0.246906;,
  0.786875;0.251065;,
  0.779189;0.239563;,
  0.767687;0.264633;,
  0.767687;0.241472;,
  0.767687;0.287795;,
  0.767687;0.297389;,
  0.767687;0.287795;,
  0.767687;0.264633;,
  0.767687;0.241472;,
  0.767687;0.231878;,
  0.754120;0.264633;,
  0.754120;0.239563;,
  0.754120;0.289703;,
  0.754120;0.300087;,
  0.754120;0.289703;,
  0.754120;0.264633;,
  0.754120;0.239563;,
  0.754120;0.229179;,
  0.740552;0.264633;,
  0.740552;0.241472;,
  0.740552;0.287795;,
  0.740552;0.297389;,
  0.740552;0.287795;,
  0.740552;0.264633;,
  0.740552;0.241472;,
  0.740552;0.231878;,
  0.729050;0.264633;,
  0.729050;0.246906;,
  0.729050;0.282360;,
  0.729050;0.289703;,
  0.729050;0.282360;,
  0.729050;0.264633;,
  0.729050;0.246906;,
  0.729050;0.239563;,
  0.721364;0.264633;,
  0.721364;0.255039;,
  0.721364;0.274227;,
  0.721364;0.278201;,
  0.721364;0.274227;,
  0.721364;0.264633;,
  0.721364;0.255039;,
  0.721364;0.251065;,
  0.789574;0.264633;,
  0.718665;0.264633;;
 }
}
