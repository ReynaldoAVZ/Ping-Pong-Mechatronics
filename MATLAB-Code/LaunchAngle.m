function [rangeAngle] = LaunchAngle(d, velCoeffs, xTarget)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
[range, rangeAngle] = ProjectileRange2(d, velCoeffs);
theta = linspace(rangeAngle, 90, 10000);
rangeAngle = [];
for i = 1:length(xTarget)
    xLand = LandingDistance(d, velCoeffs, theta);
    xDiff = abs(xLand - xTarget(i));
    [minDiff, minDiffIndex] = min(xDiff);
    rangeAngle(i) = theta(minDiffIndex);
end
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW9a