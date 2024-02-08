function [launchAngleVector, avgDistanceVecM] = ProjectileData(filename)
% Function imports and averages experimental projectile data. When no
% output is assigned, generates a landing distance vs launch angle plot.
data = readmatrix(filename);
launchAngleVector = data(:, 1);
distanceVecCM = data(:, 2:end);
avgDistanceVecCM = mean(distanceVecCM, 2);
avgDistanceVecM = avgDistanceVecCM ./ 100;
if(nargout == 0)
    plot(launchAngleVector, avgDistanceVecM, "ob");
    xlabel("Launch Angle [deg]");
    ylabel("Horizontal Distance Traveled [m]");
    title("Ping Pong Ball Projectile Data");
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW9b