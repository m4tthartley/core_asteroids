##
##  Created by Matt Hartley on 27/05/2025.
##  Copyright 2025 GiantJelly. All rights reserved.
##

set -e
mkdir -p ./build

files="main.c ../core/core/sysvideo_osx.m"
options="-g -fno-objc-arc"

clang -o ./build/asteroids $files \
	-I../core \
	-fno-objc-arc \
	-framework Metal \
	-framework OpenGL \
	-framework Cocoa \
	-framework QuartzCore \
	$options \

# -Wl,-rpath,@executable_path/Frameworks \
