function [xLand] = LandingDistance(d, velCoeffs, theta)
% Computes the horizontal distance traveled by a projectile
%   Using the inputs given for launch angle, initial velocity,
%   and geometric parameters defining the initial coordinates 
%   of the projectile, calculates the horizontal distance traveled
%   by a projectile.
g = 9.81;   % accelaration due to gravity (m/s^2)
[x0, y0] = InitialCoords(d, theta);
k = velCoeffs(1);
lambda = velCoeffs(2);
v0 = k + lambda * theta;
[v0x, v0y] = InitialVelocityComponents(v0, theta);
root = Quadratic(((-1/2) * g), v0y, y0, -1);
xLand = x0 + v0x .* root;
if(nargout == 0)
    plot(theta, xLand);
    xlabel("Launch Angle [deg]");
    ylabel("Horizontal Distance Traveled [m]");
    title("Ping Pong Ball Projectile Data");
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW9b