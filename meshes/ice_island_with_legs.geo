a = 10;
r = 1;
R = 2;
h = 3;

///Cube
Point(1) = {0, 0, 0};
Point(2) = {a, 0, 0};
Point(3) = {0, a, 0};
Point(4) = {a, a, 0};
Point(5) = {a, a, a};
Point(6) = {a, 0, a};
Point(7) = {0, a, a};
Point(8) = {0, 0, a};

Line(5) = {1, 2};
Line(6) = {2, 4};
Line(7) = {4, 3};
Line(8) = {3, 1};
Line(9) = {7, 5};
Line(10) = {5, 6};
Line(11) = {6, 8};
Line(12) = {7, 8};
Line(13) = {3, 7};
Line(14) = {5, 4};
Line(15) = {6, 2};
Line(16) = {8, 1};

Line Loop(17) = {16, 5, -15, 11};
Plane Surface(18) = {17};
Line Loop(19) = {10, 15, 6, -14};
Plane Surface(20) = {19};
Line Loop(21) = {7, 13, 9, 14};
Plane Surface(22) = {21};
Line Loop(23) = {13, 12, 16, -8};
Plane Surface(24) = {23};
Line Loop(25) = {5, 6, 7, 8};
Plane Surface(26) = {25};
Line Loop(27) = {10, 11, -12, 9};
Plane Surface(28) = {27};
Surface Loop(29) = {22, 26, 18, 24, 28, 20};

Volume(30) = {29};

Physical Surface("cube_sides") = {24, 22, 18, 20, 26, 28};
Physical Volume("cube") = {30};

///Legs
//First
Point(90) = {a / 2 - R, a / 2, a};
Point(91) = {a / 2 - R - r, a / 2, a};
Point(92) = {a / 2 - R, a / 2 + r, a};
Point(93) = {a / 2 - R + r, a / 2, a};
Point(94) = {a / 2 - R, a / 2 - r, a};

Circle(35) = {91, 90, 92};
Circle(36) = {92, 90, 93};
Circle(37) = {93, 90, 94};
Circle(38) = {94, 90, 91};

Line Loop(49) = {38, 35, 36, 37};
Plane Surface(50) = {49};

//Second
Point(100) = {a / 2, a / 2 + R, a};
Point(101) = {a / 2 - r, a / 2 + R, a};
Point(102) = {a / 2, a / 2 + R + r, a};
Point(103) = {a / 2 + r, a / 2 + R, a};
Point(104) = {a / 2, a / 2 + R - r, a};

Circle(31) = {101, 100, 102};
Circle(32) = {102, 100, 103};
Circle(33) = {103, 100, 104};
Circle(34) = {104, 100, 101};

Line Loop(47) = {31, 32, 33, 34};
Plane Surface(48) = {47};

//Third
Point(110) = {a / 2 + R, a / 2 , a};
Point(111) = {a / 2 + R - r, a / 2, a};
Point(112) = {a / 2 + R, a / 2 + r , a};
Point(113) = {a / 2 + R + r, a / 2, a};
Point(114) = {a / 2 + R, a / 2 - r, a};

Circle(43) = {111, 110, 112};
Circle(44) = {112, 110, 113};
Circle(45) = {113, 110, 114};
Circle(46) = {114, 110, 111};

Line Loop(53) = {46, 43, 44, 45};
Plane Surface(54) = {53};

//Fourth
Point(120) = {a / 2, a / 2 - R, a};
Point(121) = {a / 2 - r, a / 2 - R, a};
Point(122) = {a / 2, a / 2 - R + r, a};
Point(123) = {a / 2 + r, a / 2 - R, a};
Point(124) = {a / 2, a / 2 - R - r, a};

Circle(39) = {121, 120, 122};
Circle(40) = {122, 120, 123};
Circle(41) = {123, 120, 124};
Circle(42) = {124, 120, 121};

Line Loop(51) = {42, 39, 40, 41};
Plane Surface(52) = {51};

//Translate all
Extrude {0, 0, h} {
  Surface{50, 48, 54, 52};
}

Physical Surface("legs_sides") = {115, 89, 85, 97, 93, 48, 98, 119, 120, 111, 54, 107, 52, 141, 129, 142, 133, 137, 63, 50, 75, 67, 71, 76};
Physical Volume("legs") = {32, 31, 33, 34};

Transfinite Line "*" = 20 Using Bump 0.25;
Transfinite Surface "*";
Recombine Surface "*";
Transfinite Volume "*";

