function [servoAngleVector, averageAngleVector] = LinkageData(filename)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
data = readmatrix(filename);
servoAngleVector = data(:,1);
angleVector = data(:,2:end);
averageAngleVector = mean(angleVector, 2);
if (nargout == 0)
    plot(servoAngleVector, averageAngleVector, 'bo');
    xlabel("Servomotor Angle [deg]");
    ylabel("Launch Angle [deg]");
    title("Cannon Fourbar Kinematics");
end

end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW8b