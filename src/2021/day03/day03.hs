
import Data.List.Split

convert :: String -> [[Int]]
convert x = map decode $ filter (/="") . splitOn "" <$> lines x

decode :: [String] -> [Int]
decode x = map (read :: String->Int) x

sum :: [[Int]] -> [Int]
sum = foldl add [0, 0 ..]

add :: [Int] -> [Int] -> [Int]
add _ []          = []
add [] _          = []
add (x:xs) (y:ys) = (x + y) : add xs ys

determine_epsilon :: Int -> Int
determine_epsilon x
    | x >= 0 = 1
    | x < 0 = 0

determine_gamma :: Int -> Int
determine_gamma x
    | x < 0 = 1
    | x >= 0 = 0

binaryToDecimal :: [Int] -> Int
binaryToDecimal = Prelude.sum . zipWith (\pow n -> n * 2 ^ pow) [0..] . reverse

main :: IO ()
main = do
    let file = "day3_sample_input.txt"
    raw <- readFile file
    putStrLn("sample input day 3")
    putStr("task 1: ")
    let ls = convert raw
    let middle = length ls `div` 2
    let epsilon = binaryToDecimal $ map determine_epsilon $ map (subtract middle) $ Main.sum $ convert raw
    let gamma = binaryToDecimal $ map determine_gamma $ map (subtract middle) $ Main.sum $ convert raw
    print $ epsilon * gamma

    let file = "day3_input.txt"
    raw <- readFile file
    putStrLn("input day 3")
    putStr("task 1: ")
    let ls = convert raw
    let middle = length ls `div` 2
    let epsilon = binaryToDecimal $ map determine_epsilon $ map (subtract middle) $ Main.sum $ convert raw
    let gamma = binaryToDecimal $ map determine_gamma $ map (subtract middle) $ Main.sum $ convert raw
    print $ epsilon * gamma
