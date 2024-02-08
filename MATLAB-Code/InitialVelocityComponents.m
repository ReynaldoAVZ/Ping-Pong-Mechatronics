function [v0x, v0y] = InitialVelocityComponents(v0, theta)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
v0x = v0 .* cosd(theta);
v0y = v0 .* sind(theta);
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW9b