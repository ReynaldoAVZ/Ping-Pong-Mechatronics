function [centroidRow,centroidCol,modImage] = FindTargetCentroid2(origImage,targetRGB)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

redLayer = origImage(:,:,1);
greenLayer = origImage(:,:,2);
blueLayer = origImage(:,:,3);

%logArray = redLayer == targetRGB(1) & greenLayer == targetRGB(2) & blueLayer == targetRGB(3);
logArray = sum(origImage, 3) == (sum(targetRGB) - 1);

[matchRows, matchCols] = find(logArray == 1);

firstMatchRow = matchRows(1);
firstMatchCol = matchCols(1);

[rows, cols,colors] = size(origImage);

for c = firstMatchCol:cols
    if logArray(firstMatchRow,c + 1) == 0
        break;
    end
end
lastMatchCol = c;

for r = firstMatchRow:rows
    if logArray(r + 1, firstMatchCol) == 0
        break;
    end
end
lastMatchRow = r;

%Centroid
centroidRow = (firstMatchRow + lastMatchRow)/2;
centroidCol = (firstMatchCol + lastMatchCol)/2;

modImage = origImage;

%Use INDEXING to change all of the red/target pixels in modImage to black. Do NOT use nested for loops! 
modImage(firstMatchRow:lastMatchRow,firstMatchCol:lastMatchCol,:) = 0;
