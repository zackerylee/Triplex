class AbstractSequence {
  public:
    virtual void step() = 0;
};

class NewSequence : public AbstractSequence {
  public:
    inline NewSequence() {
      i = 0;
    };
    inline void step() {
      i++;
    };
  private:
    int i;
};

class FadeSequence : public AbstractSequence {
  public:
    inline FadeSequence() {};
    inline FadeSequence(TriangleSet* triangleSet, int num) {
      red = 255;
      blue = 1;
      green = 1;
      redInc = -1;
      greenInc = 1;
      blueInc = 0;
      triangles = triangleSet;
      triangleListSize = num;
    };
    inline void step() {
      for (int x = 0; x < triangleListSize; x++) {
        triangles[x].manualWrite(red, blue, green);
      }
      red += redInc;
      blue += blueInc;
      green += greenInc;
      if (red == 1 && green == 255) {
        redInc = 0;
        blueInc = 1;
        greenInc = -1;
      }
      else if (green == 1 && blue == 255) {
        greenInc = 0;
        blueInc = -1;
        redInc = 1;
      }
      else if (red == 255 && blue == 1) {
        redInc = -1;
        greenInc = 1;
        blueInc = 0;
      }
    };
  private:
    int red;
    int blue;
    int green;
    int redInc;
    int blueInc;
    int greenInc;
    TriangleSet* triangles;
    int triangleListSize;
};

