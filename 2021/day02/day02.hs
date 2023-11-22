import Data.List.Split
import Data.List

move :: [String] -> (Int, Int)
move ["forward", x] = (read x :: Int, 0)
move ["down",    x] = (0,             read x :: Int)
move ["up",      x] = (0,           -(read x :: Int))

step1 :: (Int, Int) -> (Int, Int) -> (Int, Int)
step1 (x, y) (dx, dy) = (x + dx, y + dy)

solve1 :: String -> (Int, Int)
solve1 str = foldl step1 (0, 0) . map move $ splitOn " " <$> lines str

step2 :: (Int, Int, Int) -> (Int, Int) -> (Int, Int, Int)
step2 (x, y, a) (dx, dy) = (x + dx, y + a*dx, a+dy)

solve2 :: String -> (Int, Int, Int)
solve2 str = foldl step2 (0, 0, 0) . map move $ splitOn " " <$> lines str

main :: IO ()
main = do
    let file = "day2_sample_input.txt"
    raw <- readFile file
    let (x, y) = solve1 raw
    putStrLn("sample input 2")
    putStr("1: ")
    print $ x*y
    let (x, y, a) = solve2 raw
    putStr("2: ")
    print $ x*y
    putStrLn("input 2")
    let file = "day2_input.txt"
    raw <- readFile file
    let (x, y) = solve1 raw
    putStr("1: ")
    print $ x*y
    let (x, y, a) = solve2 raw
    putStr("2: ")
    print $ x*y
