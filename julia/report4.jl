using ApproxFun, FFTW

include("FourierChebyshev.jl")

 #f(x) の概形
f(x) = (sin(sin(x))+cos(cos(x)))/(sin(cos(x))+cos(sin(x)))
#plot(f,0,2π)

fc = Fun(f,Laurent())
m = ncoefficients(fc)
M = Int((m+1)/2)
h = 2π/(2M-1)
xx = h*(0:2M-2)
scatter(xx,f.(xx),ylabel = "\$f(x)\$",left_margin=10Plots.mm)

a = fouriercoeffs(f,M)

function ifourier(bc, I=[0,2π])
    # bc: Fourier coefficients
    a = I[1]; b = I[2]
    N = (length(bc)+1)/2 # 2N-1
    #n_pad = 500
    n_pad = 0
    bc_pad = [zeros(n_pad);bc;zeros(n_pad)]
    N_pad = N + n_pad
    h_pad = (b-a)/(2N_pad-1)
    xj_pad = a .+ h_pad*(0:2N_pad-2)
    fNj_pad = real((2N_pad-1)*ifft(ifftshift(bc_pad)))
    #plot!(xj_pad, fNj_pad, legend=false, xlabel = "\$x\$", ylabel = "\$f(x)\$")
    
    ih = 2π/(2N-1)
    ixx = ih*(0:2N-2)
    #scatter!(ixx,fNj_pad,ylabel = "\$ℱ^{-1}(ℱ(f(t))\$",left_margin=10Plots.mm)
    return fNj_pad
end

b = ifourier(a)
#scatter(xx, abs.(f.(xx).-b),left_margin=15Plots.mm)
# FFT Algorithm

savefig("f.png")
#savefig("ifftfft.png")
#savefig("ffconparison.png")
#savefig("diff.png")