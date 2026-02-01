#### Getting the clang++ path dynamically ####
# $clangPath = "D:/msys64/clang64/bin/clang++.exe"
$clangPath = Get-Command "clang++" -ErrorAction SilentlyContinue | Select-Object -ExpandProperty Source
if (-not $clangPath) {
    Write-Error "Clang++ not found in system PATH. Please ensure LLVM/Clang or MSYS2 is installed and added to PATH."
    exit 1
}


#### Building script ####
$objDir = "./obj"
if (-not (Test-Path $objDir)) { #Creates 'obj' dir to store .o files
    New-Item -ItemType Directory -Path $objDir 
}

$flags = @(
    "-std=c++20", 

    "-Wall", 
    # "-Wextra",
    # "-O3",
    "-fcolor-diagnostics", 
    "-fansi-escape-codes",
    "-g",
    "-MMD",
    "-MP"
)

$includes = @(
    "-I./Utils/include", 
    "-I./LinearAlgebra/include", 
    "-I./MachineLearning/CustomNeuralNetwork/include"
)

$sources = Get-ChildItem `
    -Path './Utils/src', './LinearAlgebra/src', './MachineLearning/CustomNeuralNetwork/src' `
    -Filter '*.cpp' -Recurse
$sources += Get-Item "main.cpp"

$tppFiles = Get-ChildItem `
    -Path './Utils/include', `
          './LinearAlgebra/include', `
          './MachineLearning/CustomNeuralNetwork/include' `
    -Filter '*.tpp' -Recurse

$objectFiles = @(
)

foreach ($file in $sources) {
    # Define the object path and add to array
    $objFile = Join-Path $objDir ($file.BaseName + ".o")
    $depFile = Join-Path $objDir ($file.BaseName + ".d")
    $objectFiles += $objFile

    # Recompile file if .o doesn't exist or .cpp/.tpp is newer than .o
    $needsCompile = $false
    if (-not (Test-Path $objFile)) {
        $needsCompile = $true
        $reason = "Object file missing"
    }
    elseif ($file.LastWriteTime -gt (Get-Item $objFile).LastWriteTime) {
        $needsCompile = $true
        $reason = "Source file ($($file.Name)) was modified"
    }
    elseif (Test-Path $depFile) {
        $deps = Get-Content $depFile -Raw
        $deps = $deps -replace "^[^:]+:\s*", "" -replace "\\\r?\n", " "
        $depPaths = $deps -split "\s+" | Where-Object { $_ -match '\S' }
        foreach ($path in $depPaths) {
            if (Test-Path $path) {
                if ((Get-Item $path).LastWriteTime -gt (Get-Item $objFile).LastWriteTime) {
                    $needsCompile = $true
                    $reason = "Dependency changed: $(Split-Path $path -Leaf)"
                    break
                }
            }
        }
    }
    if ($needsCompile) {
        Write-Host "Compiling: $($file.Name) [$reason]" -ForegroundColor Cyan
        & $clangPath $flags $includes -c $file.FullName -o $objFile
        if ($LASTEXITCODE -ne 0) { 
            Write-Error "Compilation failed!"; exit $LASTEXITCODE
        }
    }
}


### Deletes .o and .d files in the obj dir that are no longer required
$existingFiles = Get-ChildItem $objDir -File
foreach ($file in $existingFiles) {
    # Check if this .o or .d file belongs to a current source file
    $requiredFile = $false
    foreach ($expected in $objectFiles) {
        $expectedName = [System.IO.Path]::GetFileNameWithoutExtension($expected)
        if ($file.BaseName -eq $expectedName) {
            $requiredFile = $true
            break
        }
    }
    # Delete file if not required
    if (-not $requiredFile) {
        Write-Host "Deleting unecessary file: $($file.Name)" -ForegroundColor Magenta
        Remove-Item $file.FullName -Force
    }
}



### Linking only runs if the exe is missing or any .o is newer than the exe
$outputExe = "main.exe"
$needsLinking = $false
if (-not (Test-Path $outputExe)) { 
    $needsLinking = $true 
}
else {
    foreach ($obj in $objectFiles) {
        if ((Get-Item $obj).LastWriteTime -gt (Get-Item $outputExe).LastWriteTime) {
            $needsLinking = $true; break
        }
    }
}

if ($needsLinking) {
    Write-Host "Linking $outputExe..." -ForegroundColor Green
    & $clangPath $objectFiles -o $outputExe
} else {
    Write-Host "Everything up to date. No building needed." -ForegroundColor Gray
}