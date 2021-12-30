# Settings

## Temporary build folders

```
SDL2_image-2.0.5
SDL2-2.0.18
```

## Dependencies tree view

```
SDL2
  include
    SDL2
      <header-files>
  Win32
    Debug
      <dll and lib files>
    Release
      <dll and lib files>
```

## SDL2_Image

```
Additional Include Directories
$(SolutionDir)..\..\..\Dependencies\SDL2\include\SDL2;

Additional Library Directories
$(SolutionDir)..\..\..\Dependencies\SDL2\$(Platform)\$(Configuration)
```

### Issue

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

