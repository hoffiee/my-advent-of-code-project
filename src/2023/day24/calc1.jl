# Run in REPL with `include("calc.jl")
using LinearAlgebra
using Symbolics

# Part 1
# We describe a line with
# x0 + vt = x,
#
# We describe two lines that intersect at with
#
# x1 + v1*t1 = x2 + v2*t2, reformulate into
#
# v1*t1 - v2*t2 = x2 - x1
# [v1 -v2]'[t1 t2] = x2 - x1
#
# where ' denotes the transpose, collect the terms into the form
# At = b
#
# with A = [v1 -v2]' ∈ R²ˣ² and b = x2 - x1, b ∈ R²

p1 = [19, 13]
v1 = [-2, 1]

p2 = [18, 19]
v2 = [-1, -1]

function check(p1, v1, p2, v2)
    A = [v1 -v2]
    b = p2 - p1

    coord_min = [7, 7]
    coord_max = [27, 27]

    # check if they intersect
    if (rank(A) == 2)
        # case not handled here, collisions in the past,
        t1, _ = A\b
        if (coord_min <= p1 + v1*t1 <= coord_max)
            return true;
        end
    end

    return false;

end

# seems to work.
check(p1, v1, p2, v2)

# I'm lazy, so solve this here and copy the results to the C++ solution file
@variables x1 y1 vx1 vy1 x2 y2 vx2 vy2

A = [vx1 -vx2; vy1 -vy2]
b = [x2 - x1; y2 - y1]

A\b
