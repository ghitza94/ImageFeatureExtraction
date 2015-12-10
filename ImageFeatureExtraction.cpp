//
// Created by virgil on 10.12.2015.
//

# include "ImageFeatureExtraction.h"

ImageFeatureExtraction::ImageFeatureExtraction()
{
    initGlobalColorHistogram();
}

ImageFeatureExtraction::ImageFeatureExtraction(QString filePath)
{
    image.load(filePath);
    width = image.width();
    height = image.height();
    printf("Image loaded: width=%d height=%d\n", width, height);

    initGlobalColorHistogram();
}

QImage ImageFeatureExtraction::getImage()
{
    return image;
}

void ImageFeatureExtraction::setImage(QImage image)
{
    this->image = image;
}

void ImageFeatureExtraction::calculateGlobalColorHistogram()
{
    int red, green, blue;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            QRgb pixelRGB = image.pixel(x, y);
            QColor pixelColor(pixelRGB);
            red = pixelColor.red();
            green = pixelColor.green();
            blue = pixelColor.blue();

            ++globalColorHistogram[red / VALUES_PER_BIN][green / VALUES_PER_BIN][blue / VALUES_PER_BIN];
        }
    }
}

void ImageFeatureExtraction::printGlobalColorHistogram()
{
    printf("R G B PixelCount\n");
    for (int r = 0; r < NO_OF_BINS; ++r) {
        for (int g = 0; g < NO_OF_BINS; ++g) {
            for (int b = 0; b < NO_OF_BINS; ++b) {
                printf("%d %d %d %d\n", r, g, b, globalColorHistogram[r][g][b]);
            }
        }
    }
}

void ImageFeatureExtraction::initGlobalColorHistogram()
{
    for (int r = 0; r < NO_OF_BINS; ++r) {
        for (int g = 0; g < NO_OF_BINS; ++g) {
            for (int b = 0; b < NO_OF_BINS; ++b) {
                globalColorHistogram[r][g][b] = 0;
            }
        }
    }
}
