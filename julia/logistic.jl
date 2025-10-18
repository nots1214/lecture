using LinearAlgebra
using IntervalArithmetic

function logistic()
   #lam = 3.82843
   # lam = 4
   #lam = 3.8777
   lam = 3.8334
   # 写像Fを定義する
   F((x, y, z)) = [x-lam*z*(1-z)
   y-lam*x*(1-x)
   z-lam*y*(1-y)]
   # ヤコビ行列DFを定義
   Df((x, y, z)) = [1 0 -lam*(1-2*z);-lam*(1-2*x) 1 0;
   0 -lam*(1-2*y) 1]
   # 初期値を設定
   tol = 1e-12
   p = Inf
   X0 = [1;-1; 1]
   X = X0
   num_itr = 0
   FX = F(X)
   println("Before iteration: $(norm(FX,p))")
   # ニュートン法を計算する
   while num_itr ≤ 100
     dx = Df(X)\FX 
     X = X- dx
     num_itr += 1
     FX = F(X)
     println("After $(num_itr) th iteration: $(norm(FX,p))")
     if norm(FX,p) < tol
        break
     end
    end
    @show X
    itr = 0
    t = X[1]
    f(t) = lam*t*(1-t)
    while itr < 100
        t=f(t)
        itr = itr + 1
        if itr > 90
          @show t
        end
    end
    return X
end

function nk_logistic(X)
   #lam = 3.8777
   lam = 3.8334
   p = Inf
   # 写像Fを定義する
   F((x, y, z)) = [x-lam*z*(1-z)
   y-lam*x*(1-x)
   z-lam*y*(1-y)]
   # ヤコビ行列DFを定義
   Df((x, y, z)) = [1 0 -lam*(1-2*z);-lam*(1-2*x) 1 0;
   0 -lam*(1-2*y) 1]
   iX = map(Interval,X)
   A = inv(Df(X))
   Y0 = norm(A*F(iX),p)
   @show Y0
   Z0 = opnorm(Matrix{Float64}(I,size(A))- A*Df(iX),p)
   @show Z0
   Z1 = 0
   Z2 = 2*lam*opnorm(map(Interval,A),p)
   @show Z2
   # p(r) = Z2*r̂ 2- (1-Z1-Z0)*r + Y0
   a = Z2
   b =-(1-Z1-Z0)
   c = Y0
   if sup(b^2-4*a*c) < 0
     println("error: cannot find root of radii polynomial")
   else
     r_min = (-b- sqrt(b^2-4*a*c))/2/a
     r_max = (-b + sqrt(b^2-4*a*c))/2/a
   end
   @show sup(r_min), inf(r_max)
   r0 = sup(r_min)
   if sup(a*r0^2 + b*r0 + c) < 0 # validate p(r0) < 0
     sol1 = X .- sup(r_min) 
     sol2 = X .+ sup(r_min)
   end
   @show sol1
   @show sol2
end

X = logistic()
nk_logistic(X)