
#include "filter.h"

Filter::Filter() {

}

Filter::~Filter() {
    delete[] filter;
}

void Filter::printFilter() {
    std::cout << "\nFilter Matrix:\n";
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            std::cout << filter[j * width + i] << "\t";
        }
        std::cout << "\n";
    }
}

void Filter::convolution(Film *read, Film *write) {
    int filmWidth = read->getWidth();
    int filmHeight = read->getHeight();
    for (int row = 0; row < filmHeight; row++) {
        for (int col = 0; col < filmWidth; col++) {
            Vector3D newColor;
            for (int j = 0; j < height; j++) {
                for (int i = 0; i < width; i++) {
                    int x = col + i - width / 2;
                    int y = row + j - height / 2;

                    if (x < 0)
                        x = 0;
                    else if (x >= filmWidth)
                        x = filmWidth - 1;

                    if (y < 0)
                        y = 0;
                    else if (y >= filmHeight)
                        y = filmHeight - 1;

                    newColor += read->getPixelValue(x, y) * filter[j * width + i];
                }
            }
            write->setPixelValue(col, row, newColor);
        }
    }
}



void Filter::setMean(size_t w, size_t h) {
    if (w < 1) w = 1;
    if (h < 1) h = 1;

    width = w;
    height = h;
    filter = new double[width * height];
    double mean = 1.0 / (width * height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            filter[j * width + i] = mean;
        }
    }
    printFilter();
}

void Filter::setGauss(size_t w, size_t h, double sigma) {
    if (w < 1) w = 1;
    if (h < 1) h = 1;

    width = w;
    height = h;
    filter = new double[width * height];

    double sum = 0;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int x = i - (width / 2);
            int y = j - (height / 2);
            sum += filter[j * width + i] = (1.0 / (2.0 * M_PI * sigma * sigma) *
                                            pow(M_E, -(x * x + y * y) / 2.0 * sigma * sigma));
        }
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            filter[j * width + i] /= sum;
        }
    }
    printFilter();
}