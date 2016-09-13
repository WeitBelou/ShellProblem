L = 15;
r = 5;
d = 0.3;

Point(1) = {0, 0, 0};
Point(2) = {r, 0, 0};
Point(3) = {0, r, 0};
Point(4) = {-r, 0, 0};
Point(5) = {0, -r, 0};
Point(6) = {0, 0, r};

Translate {0, 0, -L + d} {
  Duplicata { Point{1, 2, 3, 4, 5}; }
}

Point(12) = {0, 0, -L};

Circle(1) = {2, 1, 3};
Circle(2) = {3, 1, 4};
Circle(3) = {4, 1, 5};
Circle(4) = {5, 1, 2};

Circle(5) = {6, 1, 2};
Circle(6) = {6, 1, 3};
Circle(7) = {6, 1, 4};
Circle(8) = {6, 1, 5};

Circle(9) = {8, 7, 9};
Circle(10) = {9, 7, 10};
Circle(11) = {10, 7, 11};
Circle(12) = {11, 7, 8};

Line(13) = {2, 8};
Line(14) = {3, 9};
Line(15) = {4, 10};
Line(16) = {5, 11};

Line Loop(17) = {9, 10, 11, 12};
Plane Surface(18) = {17};

Line Loop(19) = {1, 14, -9, -13};
Ruled Surface(20) = {19};

Line Loop(21) = {2, 15, -10, -14};
Ruled Surface(22) = {21};

Line Loop(23) = {3, 16, -11, -15};
Ruled Surface(24) = {23};

Line Loop(25) = {4, 13, -12, -16};
Ruled Surface(26) = {25};

Line Loop(27) = {1, -6, 5};
Ruled Surface(28) = {27};

Line Loop(29) = {2, -7, 6};
Ruled Surface(30) = {29};

Line Loop(31) = {3, -8, 7};
Ruled Surface(32) = {31};

Line Loop(33) = {4, -5, 8};
Ruled Surface(34) = {33};
Point(13) = {r+d, 0, -L, 1.0};
Point(14) = {0, r+d, -L, 1.0};
Point(15) = {-(r+d), 0, -L, 1.0};
Point(16) = {0, -(r+d), -L, 1.0};

Translate {0, 0, L} {
  Duplicata { Point{16, 13, 14, 15}; }
}
Translate {0, 0, d} {
  Duplicata { Point{6}; }
}
Circle(35) = {13, 12, 14};
Circle(36) = {14, 12, 15};
Circle(37) = {15, 12, 16};
Circle(38) = {16, 12, 13};
Line(39) = {13, 18};
Line(40) = {14, 19};
Line(41) = {15, 20};
Line(42) = {16, 17};
Circle(43) = {21, 1, 17};
Circle(44) = {21, 1, 18};
Circle(45) = {21, 1, 19};
Circle(46) = {21, 1, 20};

Line Loop(48) = {35, 36, 37, 38};
Circle(49) = {19, 1, 20};
Circle(50) = {20, 1, 17};
Circle(51) = {17, 1, 18};
Circle(52) = {18, 1, 19};

Plane Surface(53) = {48};

Line Loop(54) = {35, 40, -52, -39};
Ruled Surface(55) = {54};

Line Loop(56) = {36, 41, -49, -40};
Ruled Surface(57) = {56};

Line Loop(58) = {37, 42, -50, -41};
Ruled Surface(59) = {58};

Line Loop(60) = {42, 51, -39, -38};
Ruled Surface(61) = {60};

Line Loop(62) = {52, -45, 44};
Ruled Surface(63) = {62};

Line Loop(64) = {45, 49, -46};
Ruled Surface(65) = {64};

Line Loop(66) = {50, -43, 46};
Ruled Surface(67) = {66};

Line Loop(68) = {51, -44, 43};
Ruled Surface(69) = {68};

Surface Loop(70) = {57, 53, 55, 63, 65, 67, 59, 61, 69};
Surface Loop(71) = {22, 30, 32, 24, 26, 34, 28, 20, 18};

Volume(72) = {70, 71};

Physical Surface(0) = {55, 20, 22, 57, 59, 24, 26, 61, 53, 18, 34, 28, 32, 30};
Physical Surface(2) = {67, 69, 63, 65};

Physical Volume(10) = {72};

Mesh.Algorithm = 8;
Mesh.RecombineAll = 1;
Mesh.CharacteristicLengthFactor = 0.1;
Mesh.SubdivisionAlgorithm = 2;
Mesh.Smoothing = 20;
Show "*";