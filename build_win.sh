##
##  Created by Matt Hartley on 28/05/2025.
##  Copyright 2025 GiantJelly. All rights reserved.
##

set -e
mkdir -p ./build

files="main.c ../core/core/sysvideo_win32.c"
options="-g -luser32 -lgdi32 -lopengl32 -lglu32"

# clang -o ./build/asteroids.exe $files \
# 	-I../core \
# 	$options \

gcc -o ./build/asteroids.exe $files \
	-I../core \
	$options \

# -Wl,-rpath,@executable_path/Frameworks \
