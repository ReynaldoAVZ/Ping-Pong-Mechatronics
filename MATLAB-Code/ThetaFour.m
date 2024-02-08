function [theta4] = ThetaFour(L, theta2)
% Calculates theta4 (degrees) given L and theta2
L1 = L(1);  % Length of the ground
L2 = L(2);  % Length of the servo crank
L3 = L(3);  % Length of the coupler
L4 = L(4);  % Length of the launcher link
K1 = L1 / L2;
%fprintf("K1 = %.4f\n", K1);
K2 = L1 / L4;
%fprintf("K2 = %.4f\n", K2);
K3 = ( (L1)^2 + (L2)^2 - (L3)^2 + (L4)^2 ) / ( 2 * L2 * L4 );
%fprintf("K3 = %.4f\n", K3);
A = cosd(theta2) - K1 - ( K2 * cosd(theta2) ) + K3;
%fprintf("A = %.4f\n", A);
B = -2 * sind(theta2);
%fprintf("B = %.4f\n", B);
C = K1 - ( (K2 + 1) * cosd(theta2) ) + K3;
%fprintf("C = %.4f\n", C);
theta4 = 2 * atand(Quadratic(A, B, C, -1));
  %  ( -B - sqrt( (B)^2 - (4 * A * C) ) ) / (2 * A) );
end

% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010, HW8b