# PPM Image Viewer (SDL2)

This is a simple PPM (P6) image viewer written in C using **SDL2**.  
It reads raw pixel data from **stdin**, parses the PPM header, and renders the image pixel-by-pixel onto an SDL2 window.

---

## 🚀 Features

- Reads **PPM (P6)** images from standard input
- Parses image width, height, and pixel data
- Creates an SDL2 window matching the image dimensions
- Renders each pixel manually using `SDL_FillRect`
- Displays the final image until the user closes the window

---

## 📸 Supported Format

Only **binary PPM (P6)** files are supported.

A valid P6 header looks like:

```
P6
# optional comment
WIDTH HEIGHT
255
```

Followed by raw bytes in RGBRGBRGB… format.

---

## 🔧 Build Instructions

Make sure SDL2 is installed.

### On Arch / Manjaro

```bash
sudo pacman -S sdl2
```

### Compile

```bash
gcc iv.c -o iv $(sdl2-config --cflags --libs)
```

---

## ▶️ Usage

Run the viewer by piping a PPM file into the program:

```bash
cat image.ppm | ./iv
```

or:

```bash
./iv < image.ppm
```

The program will:

1. Read the PPM header  
2. Parse width and height  
3. Create an SDL window  
4. Render every pixel  
5. Display the image until the window is closed  

---

## 📂 Code Overview

### **1. Read PPM Header**

The program reads:
- Magic number (`P6`)
- Comment line
- Dimensions (`width height`)
- Max color value

```c
fgets(...); // Read header lines
sscanf(...); // Extract width & height
```

---

### **2. Create an SDL Window**

```c
SDL_Window *pwindow = SDL_CreateWindow(
    "PPM Image Viewer",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    width, height,
    0
);

SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
```

---

### **3. Render Pixels**

Each pixel is read as three bytes (RGB):

```c
Uint8 r = getchar();
Uint8 g = getchar();
Uint8 b = getchar();
```

Mapped to SDL format:

```c
Uint32 color = SDL_MapRGB(psurface->format, r, g, b);
```

And drawn using a 1×1 rectangle:

```c
pixel.x = x;
pixel.y = y;
SDL_FillRect(psurface, &pixel, color);
```

---

## 🛑 Limitations

- Only supports **PPM P6** format (no P3 / ASCII mode)
- Does not check for malformed headers
- Rendering each pixel individually is slow for very large images
- Depends on SDL window surface API (not renderer)
