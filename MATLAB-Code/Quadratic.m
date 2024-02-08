function [root] = Quadratic(a, b, c, plusOrMinus)
% Calculates the root of a quadratic function.
%   By using the given inputs, the root of the function is calculated.
%   However, function generates an error if the coefficients produce 
%   a complex root. 
if( (b.^2 - 4 .* a .* c) >= 0)
    root = (-b + (plusOrMinus .* sqrt(b.^2 - 4 .* a .* c))) ./ (2 .* a);
else
    error("The given coefficients yield a complex root")
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW8b