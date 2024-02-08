function [sumOfSquaredErrors] = CompareProjectileData(velCoeffs, d, thetaL, landingDistanceVec)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
landingDistanceVecTheoretical = LandingDistance(d, velCoeffs, thetaL);
sumOfSquaredErrors = SumOfSquaredErrors(landingDistanceVec, landingDistanceVecTheoretical);
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW9b