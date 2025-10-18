using SpecialFunctions
include("FourierChebyshev.jl")

M = 150; p = 2
f(x) = erf(sin(3x)+cos(2x))^4
g(x) = f(x)^p
plot(g , 0 , 2π,size=(800,400),legend=false,xlabel="\$x\$", ylabel="\$f(x)^p\$")
a = fouriercoeffs(f,M) # size(a) = 2M-1
function powerconvfourier(a::Vector{Complex{T}},p) where T
 M = Int((length(a)+1)/2)
 N = (p-1)*M
 ta = [zeros(N,1);a;zeros(N,1)] # 1. Padding zeros: size(ta) = 2pM-1
 tb = ifft(ifftshift(ta)) # 2. IFFT of ta
 tbp = tb.^p # 3. tb*^tb
 cp = fftshift(fft(tbp))*(2.0*p*M-1)^(p-1)
 return cp[N+1:end-N], cp[p:end-(p-1)] # return (truncated, full) version
end
ap, ap_full = powerconvfourier(a,p)
plot_fourier!(ap_full)
savefig("fftgraphcomparison.png")