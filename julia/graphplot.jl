using FFTW
using Plots
f(x)=exp(sin(5x))/(1+sin(cos(x)))
N= 100
function fouriercoeffs(f,N)
 h = 2.0*π/(2N-1)
 xj = h*(0:2N-2)
 fj = f.(xj)
 return fftshift(fft(fj))/(2N-1)
end

bc = fouriercoeffs(f,N)
p=plot(-N+1:N-1, abs.(bc), yscale=:log10,
 legend=false,
 xlabel = "\$k\$",
 ylabel = "\$|\\bar{c}_k\\,|\$",
 title = "Absolute values of Fourier coefficients"
)
savefig(p, "fuorier.png")