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
 16;
 -156.79849;164.07980;38.89830;,
 159.40150;164.07980;38.89830;,
 159.40150;99.92000;32.44240;,
 -156.79849;99.92000;32.44240;,
 159.40150;44.99500;65.96290;,
 -156.07210;45.19270;68.32970;,
 159.40150;196.44940;67.44240;,
 159.40150;99.92000;67.44240;,
 159.40150;200.27280;102.44240;,
 159.40150;101.92110;102.44240;,
 159.40150;44.76910;102.29710;,
 -156.79849;200.27280;102.44240;,
 -156.79849;101.92110;102.44240;,
 -156.79849;44.76910;102.29710;,
 -156.79849;196.44940;67.44240;,
 -156.79849;99.92000;67.44240;;
 
 15;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;1,6,7,2;,
 4;6,8,9,7;,
 4;7,9,10,4;,
 4;8,11,12,9;,
 4;9,12,13,10;,
 4;11,14,15,12;,
 4;14,0,3,15;,
 4;12,15,5,13;,
 4;11,8,6,14;,
 4;14,6,1,0;,
 4;5,4,10,13;,
 3;4,2,7;,
 3;5,15,3;;
 
 MeshMaterialList {
  3;
  15;
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
  1;;
  Material {
   0.800000;0.636800;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\sofa.jpeg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  16;
  0.000000;0.399968;-0.916529;,
  -0.001780;-0.229872;-0.973219;,
  1.000000;0.000000;0.000000;,
  -0.002108;-0.873728;-0.486411;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.001271;0.999999;,
  -0.999984;-0.005020;-0.002694;,
  0.000000;-0.002542;0.999997;,
  -0.999980;-0.003405;-0.005388;,
  -0.999978;-0.006636;0.000000;,
  -0.999935;-0.010041;-0.005388;,
  -0.999919;-0.006810;-0.010775;,
  0.000000;0.994086;-0.108594;,
  0.000000;0.887704;-0.460415;,
  -0.000337;-0.999956;-0.009344;;
  15;
  4;0,0,1,1;,
  4;1,1,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,6,6;,
  4;6,6,8,8;,
  4;5,5,7,9;,
  4;5,5,10,7;,
  4;9,7,11,12;,
  4;13,13,14,14;,
  4;14,14,0,0;,
  4;3,3,15,15;,
  3;2,2,2;,
  3;11,7,10;;
 }
}
