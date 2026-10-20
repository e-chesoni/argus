#pragma once

namespace Drive
{
    void setup();

    void move(float x, float y);
    
    void forward();
    void backward();

    void strafeLeft();
    void strafeRight();

    void rotateLeft();
    void rotateRight();

    void diagonalFrontLeft();
    void diagonalFrontRight();
    void diagonalBackLeft();
    void diagonalBackRight();

    void stop();
}