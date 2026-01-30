$clangPath = "D:/msys64/clang64/bin/clang++.exe"

$flags = @(
    "-std=c++20"
    "-Wall"
    "-Wextra"
    "-fcolor-diagnostics"
    "-fansi-escape-codes"
    "-g"
)

$includes = @(
    "-I./Utils/include"
    "-I./LinearAlgebra/include"
    "-I./MachineLearning/CustomNeuralNetwork/include"
)

$sources = Get-ChildItem `
    -Path './LinearAlgebra/src', './MachineLearning/CustomNeuralNetwork/src' `
    -Filter '*.cpp' -Recurse |
    ForEach-Object { $_.FullName }
    
$mainSource = "main.cpp"
$output = "-o"
$outputExe = "main.exe"

& $clangPath `
    $flags `
    $includes `
    $sources `
    $mainSource `
    $output `
    $outputExe