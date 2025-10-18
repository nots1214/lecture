using SpecialFunctions
using ApproxFun
using Plots
using FFTW
using Pkg


function chebpts(n, a=-5, b=5) # n: maximum order of Chebyshev polynomials
    tt = range(0, stop=π, length=n+1)
    x = cos.(tt)
    return (1.0 .- x).*a/2 + (1.0 .+ x).*b/2
end

M = 150# number of Chebyshev polynimals
#fc = Fun(x->exp(erf(x^2)+x.^5).*sin(3*pi*x) + x, Chebyshev(), M)
fc = Fun(x->exp(sin(x))+exp(cos(x))-exp(atan(x)) + x,Chebyshev(Interval(-5.0,5.0)),M)
n = ncoefficients(fc)- 1 # maximum order of Chebyshev polynomials (n = M-1)
p = plot(fc,
  xlabel = "\$x\$",
  ylabel = "\$f(x)\$",
  line = 3,
  title = "\$f(x) = \\exp(\\sin(x)) + \\exp(\\cos(x)) - \\exp(\\arctan(x)) + x\$",
  legend  = false,
)
cpts = chebpts(n)
fvals = fc.(cpts)
scatter!(p, cpts,fvals)
savefig(p,"cheb.png")

FourierCoeffs = real(fftshift(fft([fvals;reverse(fvals[2:end-1])])))/(2M-2)
Cheb_onesided = reverse(FourierCoeffs[1:M])
Cheb_twosided = similar(Cheb_onesided)
Cheb_twosided[1] = Cheb_onesided[1]
Cheb_twosided[end] = Cheb_onesided[end]
Cheb_twosided[2:end-1] = 2*Cheb_onesided[2:end-1]
println(reshape([coefficients(fc);Cheb_twosided],M,2))