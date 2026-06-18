Adaptive recursive integrator with subdivision into three subintervals

Implement a (one-dimensional) adaptive recursive integrator which at each iteration subdivides the interval not into two, but into three sub-intervals.

For example, a rule like this,
xi={1/6,3/6,5/6} reusable points for division by 3;
wi={3/8,2/8,3/8} trapezium (higher order) rule; 
vi={1/3,1/3,1/3} rectangle (lower order) rule; 


Tasks:
(A)
Implement an adaptive division-by-three integrator with the signature:

double adaptive3(
	Func<double,double> integrand,
	double a,double b,
	double acc=1e-3,double eps=1e-3,
	double f2=NaN
	)
that takes a function 'integrand' and calculates its integral from 'a' to 'b' with the absolute accuracy 'acc' and relative accuracy 'eps' (reusing the points from the previous iteration).
Test your integrator on some interesting integrals (for example, from the homework "recursive adaptive integration") and check that the returned result is within the required accuracy goal, that is, check that

|result-exact| ≤ acc + |exact|*eps .

Record the number of integrand evaluations during the integration of these integrals and compare with your integrator from the homework.

(B)
Implement the Clenshaw–Curtis variable transformation method. Compare the number of integrand evaluations with your 'adaptive3' integrator and with your integrator from your homework.

(C)
Make your integrator estimate and return the error.

Make your integrator accept infinite limits.

Try calculate 'erf(1)' with the maximum precision that your integrator can do.



Reflection: The given task on the webpage (copied it to this file) was comparable to the homework task for recursive adaptive integration. Therefore, I did not add more to it. Everything works, so if we use that criteria, I would give myself 10 points. 

About the code: In the code, I choose to first implement the recusrive adaptive integrator with 3 sub-intervals which also returns the estimated error. I choose to have 3 error messages (max_depth, interval width is 0 (machine precision) and integrand evaluated as inf or nan). I choose to just display a message instead of throwing an error. For the integrals tested by the integrator, this seems just fine. Eventhough on ∫_0^1 dx 1/√(x) and ∫_0^1 dx ln(x)/√(x), all 3 error messages show, the final result is good. It looks like the integrator likes to zoom in on singularities until it can't further zoom in. The width of the interval will go to 0, so I think it will be fine to set it to 0, but it is something to be carefull with.
In the end, for the integrator to accept +- infinity as boundaries of the integrals, I found it easier to make a new function (Integrate) which can accepts all boundaries. It checks if 1 or both of the boundaries is infinity, and transforms it accordingly (see page 12 lecture notes). It then calls the Clenshaw-Curtis (CC) transformation, since it seems like this transformation performs better on average. The CC transformation then calls the adaptive3 (recursive adaptive integrator with 3 sub-intervals).

About the project itself: At the beginning of the project, I made a mistake with splitting the interval in 3... This gave weird results for the integrals. After finding the mistake, everything worked fine. When comparing the recursive adaptive integrator with 3 sub-intervals with the recusrive adaptive integrator with 2 sub-intervals (homework), there is some (but not significant) difference between the number of function evaluations. On most functions, the integrator from this project used less function evaluations, but on some functions (for example ln(x) / sqrt(x)) the homework integrator used less evaluations. In the end it all depends on the function. Since we sample in the middle with this integrator, it would have a hard time on functions with a singularity in the middle. 

Have a nice Summer!
