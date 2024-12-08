-- Calculates the differences between adjacent elements in an array
-- https://stackoverflow.com/questions/8409022/haskell-calculate-differences-of-every-pair-of-adjacent-elements-in-a-list
differences :: [Int] -> [Int]
differences xs = zipWith (-) xs (tail xs)

solve1 :: [Int] -> Int
solve1 xs = length [ x | x <- differences xs, x < 0]

sum' :: Int -> Int -> Int -> Int
sum' a b c = a + b + c

-- Inspiration from above...
sliding_window :: [Int] -> [Int]
sliding_window xs = zipWith3 (sum') xs (tail xs) (tail $ tail xs)

solve2 :: [Int] -> Int
solve2 xs = length [ x | x <- differences $ sliding_window xs, x < 0]

convert :: String -> [Int]
convert x = map read (lines x) :: [Int]

-- Herregud....
-- https://stackoverflow.com/questions/52528547/read-list-of-numbers-in-haskell
main :: IO ()
main = do
    let file = "day_1_sample_input.txt"
    raw <- readFile file
    print $ solve1 (convert raw)
    let file = "day_1_input.txt"
    raw <- readFile file
    print $ solve1 (convert raw)
    let file = "day_1_sample_input.txt"
    raw <- readFile file
    print $ solve2 (convert raw)
    let file = "day_1_input.txt"
    raw <- readFile file
    print $ solve2 (convert raw)
