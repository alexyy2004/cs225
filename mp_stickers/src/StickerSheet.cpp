#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    max_ = max;
    //*base_ = picture;
    base_ = picture;
    x_coordinate_ = std::vector<int>(max);
    y_coordinate_ = std::vector<int>(max);
    for (unsigned int i = 0; i < max; i++) {
        stickers_.push_back(nullptr);
        x_coordinate_[i] = 0;
        y_coordinate_[i] = 0;
    }
}
        
StickerSheet::StickerSheet(const StickerSheet& other) {
    //stickers_.clear();
    copy(other);
}

StickerSheet::~StickerSheet() {
    // stickers_.clear();
    //del();
}

void StickerSheet::copy(const StickerSheet& other) {
    // std::cout << "s2 original: " << stickers_.size() << std::endl;
    // std::cout << "s1 original: " << other.stickers_.size() << std::endl;
    base_ = Image(other.base_);
    max_ = other.max_;
    x_coordinate_ = other.x_coordinate_;
    y_coordinate_ = other.y_coordinate_;
    // stickers_.resize(max_);
    // x_coordinate_.resize(max_);
    // y_coordinate_.resize(max_);
    // std::cout << "Reached line " << __LINE__ << std::endl;
    for (unsigned int i = 0; i < stickers_.size(); i++) {
        delete stickers_[i];
        stickers_[i] = nullptr;
    }
    stickers_.clear();
    for (unsigned int i = 0; i < other.stickers_.size(); i++) {
        stickers_.push_back(other.stickers_[i]);
        // Image temp = Image(*(other.stickers_[i]));
        // stickers_[i] = &temp;
    }
    // << "s2 final: " << stickers_.size() << std::endl;
}

void StickerSheet::del() {
    // delete base_;
    // base_ = nullptr;
    // for (unsigned int i = 0; i < max_; i++) {
    //     if (stickers_[i] != nullptr) {
    //         delete stickers_[i];
    //         stickers_[i] = nullptr;
    //     }
    // }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        //del();
        //stickers_.clear();
        copy(other); 
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    max_ = max;
    stickers_.resize(max, nullptr);
    x_coordinate_.resize(max, 0);
    y_coordinate_.resize(max, 0);
}

int StickerSheet::addSticker(Image& sticker, int x, int y) {
    bool flag = false;
    int layer = 0;
    for (unsigned int i = 0; i < max_; i++) {
        if (stickers_[i] == nullptr) {
            stickers_[i] = &sticker;
            x_coordinate_[i] = x;
            y_coordinate_[i] = y;
            flag = true;
            layer = i;
            break;
        }
    }
    
    if (!flag) {
        max_ += 1;
        stickers_.push_back(&sticker);
        x_coordinate_.push_back(x);
        y_coordinate_.push_back(y);
        layer = max_ - 1;
    }
    return layer;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y) {
    if (layer >= max_) {
        return -1;
    } else {
        //delete stickers_[layer];
        stickers_[layer] = &sticker;
        x_coordinate_[layer] = x;
        y_coordinate_[layer] = y;
        return (int)layer;
    }
}

bool StickerSheet::translate (unsigned index, int x, int y) {
    if (index >= max_ || stickers_[index] == nullptr) {
        return false;
    } else {
        x_coordinate_[index] = x;
        y_coordinate_[index] = y;
        return true;
    }
}
void StickerSheet::removeSticker (unsigned index) {
    //delete stickers_[index];
    if (index >= stickers_.size() || index < 0) {
        return;
    }
    stickers_[index] = nullptr;
    x_coordinate_[index] = 0;
    y_coordinate_[index] = 0;
}

Image* StickerSheet::getSticker (unsigned index) {
    if (index >= max_ || index < 0 || stickers_[index] == nullptr) {
        return nullptr;
    } else {
        return stickers_[index];
    }
}

int StickerSheet::layers () const {
    // int count = 0;
    // for (unsigned int i = 0; i < max_; i++) {
    //     if (stickers_[i] != nullptr) {
    //         count += 1;
    //     }
    // }
    return max_;
}
Image StickerSheet::render () const {
    Image final(base_);
    for (unsigned int i = 0; i < final.width(); i++) {
        for (unsigned int j = 0; j < final.height(); j++) {
            cs225::HSLAPixel& temp = final.getPixel(i, j);
            cs225::HSLAPixel temp1 = base_.getPixel(i, j);
            temp = temp1;
        }
    }
    
    int final_height = final.height();
    int final_width = final.width();
    for (unsigned int i = 0; i < max_; i++) {
        if (stickers_[i] != nullptr) {
            Image* cur = stickers_[i];
            int cur_x = x_coordinate_[i];
            int cur_y = y_coordinate_[i];

            if (cur_x < 0 || cur_y < 0) {
                if (cur_x < 0) {
                    final_width = std::max((int)(cur->width()), (std::abs(cur_x) + final_width));
                } else {
                    final_width = std::max((int)(cur_x + cur->width()), final_width);
                }
                if (cur_y < 0) {
                    final_height = std::max((int)(cur->height()), (std::abs(cur_y) + final_height));
                } else {
                    final_height = std::max((int)(cur_y + cur->height()), final_height);
                }
                Image temp;
                int diff_height = 0;
                int diff_width = 0;
                if (cur_x < 0) {
                    diff_width = -cur_x;
                }
                if (cur_y < 0) {
                    diff_height = -cur_y;
                }
                temp.resize(final_width, final_height);
                for (unsigned int i = 0; i < final.width(); i++) {
                    for (unsigned int j = 0; j < final.height(); j++) {
                        cs225::HSLAPixel& prev = final.getPixel(i, j);
                        cs225::HSLAPixel& current = temp.getPixel(i + diff_width, j + diff_height);
                        current = prev;
                    }
                }
                final = temp;
                for (unsigned int w = 0; w < cur->width(); w++) {
                    for (unsigned int h = 0; h < cur->height(); h++) {
                        cs225::HSLAPixel& pixel = cur->getPixel(w, h);
                        int final_x = w;
                        int final_y = h;
                        if (cur_x >= 0) {
                            final_x += cur_x;
                        }
                        if (cur_y >= 0) {
                            final_y += cur_y;
                        }
                        cs225::HSLAPixel& final_pixel = final.getPixel(final_x, final_y);
                        if (pixel.a != 0) {
                            final_pixel = pixel;
                        }
                    }
                }

            } else {
                if ((int)(cur_x + cur->width()) > final_width) {
                    final_width = cur_x + cur->width();
                }
                if ((int)(cur_y + cur->height()) > final_height) {
                    final_height = cur_y + cur->height();
                }
                final.resize(final_width, final_height);
                for (unsigned int w = 0; w < cur->width(); w++) {
                    for (unsigned int h = 0; h < cur->height(); h++) {
                        cs225::HSLAPixel& pixel = cur->getPixel(w, h);
                        cs225::HSLAPixel& final_pixel = final.getPixel(w + x_coordinate_[i], h + y_coordinate_[i]);
                        if (pixel.a != 0) {
                            final_pixel = pixel;
                        }
                    }
                }
            }
        }
    }
    return final;
}