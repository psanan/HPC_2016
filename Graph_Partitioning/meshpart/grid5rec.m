function [A,xy] = grid5rec(k1, k2)
% GRID5lrec : Generate 5-point finite difference on a rectangular mesh.
%
% [A,xy] = GRID5REC(k) returns a k1*k2-by-k1*k2 symmetric positive definite 
%        matrix A with the structure of the k-by-k 5-point grid,
%        and an array xy of coordinates for the grid points.
%
% John Gilbert, Xerox PARC, 1992.
% Copyright (c) 1990-1996 by Xerox Corporation.  All rights reserved.
% HELP COPYRIGHT for complete copyright and licensing notice.

a = blockdiags ([-1 4 -1], -1:1, k1, k1);
I = speye (k1, k1);
A = blockdiags ([-I a -I], -1:1, k2, k2);

[x,y] = meshgrid(1:k2, 1:k1);
xy = zeros(k1*k2,2);
xy(:,1) = x(:);
xy(:,2) = y(:);


