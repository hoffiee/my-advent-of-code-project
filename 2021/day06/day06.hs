-- dynamic solution from https://www.reddit.com/r/adventofcode/comments/r9z49j/2021_day_6_solutions/hngi4hp/
-- try to understand what happens here...
-- parse input

g :: Int -> Int
g = (map g' [0 ..] !!)
    where
        g' 0 = 1
        g' n | n < 9 = 0
        g' n = g (n - 9) + g (n - 7)

f :: Int -> Int
f = (map f' [0 ..] !!)
    where
        f' 0 = 1
        f' n = f (n - 1) + g n

solve :: Int -> [Int] -> Int
solve days = sum . map (\i -> f (days + 8 - i))

part1 :: [Int] -> Int
part1 = solve 80

part2 :: [Int] -> Int
part2 = solve 256
