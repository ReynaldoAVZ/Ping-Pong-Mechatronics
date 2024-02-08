function [thetaL] = ThetaLaunch(L, thetaS, params)
% Calculate thetaL (degrees) given L, thetaS (Servo angle), and 
% params (alpha = angle (degrees), beta = unitless scaling factor, thetaL0
% = angle (degrees)
alpha = params(1);
beta = params(2);
thetaL0 = params(3);
thetaSC = alpha + beta * thetaS;
theta2 = 180 - thetaS + thetaSC;
theta4 = ThetaFour(L, theta2);
thetaL = 180 - theta4 + thetaL0;
if (nargout == 0)
    plot(thetaS, thetaL);
    xlabel("Servo Motor Angle [deg]");
    ylabel("Launch Angle [deg]");
    title("Cannon Fourbar Kinematics");
end
end

% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010, HW8b