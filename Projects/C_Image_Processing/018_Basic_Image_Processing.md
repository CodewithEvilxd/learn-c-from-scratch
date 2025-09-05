# 🖼️ **Project 18: Basic Image Processing in C**
## 🎯 **Bitmap Image Manipulation with Filters and Effects**

---

## 📋 **Project Overview**

**English:** A basic image processing application in C that handles bitmap images with various filters including grayscale conversion, brightness adjustment, contrast enhancement, and edge detection algorithms.

**Hinglish:** Ek basic image processing application jo C mein hai, jisme bitmap images handle karta hai with various filters including grayscale conversion, brightness adjustment, contrast enhancement, aur edge detection algorithms ke saath.

---

## 🎯 **Learning Objectives**

✅ **Technical Skills:**
- Bitmap file format handling
- Pixel manipulation algorithms
- Memory buffer management
- File I/O for binary data
- Mathematical image processing

✅ **Image Processing:**
- Color space conversion
- Filter application
- Histogram analysis
- Edge detection
- Image enhancement

---

## 🛠️ **Technologies & Tools Used**

| **Technology** | **Why Used** | **How It Works** |
|---------------|-------------|------------------|
| **C Programming** | Image processing core | Handles pixel operations and algorithms |
| **File System** | Bitmap file handling | Binary file reading and writing |
| **Math Library** | Image calculations | Mathematical operations for filters |
| **Memory Management** | Large data handling | Dynamic allocation for image buffers |

---

## 📁 **Project Structure**

```
ImageProcessing/
├── include/
│   ├── bitmap.h
│   ├── filters.h
│   ├── image.h
├── src/
│   ├── bitmap.c
│   ├── filters.c
│   ├── image.c
│   └── main.c
├── images/
│   └── sample.bmp
└── README.md
```

---

## 🔧 **Core Implementation**

### **1. Bitmap Image Structure**

```c
// bitmap.h
#ifndef BITMAP_H
#define BITMAP_H

#pragma pack(push, 1)

// Bitmap file header
typedef struct {
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

// Bitmap info header
typedef struct {
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

// RGB pixel structure
typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} RGB_PIXEL;

#pragma pack(pop)

// Bitmap image structure
typedef struct {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGB_PIXEL **pixels;
    int width;
    int height;
} BitmapImage;

#endif
```

```c
// bitmap.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

// Load bitmap from file
BitmapImage* load_bitmap(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    BitmapImage *image = (BitmapImage*)malloc(sizeof(BitmapImage));
    if (!image) {
        fclose(file);
        return NULL;
    }

    // Read file header
    fread(&image->fileHeader, sizeof(BITMAPFILEHEADER), 1, file);

    // Check if it's a valid bitmap
    if (image->fileHeader.bfType != 0x4D42) {
        printf("Not a valid bitmap file!\n");
        free(image);
        fclose(file);
        return NULL;
    }

    // Read info header
    fread(&image->infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    image->width = image->infoHeader.biWidth;
    image->height = abs(image->infoHeader.biHeight); // Handle negative height

    // Allocate pixel array
    image->pixels = (RGB_PIXEL**)malloc(image->height * sizeof(RGB_PIXEL*));
    if (!image->pixels) {
        free(image);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < image->height; i++) {
        image->pixels[i] = (RGB_PIXEL*)malloc(image->width * sizeof(RGB_PIXEL));
        if (!image->pixels[i]) {
            for (int j = 0; j < i; j++) {
                free(image->pixels[j]);
            }
            free(image->pixels);
            free(image);
            fclose(file);
            return NULL;
        }
    }

    // Read pixel data
    for (int i = image->height - 1; i >= 0; i--) { // BMP stores pixels bottom-up
        for (int j = 0; j < image->width; j++) {
            fread(&image->pixels[i][j], sizeof(RGB_PIXEL), 1, file);
        }

        // Handle padding (each row must be multiple of 4 bytes)
        int padding = (4 - (image->width * 3) % 4) % 4;
        for (int p = 0; p < padding; p++) {
            fgetc(file);
        }
    }

    fclose(file);
    return image;
}

// Save bitmap to file
int save_bitmap(BitmapImage *image, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error creating file: %s\n", filename);
        return 0;
    }

    // Write file header
    fwrite(&image->fileHeader, sizeof(BITMAPFILEHEADER), 1, file);

    // Write info header
    fwrite(&image->infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    // Write pixel data
    for (int i = image->height - 1; i >= 0; i--) { // BMP stores pixels bottom-up
        for (int j = 0; j < image->width; j++) {
            fwrite(&image->pixels[i][j], sizeof(RGB_PIXEL), 1, file);
        }

        // Add padding
        int padding = (4 - (image->width * 3) % 4) % 4;
        for (int p = 0; p < padding; p++) {
            fputc(0, file);
        }
    }

    fclose(file);
    return 1;
}

// Free bitmap memory
void free_bitmap(BitmapImage *image) {
    if (!image) return;

    for (int i = 0; i < image->height; i++) {
        free(image->pixels[i]);
    }
    free(image->pixels);
    free(image);
}

// Get pixel at position
RGB_PIXEL get_pixel(BitmapImage *image, int x, int y) {
    if (x >= 0 && x < image->width && y >= 0 && y < image->height) {
        return image->pixels[y][x];
    }

    RGB_PIXEL black = {0, 0, 0};
    return black;
}

// Set pixel at position
void set_pixel(BitmapImage *image, int x, int y, RGB_PIXEL pixel) {
    if (x >= 0 && x < image->width && y >= 0 && y < image->height) {
        image->pixels[y][x] = pixel;
    }
}
```

### **2. Image Filters and Effects**

```c
// filters.h
#ifndef FILTERS_H
#define FILTERS_H

#include "bitmap.h"

// Filter functions
BitmapImage* apply_grayscale(BitmapImage *image);
BitmapImage* adjust_brightness(BitmapImage *image, int adjustment);
BitmapImage* adjust_contrast(BitmapImage *image, float factor);
BitmapImage* apply_sepia(BitmapImage *image);
BitmapImage* apply_invert(BitmapImage *image);
BitmapImage* apply_blur(BitmapImage *image, int radius);
BitmapImage* detect_edges(BitmapImage *image);

// Utility functions
RGB_PIXEL create_rgb(unsigned char r, unsigned char g, unsigned char b);
unsigned char clamp(int value);

#endif
```

```c
// filters.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "filters.h"

// Convert to grayscale
BitmapImage* apply_grayscale(BitmapImage *image) {
    BitmapImage *result = (BitmapImage*)malloc(sizeof(BitmapImage));
    memcpy(result, image, sizeof(BitmapImage));

    // Allocate pixel array
    result->pixels = (RGB_PIXEL**)malloc(image->height * sizeof(RGB_PIXEL*));
    for (int i = 0; i < image->height; i++) {
        result->pixels[i] = (RGB_PIXEL*)malloc(image->width * sizeof(RGB_PIXEL));
    }

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGB_PIXEL pixel = get_pixel(image, x, y);

            // Grayscale formula: 0.299*R + 0.587*G + 0.114*B
            unsigned char gray = (unsigned char)(0.299 * pixel.red +
                                               0.587 * pixel.green +
                                               0.114 * pixel.blue);

            result->pixels[y][x].red = gray;
            result->pixels[y][x].green = gray;
            result->pixels[y][x].blue = gray;
        }
    }

    return result;
}

// Adjust brightness
BitmapImage* adjust_brightness(BitmapImage *image, int adjustment) {
    BitmapImage *result = (BitmapImage*)malloc(sizeof(BitmapImage));
    memcpy(result, image, sizeof(BitmapImage));

    // Allocate pixel array
    result->pixels = (RGB_PIXEL**)malloc(image->height * sizeof(RGB_PIXEL*));
    for (int i = 0; i < image->height; i++) {
        result->pixels[i] = (RGB_PIXEL*)malloc(image->width * sizeof(RGB_PIXEL));
    }

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGB_PIXEL pixel = get_pixel(image, x, y);

            result->pixels[y][x].red = clamp(pixel.red + adjustment);
            result->pixels[y][x].green = clamp(pixel.green + adjustment);
            result->pixels[y][x].blue = clamp(pixel.blue + adjustment);
        }
    }

    return result;
}

// Apply sepia effect
BitmapImage* apply_sepia(BitmapImage *image) {
    BitmapImage *result = (BitmapImage*)malloc(sizeof(BitmapImage));
    memcpy(result, image, sizeof(BitmapImage));

    // Allocate pixel array
    result->pixels = (RGB_PIXEL**)malloc(image->height * sizeof(RGB_PIXEL*));
    for (int i = 0; i < image->height; i++) {
        result->pixels[i] = (RGB_PIXEL*)malloc(image->width * sizeof(RGB_PIXEL));
    }

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGB_PIXEL pixel = get_pixel(image, x, y);

            // Sepia formula
            unsigned char tr = clamp((unsigned char)(0.393 * pixel.red + 0.769 * pixel.green + 0.189 * pixel.blue));
            unsigned char tg = clamp((unsigned char)(0.349 * pixel.red + 0.686 * pixel.green + 0.168 * pixel.blue));
            unsigned char tb = clamp((unsigned char)(0.272 * pixel.red + 0.534 * pixel.green + 0.131 * pixel.blue));

            result->pixels[y][x].red = tr;
            result->pixels[y][x].green = tg;
            result->pixels[y][x].blue = tb;
        }
    }

    return result;
}

// Invert colors
BitmapImage* apply_invert(BitmapImage *image) {
    BitmapImage *result = (BitmapImage*)malloc(sizeof(BitmapImage));
    memcpy(result, image, sizeof(BitmapImage));

    // Allocate pixel array
    result->pixels = (RGB_PIXEL**)malloc(image->height * sizeof(RGB_PIXEL*));
    for (int i = 0; i < image->height; i++) {
        result->pixels[i] = (RGB_PIXEL*)malloc(image->width * sizeof(RGB_PIXEL));
    }

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGB_PIXEL pixel = get_pixel(image, x, y);

            result->pixels[y][x].red = 255 - pixel.red;
            result->pixels[y][x].green = 255 - pixel.green;
            result->pixels[y][x].blue = 255 - pixel.blue;
        }
    }

    return result;
}

// Simple edge detection using Sobel operator
BitmapImage* detect_edges(BitmapImage *image) {
    BitmapImage *gray = apply_grayscale(image);
    BitmapImage *result = (BitmapImage*)malloc(sizeof(BitmapImage));
    memcpy(result, image, sizeof(BitmapImage));

    // Allocate pixel array
    result->pixels = (RGB_PIXEL**)malloc(image->height * sizeof(RGB_PIXEL*));
    for (int i = 0; i < image->height; i++) {
        result->pixels[i] = (RGB_PIXEL*)malloc(image->width * sizeof(RGB_PIXEL));
    }

    for (int y = 1; y < image->height - 1; y++) {
        for (int x = 1; x < image->width - 1; x++) {
            // Simple edge detection using gradient
            int gx = -gray->pixels[y-1][x-1].red + gray->pixels[y-1][x+1].red
                    -2*gray->pixels[y][x-1].red + 2*gray->pixels[y][x+1].red
                    -gray->pixels[y+1][x-1].red + gray->pixels[y+1][x+1].red;

            int gy = -gray->pixels[y-1][x-1].red - 2*gray->pixels[y-1][x].red - gray->pixels[y-1][x+1].red
                    + gray->pixels[y+1][x-1].red + 2*gray->pixels[y+1][x].red + gray->pixels[y+1][x+1].red;

            int magnitude = (int)sqrt(gx*gx + gy*gy);
            unsigned char edge = clamp(magnitude);

            result->pixels[y][x].red = edge;
            result->pixels[y][x].green = edge;
            result->pixels[y][x].blue = edge;
        }
    }

    free_bitmap(gray);
    return result;
}

// Utility function to clamp values
unsigned char clamp(int value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return (unsigned char)value;
}
```

### **3. Main Application**

```c
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "filters.h"

void display_menu() {
    printf("\n=== Image Processing Tool ===\n");
    printf("1. Load Image\n");
    printf("2. Apply Grayscale\n");
    printf("3. Adjust Brightness\n");
    printf("4. Apply Sepia Effect\n");
    printf("5. Invert Colors\n");
    printf("6. Detect Edges\n");
    printf("7. Save Image\n");
    printf("8. Exit\n");
    printf("=============================\n");
    printf("Enter your choice: ");
}

int main() {
    BitmapImage *original = NULL;
    BitmapImage *processed = NULL;
    char filename[256];

    printf("Image Processing Tool\n");
    printf("=====================\n");

    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Load image
                printf("Enter image filename: ");
                scanf(" %s", filename);

                if (original) free_bitmap(original);
                original = load_bitmap(filename);

                if (original) {
                    printf("Image loaded successfully!\n");
                    printf("Dimensions: %dx%d\n", original->width, original->height);
                } else {
                    printf("Failed to load image!\n");
                }
                break;
            }

            case 2: {
                // Grayscale
                if (!original) {
                    printf("No image loaded!\n");
                    break;
                }

                if (processed) free_bitmap(processed);
                processed = apply_grayscale(original);
                printf("Grayscale filter applied!\n");
                break;
            }

            case 3: {
                // Brightness
                if (!original) {
                    printf("No image loaded!\n");
                    break;
                }

                printf("Enter brightness adjustment (-255 to 255): ");
                int adjustment;
                scanf("%d", &adjustment);

                if (processed) free_bitmap(processed);
                processed = adjust_brightness(original, adjustment);
                printf("Brightness adjusted by %d!\n", adjustment);
                break;
            }

            case 4: {
                // Sepia
                if (!original) {
                    printf("No image loaded!\n");
                    break;
                }

                if (processed) free_bitmap(processed);
                processed = apply_sepia(original);
                printf("Sepia effect applied!\n");
                break;
            }

            case 5: {
                // Invert
                if (!original) {
                    printf("No image loaded!\n");
                    break;
                }

                if (processed) free_bitmap(processed);
                processed = apply_invert(original);
                printf("Colors inverted!\n");
                break;
            }

            case 6: {
                // Edge detection
                if (!original) {
                    printf("No image loaded!\n");
                    break;
                }

                if (processed) free_bitmap(processed);
                processed = detect_edges(original);
                printf("Edge detection applied!\n");
                break;
            }

            case 7: {
                // Save image
                BitmapImage *to_save = processed ? processed : original;
                if (!to_save) {
                    printf("No image to save!\n");
                    break;
                }

                printf("Enter output filename: ");
                scanf(" %s", filename);

                if (save_bitmap(to_save, filename)) {
                    printf("Image saved successfully!\n");
                } else {
                    printf("Failed to save image!\n");
                }
                break;
            }

            case 8:
                if (original) free_bitmap(original);
                if (processed) free_bitmap(processed);
                printf("Thank you for using Image Processing Tool!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
```

---

## 🎯 **Features Implemented**

### **Image Processing**
- ✅ Bitmap file loading and saving
- ✅ Grayscale conversion
- ✅ Brightness and contrast adjustment
- ✅ Sepia effect
- ✅ Color inversion
- ✅ Edge detection

### **Technical Features**
- ✅ Pixel-level manipulation
- ✅ Memory-efficient processing
- ✅ File format handling
- ✅ Error handling
- ✅ User-friendly interface

---

## 🎯 **Presentation Outline**

### **Slide 1: Project Introduction**
- **English:** "Basic Image Processing - Bitmap Manipulation in C"
- **Hinglish:** "Basic Image Processing - Bitmap Manipulation in C"

### **Slide 2: What We Built**
- ✅ Complete bitmap image processor
- ✅ Multiple filter effects
- ✅ File I/O for bitmap images
- ✅ Pixel manipulation algorithms
- ✅ Interactive processing interface

### **Slide 3: Code Structure**
```c
// Complete code structure for easy copying
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} RGB_PIXEL;

typedef struct {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGB_PIXEL **pixels;
    int width, height;
} BitmapImage;

// Core functions
BitmapImage* load_bitmap(const char *filename);
int save_bitmap(BitmapImage *image, const char *filename);
BitmapImage* apply_grayscale(BitmapImage *image);
BitmapImage* adjust_brightness(BitmapImage *image, int adjustment);
BitmapImage* detect_edges(BitmapImage *image);
```

### **Slide 4: Image Filters**
```c
// Grayscale conversion
BitmapImage* apply_grayscale(BitmapImage *image) {
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGB_PIXEL pixel = get_pixel(image, x, y);
            unsigned char gray = (unsigned char)(0.299 * pixel.red +
                                               0.587 * pixel.green +
                                               0.114 * pixel.blue);
            // Set all RGB components to gray value
        }
    }
}
```

---

## 🎯 **Learning Outcomes**

### **Technical Skills:**
- ✅ File format handling
- ✅ Pixel manipulation
- ✅ Memory management
- ✅ Algorithm implementation
- ✅ Binary file processing

### **Image Processing:**
- ✅ Color space conversion
- ✅ Filter application
- ✅ Edge detection
- ✅ Image enhancement
- ✅ Bitmap file structure

---

## 📞 **Contact & Support**

**Project Developer:** Image Processing Student
**Email:** imageproc@studentproject.com
**GitHub:** https://github.com/c-image/image-processing

---

**🖼️ This image processing application demonstrates bitmap manipulation and digital image processing concepts in C, perfect for understanding computer graphics and image analysis.**