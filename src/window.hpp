#ifndef GLSANDBOX_WINDOW_HPP
#define GLSANDBOX_WINDOW_HPP

namespace glsb {

class WindowState {
public:
    int mWidth = 800;
    int mHeight = 800;

    void setWindowState(int pWidth, int pHeight) {
        mWidth = pWidth;
        mHeight = pHeight;
    }

    [[nodiscard]] int getWidth() const {
        return mWidth;
    }

    [[nodiscard]] int getHeight() const {
        return  mHeight;
    }
};

} //glsb

#endif //GLSANDBOX_WINDOW_HPP
