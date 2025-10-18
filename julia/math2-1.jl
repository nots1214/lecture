using IntervalArithmetic

function newton_method()
    f(x) = x^3 - 3x
    Df(x) = 3x^2-3
    num_itr = 0
    tol = 1e-12
    x = 2.0
    Fx = f(x)

    println("Before iteration: $(Fx)")

    while num_itr ≤ 10
        dx = Fx / Df(x)
        x = x - dx
        num_itr += 1
        Fx = f(x)
        println("After $(num_itr) iteration: $(Fx)")
        if abs(Fx) < tol
            break
        end
    end

    @show x
    @show sqrt(3.0)
    return x
end

function newton_kantorovich(x)
    f(x) = x^3 - 3x
    Df(x) = 3x^2-3
    ix = map(Interval,x)
    # Y0 bound
    Y0 = abs(f(ix))/abs(3*ix^2-3)
    @show Y0
    # Z0 bound
    Z0 = abs(1- (1/(3*ix^2-3))*(3*ix^2-3))
    @show Z0
    # Z1 bound
    Z1 = 0
    # Z2 bound
    Z2 = 4/abs(ix^2-1)
    @show Z2
    # p(r)を求める
    a =Z2
    b =-(1-Z1-Z0)
    c = Y0
    if sup(b^2-4*a*c) < 0
      println("error: connot find the root of radii polynomial")
    else
      r_min = (-b- sqrt(b^2-4*a*c))/2/a
      r_max = (-b + sqrt(b^2-4*a*c))/2/a
    end
    @show sup(r_min), inf(r_max)
    r0 = sup(r_min);
    if sup(a*r0^2 + b*r0 + c) < 0 # validate p(r0) < 0
      sol1 = x + sup(r_min)
      sol2 = x - sup(r_min)
    end
    @show sol2
    @show sol1
end

x = newton_method()
newton_kantorovich(x)