# Morphology
C++ Morphological Image Processing program

Morphological image processing is a collection of non-linear operations related to the shape or morphology of features in an image. 

This program takes a Binary Image text input image which includes a header for its number of rows, columns, min and max values for the proceeding image.

The structuring element [SE] is a matrix for which the operations will use to perform on the binary image. 
The SE includes number of rows, cols, min and max as well as a row and column origin to notify the operators where to center the SE around.

This morphology program runs and operates on the binary image as long as SE elements and operations are chosen, until the user decides to quit. 

Input 1 - Binary Image including: [ROW, COL, Min, Max] header
Input 2 - Structuring Element including: [ROW, COL, Min, Max, RowOrigin, ColOrigin] header

Input 3 - Character for operation to be performed 
E-Erosion
shrink image regions

D-Dilation  
grow image regions

C-Closing
structured filling in of image region boundary pixels

O-Opening
structured removal of image region boundary pixels

//////////
Example Binary image in input.txt
Example SE in input2.txt

- After compiling run with:
main input.txt input2.txt [Choice of E,D,C,O operations]

Output.txt automatically generated/rewritten for end results.
