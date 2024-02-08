function [range, rangeAngle] = ProjectileRange2(d, velCoeffs)
thetaL = 0:0.01:90;
[xLand] = LandingDistance(d, velCoeffs, thetaL);
[range, rangeIndex] = max(xLand);
rangeAngle = thetaL(rangeIndex);
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW6b