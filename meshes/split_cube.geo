a = 10;

Point(1) = {0, 0, 0};
Point(2) = {0, 0, a / 2};
Point(3) = {0, 0, a};
Point(4) = {a, 0, a};
Point(5) = {a, 0, a / 2};
Point(6) = {a, 0, 0};

Line(1) = {1, 2};
Line(2) = {2, 5};
Line(3) = {5, 6};
Line(4) = {6, 1};
Line(5) = {2, 3};
Line(6) = {3, 4};
Line(7) = {4, 5};

Line Loop(8) = {1, 2, 3, 4};
Plane Surface(9) = {8};
Line Loop(10) = {5, 6, 7, -2};
Plane Surface(11) = {10};

Extrude {0, a, 0} {
  Surface{11, 9};
}

Transfinite Line "*" = 1;
Transfinite Surface "*";
Recombine Surface "*";
Transfinite Volume "*";
