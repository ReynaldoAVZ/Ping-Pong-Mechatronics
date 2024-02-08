function [RGBvec] = ColorPicker(imageArray)
image(imageArray);
[clickedCol, clickedRow] = ginput(1);
clickedCol = round(clickedCol);
clickedRow = round(clickedRow);
R = imageArray(clickedRow, clickedCol, 1);
G = imageArray(clickedRow, clickedCol, 2);
B = imageArray(clickedRow, clickedCol, 3);
RGBvec = [R, G, B];
end
% Reynaldo Villarreal Zambrano, u1348597, ME EN 1010 HW11b