# SDL Game Development (Mitchell)



[TOC]

# Settings

## zlib installation

```
vcpkg install zlib
vcpkg install sdl2
vcpkg install sdl2-image
vcpkg install cpp-base64
vcpkg install tinyxml2
vcpkg integrate install
```

## Define macros for project

```
SDL_MAIN_HANDLED
```







# Old Style Settings (without vcpkg)





## Dependencies tree view (for the binary files)

```
SDL2
  include
    SDL2
      SDL_*.h
  Win32
    Debug
      SDL2.lib
      SDL2_image.lib
      SDL2main.lib
    Release
      SDL2.lib
      SDL2_image.lib
      SDL2main.lib
```





## Output tree view

```
libjpeg-9.dll
libpng16-16.dll
libtiff-5.dll
libwebp-7.dll
SDL2.dll
zlib1.dll
SDLGame.exe
```





## SDL2_Image

```
Additional Include Directories
$(SolutionDir)..\..\..\Dependencies\SDL2\include\SDL2;

Additional Library Directories
$(SolutionDir)..\..\..\Dependencies\SDL2\$(Platform)\$(Configuration)
```





### Troubleshooting

SDL2_image.lib file was not generated.

Resolve it to build static library instead of dynamic.

Next dll's should be copied to output folder for game:

```
libjpeg-9.dll
libpng16-16.dll
libtiff-5.dll
libwebp-7.dll
zlib1.dll
```

This help me to debug and resolve issue:

```
SDL_Surface* pTempSurface = IMG_Load("assets/animate-alpha.png");
std::cout << "IMG_Load returns " << pTempSurface << ", IMG_GetError() = " << IMG_GetError() << std::endl;
```

