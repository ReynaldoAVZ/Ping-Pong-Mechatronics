function [SSE] = SumOfSquaredErrors(exp_landingDistance, thr_landingDistance)
% Computes the sum of squared errors (SSE) between the experimental landing
% distance and the theoretical landing distance for manually optimized v0
vectorDifference = exp_landingDistance - thr_landingDistance;
vectorDifferenceSquared = (vectorDifference).^2;
SSE = sum(vectorDifferenceSquared);
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW9b