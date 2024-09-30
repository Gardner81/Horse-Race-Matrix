
Project Title: Odds Matrix Equation

The purpose of this project:

This project is about the use of n-dimensional vectors and n-by-n matrices to model mathematical properties 
from the bookmaker's perspective of either:

(1) a race with n horses, or 

(2) a two team (or two player) game in the special case where n=3 (home, draw, away) 

In particular, given (i) the probabilities of each possible outcome and
(ii) the vigorish (i.e., commission charged by the bookmaker) then it is possible to
calculate the profit in case of each possible outcome given the wagers on each
outcome, and vice versa, to calculate the wagers on each outcome given 
the profits of each outcome.  The expected profit (from the bookmaker's
point of view) can also be calculated.

The mathematical details of this calculation are discussed in the .pdf file included in this folder.

These calculations are best represented with n-dimensional vectors and n-by-n matrices.
The equation Aw = p expresses this relationship where the ith component of the vector w
is the total wager on the ith horse, and the ith component of the vector p is the profit to
the bookmaker in case the ith horse wins (note the ith wager is assumed to be positive, but the 
ith profit may or may not be positive, in which case a negative value represents a financial
loss to the bookmaker). To simplify the matter, we consider only the winner, but neither
place nor show, and for simplicity we ignore the possibility of a dead heat for first place in the race, and
we maintain the assumption that for each horse in the race, the probability of winning is strictly
greater than zero.

The matrix A is both symmetric and invertible (on the assumption that the vigorish is non-zero, see .pdf)
such that A = B - C where (i) B is the n-by-n matrix where B(i,j) = 1 for all i and j and (ii) C is the n-by-n
matrix where C(i,i) = the decimal odds on the ith horse, and C(i,j) = 0 when i is not j.

Hence if D denotes the inverse of A (which always exists provided vigorish is positive, see .pdf for
proof) then we can express the relation as Dp = w where p and w are defined as above. Notice from
the definitions above both A and D are symmetric matrices.

If the vector t is such that t(i) = the probability of the ith outcome and the vector p is as above, 
i.e, such that p(i) is the bookmaker's profit in case of the ith outcome then the expected profit
(from the bookmaker's perspective) is clearly the dot-product t*p.

If the commission is the real number u such that 0 < u < 1, then the odds vector v is such
that v(i) = 1/[(1+u)*t(i)]

How to use this program:

This folder does not contain an executeable file, it contains a (reasonably thoroughly) commented 
source code written in c++ which must first be compiled to execute. 

When run, this program first randomly generates a set of probabilities for an 8 horse race,
and the user then (i) chooses the real number u = the percent vigorish (i.e. bookmaker's commission),
and (ii) decides whether to introduce some random noise in the wagers (which are otherwise set in
exact proportion to the outcome probabilities where the sum of all wagers is one million dollars).
Based on these two decisions, the output of the program displays the vectors, matricies and scalars
as defined above: t, v, w, p, the matrices A and D, the total wagers and the expected profit from
the bookmakers point of view.

The source code included can easily be modified and adapted to, e.g.,

(1) allow the user to set the outcome probabilities, to choose the exact wagers on each horse, or alternatively to set
the profit for each outcome,

(2) to alter the amount of noise in the wagers, to make the total amount of wagers random, or to make the wagers
completely random,

(3) to assess whether (given distribution of probabilities) a choice of commission results in
a "Dutch Book" where the "book" is "Dutch" when the ordered pair (t,u) is such that p(i) > 0 for all i,
t,u,p defined as above).

(4) Given a fixed commission, what range of outcome probability distributions make for a Dutch book

(5) Given a fixed outcome probability distribution, what range (i.e., what minimum) choice of commission u 
results in a Dutch book

(6) To model a full "season" i.e., multiple races with different values of t for fixed vigorish u

(7) To model a full "season" i.e., multiple races with different values of commission u for a fixed
outcome probability distribution t

(8) To enable the user to choose a probability for each horse based on user input of points

and any combination of two or more of these, and otherwise a number of other possible  modifications.
