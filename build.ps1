$clangPath = "D:/msys64/clang64/bin/clang++.exe"

$objDir = "./obj"
if (!(Test-Path $objDir)) { #Creates 'obj' dir to store .o files
    New-Item -ItemType Directory -Path $objDir 
}

$flags = @(
    "-std=c++20", 
    "-Wall", 
    # "-Wextra",
    # "-O3",
    "-fcolor-diagnostics", 
    "-fansi-escape-codes"
    "-g"
)

$includes = @(
    "-I./Utils/include", 
    "-I./LinearAlgebra/include", 
    "-I./MachineLearning/CustomNeuralNetwork/include"
)

$sources = Get-ChildItem `
    -Path './LinearAlgebra/src', './MachineLearning/CustomNeuralNetwork/src' `
    -Filter '*.cpp' -Recurse
$sources += Get-Item "main.cpp"

$objectFiles = @(
)

foreach ($file in $sources) {
    # Define the object path and add to array
    $objFile = Join-Path $objDir ($file.BaseName + ".o")
    $objectFiles += $objFile
    # Recompile file if .o doesn't exist or .cpp is newer than .o
    if (!(Test-Path $objFile) -or ($file.LastWriteTime -gt (Get-Item $objFile).LastWriteTime)) {
        Write-Host "Compiling: $($file.Name)" -ForegroundColor Cyan
        & $clangPath $flags $includes -c $file.FullName -o $objFile
        if ($LASTEXITCODE -ne 0) { 
            Write-Error "Compilation failed!"; exit $LASTEXITCODE 
        }
    }
}

# Linking only runs if the exe is missing or any .o is newer than the exe
$outputExe = "main.exe"

$needsLinking = $false
if (!(Test-Path $outputExe)) { 
    $needsLinking = $true 
}
else {
    foreach ($obj in $objectFiles) {
        if ((Get-Item $obj).LastWriteTime -gt (Get-Item $outputExe).LastWriteTime) {
            $needsLinking = $true
            break
        }
    }
}

if ($needsLinking) {
    Write-Host "Linking $outputExe..." -ForegroundColor Green
    & $clangPath $objectFiles -o $outputExe
} else {
    Write-Host "Everything up to date. No building needed." -ForegroundColor Gray
}

# Read-Host -Prompt "Press Enter to exit"