import math
from scipy import integrate

#For comparing the number of evaluations of the integrand, I asked gpt-5-mini to write a code to get it in python

class EvalCounter:
    def __init__(self, func):
        self.func = func
        self.count = 0
    def __call__(self, x):
        self.count += 1
        return self.func(x)

def main():
    # integrands and analytic results
    f1 = lambda x: 1.0 / math.sqrt(x)           # ∫_0^1 x^-1/2 dx = 2
    f2 = lambda x: math.log(x) / math.sqrt(x)   # ∫_0^1 ln(x) / sqrt(x) dx = -4
    f3 = lambda x: math.exp(-x)                 # ∫_0^∞ e^{-x} dx = 1
    f4 = lambda x: math.exp(-x*x)               # ∫_0^∞ e^{-x^2} dx = sqrt(pi)/2
    f5 = lambda x: 1.0 / (1.0 + x*x)            # ∫_0^∞ 1/(1+x^2) dx = pi/2


    analytic1 = 2.0
    analytic2 = -4.0
    analytic3 = 1.0
    analytic4 = 0.5 * math.sqrt(math.pi)
    analytic5 = 0.5 * math.pi

    # requested tolerances
    acc = 1e-3
    eps = 1e-3

    cf1 = EvalCounter(f1)
    cf2 = EvalCounter(f2)

    # integrate f1
    result1, err1 = integrate.quad(cf1, 0.0, 1.0, epsabs=acc, epsrel=eps, limit=200)
    evals1 = cf1.count
    print("Integral ∫_0^1 1/sqrt(x) dx")
    print(f"  SciPy quad result = {result1:.12g}  error est = {err1:.3g}  evaluations = {evals1}")
    print(f"  analytic = {analytic1}  abs error = {abs(result1 - analytic1):.3g}")
    print()

    # integrate f2
    result2, err2 = integrate.quad(cf2, 0.0, 1.0, epsabs=acc, epsrel=eps, limit=200)
    evals2 = cf2.count
    print("Integral ∫_0^1 ln(x)/sqrt(x) dx")
    print(f"  SciPy quad result = {result2:.12g}  error est = {err2:.3g}  evaluations = {evals2}")
    print(f"  analytic = {analytic2}  abs error = {abs(result2 - analytic2):.3g}")
    print()

    # integrate f3
    cf3 = EvalCounter(f3)
    result3, err3 = integrate.quad(cf3, 0.0, math.inf, epsabs=acc, epsrel=eps, limit=200)
    evals3 = cf3.count
    print("Integral ∫_0^∞ e^{-x} dx")
    print(f"  SciPy quad result = {result3:.12g}  error est = {err3:.3g}  evaluations = {evals3}")
    print(f"  analytic = {analytic3}  abs error = {abs(result3 - analytic3):.3g}")
    print()

    # integrate f4
    cf4 = EvalCounter(f4)
    result4, err4 = integrate.quad(cf4, 0.0, math.inf, epsabs=acc, epsrel=eps, limit=200)
    evals4 = cf4.count
    print("Integral ∫_0^∞ e^{-x^2} dx")
    print(f"  SciPy quad result = {result4:.12g}  error est = {err4:.3g}  evaluations = {evals4}")
    print(f"  analytic = {analytic4}  abs error = {abs(result4 - analytic4):.3g}")
    print()

    # integrate f5
    cf5 = EvalCounter(f5)
    result5, err5 = integrate.quad(cf5, 0.0, math.inf, epsabs=acc, epsrel=eps, limit=200)
    evals5 = cf5.count
    print("Integral ∫_0^∞ 1/(1+x^2) dx")
    print(f"  SciPy quad result = {result5:.12g}  error est = {err5:.3g}  evaluations = {evals5}")
    print(f"  analytic = {analytic5}  abs error = {abs(result5 - analytic5):.3g}")
    print()

if __name__ == "__main__":
    main()
