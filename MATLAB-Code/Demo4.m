%%%%%%%%%%%%%%%%%%%%%
% Reynaldo Villarreal Zambrano, Edwin Prieto
% u1348597, u1344505
% ME EN 1010 Lab Section 03
% DEMO 3
% Due 11.29.22
%%%%%%%%%%%%%%%%%%%%%
clear, clc,close all;

%%General

% Linkage Fitting

% Initialize file

% Robot 10 data
linkageFileName = 'Robot9_LinkageData.xlsx';
projectileFilename = 'Robot9_ProjectileData2.xlsx';
offsetFileName = 'Robot9_OffsetData2.xlsx';

% Robot 9data
% linkageFileName = 'Robot9_LinkageData.xlsx';
% projectileFilename = 'Robot9_ProjectileData2.xlsx';
% offsetFileName = 'Robot9_OffsetData2.xlsx';


%Load L vector
load L_vector.mat;
load d_vector.mat;

% Linkage Computation

% Load H vector
load H_vector.mat;

% Linkage

% Linkage Fitting

%Call linkage data
[thetaS, thetaL] = LinkageData(linkageFileName);
params = [30.0, 0.08, 12];

%Determing servo angle correction parameter and the launch angle offset.
[optimal_params, SSE] = fminsearch(@CompareLinkageData,params, [], L, thetaS, thetaL);

%Corresponding SSE between experimental and theoretical launch angles with
%optimal params
%SSE = CompareLinkageData(optimal_params, L, thetaS, thetaL);

%Plot expperimental Launch angle vs servo angle
LinkageData(linkageFileName);
hold on;

%Plot theoretical launch angle vs servo angle
ThetaLaunch(L, thetaS,optimal_params);

%Edit plot
xlabel("Servomotor Angle [deg]");
ylabel("Launch Angle [deg]");
title("Launcher Fourbar Kinematics");
legend("experiment", "theory", "Location", "southeast");
alpha = optimal_params(1);
beta = optimal_params(2);
thetaL = optimal_params(3);
message = sprintf(" alpha = %.2f degrees\n beta = %.4f\n thetaL0 = %.2f degrees\n SSE = %.4f", alpha, beta, thetaL, SSE);
text(20, 75, message);


% Projectile

% Projectile Fitting
[launchAngleVector, avgDistanceVecM] = ProjectileData(projectileFilename);
[optimalVelCoeffs, minSSE] = fminsearch(@CompareProjectileData, [3.2, 0], [], d, launchAngleVector, avgDistanceVecM)
figure
ProjectileData(projectileFilename);
hold on;
LandingDistance(d, optimalVelCoeffs, launchAngleVector);
xlabel("Launch Angle [deg]");
ylabel("Horizontal Distance Traveled [m]");
legend("experiment", "theory");
message = sprintf("The SSE is %.4f for kappa = %.2f m/s and lambda = %.4f\n", minSSE, optimalVelCoeffs(1), optimalVelCoeffs(2));
text(57, .6, message);

%% Stripe Offset Fitting
offsetVec = readmatrix(offsetFileName);
offsetAngleVecExp = offsetVec(:, 1);
offsetStripeVecExp = offsetVec(:, 2);
figure
plot(offsetAngleVecExp, offsetStripeVecExp, "LineStyle","none", "marker", "o");
hold on;
offsetCoeffs = polyfit(offsetAngleVecExp, offsetStripeVecExp, 1);
theoreticalStripeOffsetVec = polyval(offsetCoeffs, offsetAngleVecExp)
plot(offsetAngleVecExp, theoreticalStripeOffsetVec);
xlabel("Servo Angle [deg]");
ylabel("Stripe offset [cm]");
legend("experiment", "theory");
message = sprintf("m = %.4f; b = %.4f", offsetCoeffs(1), offsetCoeffs(2));
text(85, 2.5, message);
%%
hold on
%Robot 9
origImage = imread('F22_CP_A2.bmp');

disp("Click on the alien ship to get color information");
figure
[RGBvec] = ColorPicker(origImage);

[centroidRowVec,centroidColVec,modImage] = FindAllTargetCentroids2(origImage,RGBvec);
centroidRowVec
centroidColVec
figure
image(modImage)

hold on
plot(centroidColVec,centroidRowVec,'rx')
drawnow

stripeNum = centroidRowVec ./ 10
xTargetm = (650 + centroidColVec) ./ (1000)

%%
% VIDEO CODE

% serial communication setup
RomeoCOM = serialport('/dev/cu.usbmodem14201',9600);
%RomeoCOM = serialport('COM6', 9600);
endCheck = "done";
dataCheck = "ready for data";

% key press detection setup
kbhit('init');
key = char(0);
prevKey = key;

while(1)
    % key press detection
    prevKey = key;
    key = kbhit;
    pause(1/6000) % in Seconds
    if key == 'q'
        disp('MATLAB aborting')
        break
    elseif key ~= char(0)
        disp('sending letter to Arduino')
        writeline(RomeoCOM,key)
    end

    % serial communication
    if RomeoCOM.NumBytesAvailable > 0   
        message = readline(RomeoCOM);
        message = erase(message,sprintf('\r'));
        if strcmp(message,endCheck) == 1
            break
        % if Romeo sends special done message, send data, etc.
        elseif strcmp(message,dataCheck) == 1
            %send data to romeo and recieve message back
            disp('sending data to Romeo')
            %send info to romeo
           % writeline(RomeoCOM, xTargetm);
            for target = 1:6
                stripeNumString = sprintf("%.2f",stripeNum(target));
            
            % try sending inter value as a string to Romeo
                writeline(RomeoCOM,stripeNumString)
                xTargetmString = sprintf('%.3f', xTargetm(target));
                writeline(RomeoCOM,xTargetmString)
                message = readline(RomeoCOM);
                message = erase(message,sprintf('\r'));
                disp(message)
            end
            % sending optimal params to arduino
            for j = 1:length(optimal_params)
                currentValue = sprintf("%.3f", optimal_params(j));
                writeline(RomeoCOM, currentValue);
            end
            message = readline(RomeoCOM);
            message = erase(message, sprintf('\r'));
            disp(message);
            % sending optimal velocity coefficients to arduino
            for j = 1:length(optimalVelCoeffs)
                currentParam = sprintf("%.3f", optimalVelCoeffs(j));
                writeline(RomeoCOM, currentParam);
            end
            message = readline(RomeoCOM);
            message = erase(message, sprintf('\r'));
            disp(message);
            % sending offset coeffs to arduino
            for j = 1:length(offsetCoeffs)
                currentOffset = sprintf("%.4f", offsetCoeffs(j));
                writeline(RomeoCOM, currentOffset);
            end
            message = readline(RomeoCOM);
            message = erase(message, sprintf('\r'));
            disp(message);

        else
            disp(message)
        end
    end
end

clear RomeoCOM

kbhit('stop');