function [x0, y0] = InitialCoords(d, theta)
% Function takes initial input to calculate the output
%   By using the coordinates of d1 , d2 , d3 , and theta,
%   and using equations, function calculates x0 and y0.
d1 = d(1);
d2 = d(2);
d3 = d(3);
x0 = (d2 .* cosd(theta)) - (d3 .* sind(theta));
y0 = (d1 + (d2 .* sind(theta))) + (d3 .* cosd(theta));
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW9b