function initial_condition(a₁, n, r)
    θⱼ = [2(j-1)+1/2 for j in 1:n]
    return r*exp.(1.0im*π*θⱼ/n) .- a₁/n
end

function iteration(a, z, num)
    n = length(a)
    P(z) = sum(a .* [z^k for k in n-1:-1:0]) + z^n
    for k in 1:num
        denom = [prod([z[i]-z[j] for j in 1:n if i != j]) for i in 1:n]
        z = z .- P.(z) ./ denom
    end
    return z
end

function find_roots(a, r, num)
    n = length(a)
    z = initial_condition(a[1], n, r)
    return iteration(a, z, num)
end

sol = find_roots([1,1,1],2,100)
@show sol