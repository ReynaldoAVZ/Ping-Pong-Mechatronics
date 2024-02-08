function [centroidRowVec,centroidColVec,imageArray] = FindAllTargetCentroids2(imageArray,targetRGB);

for i = 1:6
    [centroidRow,centroidCol,imageArray] = FindTargetCentroid2(imageArray,targetRGB);
    centroidRowVec(i) = centroidRow;
    centroidColVec(i) = centroidCol;
end
       
end