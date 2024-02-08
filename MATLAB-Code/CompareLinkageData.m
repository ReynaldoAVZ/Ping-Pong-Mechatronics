function [SSE] = CompareLinkageData(params, Lengths, thetaS, thetaL)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
theoreticalLaunchAngles = ThetaLaunch(Lengths, thetaS, params);
SSE = SumOfSquaredErrors(thetaL, theoreticalLaunchAngles);
end

% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010, HW10b