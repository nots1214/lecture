using ApproxFun, FFTW

include("FourierChebyshev.jl")
 #f(x) の概形
f(x) = exp(sin(5x))/(1+sin(cos(x)))
#p=plot(f,0,2π)


fc = Fun(f,Laurent())
m = ncoefficients(fc)
M = Int((m+1)/2)
c = coefficients(fc) # coefficients of ApproxFun
function index_shift(c) # convert c-> fourier coeffs
 return [reverse(c[2:2:end]);c[1:2:end]]
end
a = fouriercoeffs(f,M)
#plot(-M+1:M-1,abs.(a),yscale=:log10,label="computed via FFT")
#plot!(-M+1:M-1,abs.(index_shift(c)),yscale=:log10,label = "ApproxFun")
#savefig("fftcoeff.png")
#plot(real(fc)^2)
# FFT Algorithm
p = 2
N = (p-1)*M
ta = [zeros(N,1);a;zeros(N,1)] # 1. Padding zeros
tb = ifft(ifftshift(ta)) # 2. IFFT of ta
tbp = tb.^p # 3. tb*^tb
cp = fftshift(fft(tbp))*(2.0*p*M-1)^(p-1) # 4. FFT of tb2
plot_fourier!(cp[p:end-(p-1)])

savefig("fc^2.png")