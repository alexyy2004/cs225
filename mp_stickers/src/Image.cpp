#include "Image.h"

Image::Image() : PNG(0, 0){
}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height){
}

void Image::lighten() {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.l += 0.1;
            if (cur.l > 1) {
                cur.l = 1;
            }
            if (cur.l < 0) {
                cur.l = 0;
            }
        }
    }
}

void Image::lighten(double amount) {
    //std::cout << cs225::PNG::width() << std::endl;
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.l += amount;
            if (cur.l > 1) {
                cur.l = 1;
            }
            if (cur.l < 0) {
                cur.l = 0;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.l -= 0.1;
            if (cur.l > 1) {
                cur.l = 1;
            }
            if (cur.l < 0) {
                cur.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.l -= amount;
            if (cur.l > 1) {
                cur.l = 1;
            }
            if (cur.l < 0) {
                cur.l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.s += 0.1;
            if (cur.s > 1) {
                cur.s = 1;
            }
            if (cur.s < 0) {
                cur.s = 0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.s += amount;
            if (cur.s > 1) {
                cur.s = 1;
            }
            if (cur.s < 0) {
                cur.s = 0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.s -= 0.1;
            if (cur.s > 1) {
                cur.s = 1;
            }
            if (cur.s < 0) {
                cur.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.s -= amount;
            if (cur.s > 1) {
                cur.s = 1;
            }
            if (cur.s < 0) {
                cur.s = 0;
            }
        }
    }
}

void Image::grayscale() {
    desaturate(1);
}

void Image::rotateColor(double degrees) {
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur.h += degrees;
            if (cur.h > 360) {
                cur.h -= 360;
            }
            if (cur.h < 0) {
                cur.h += 360;
            }
        }
    }
}
    
void Image::illinify() {
    int orange = 11;
    int blue = 216;
    for (unsigned int i = 0; i < cs225::PNG::width(); i++) {
        for (unsigned int j = 0; j < cs225::PNG::height(); j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            int diff_orange = 0;
            int diff_blue = 0;
            if (std::abs(cur.h - orange) > 180) {
                diff_orange = 360 - std::abs(cur.h - orange);
            } else {
                diff_orange = std::abs(cur.h - orange);
            }
            if (std::abs(cur.h - blue) > 180) {
                diff_blue = 360 - std::abs(cur.h - blue);
            } else {
                diff_blue = std::abs(cur.h - blue);
            }

            if (diff_orange < diff_blue) {
                cur.h = orange;
            } else {
                cur.h = blue;
            }
        }
    }
}

void Image::scale(double factor) {
    int w = cs225::PNG::width() * factor;
    int h = cs225::PNG::height() * factor;
    Image temp = *this;
    resize(w, h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            cs225::HSLAPixel& cur = getPixel(i, j);
            cur = temp.getPixel(i * (1 / factor), j * (1 / factor));
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double w_factor = (double)w / cs225::PNG::width();
    double h_factor = (double)h / cs225::PNG::height();
    if (w_factor < h_factor) {
        scale(w_factor);
    } else {
        scale(h_factor);
    }
}