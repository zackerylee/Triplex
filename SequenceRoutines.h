class AbstractSequence {
  public:
    AbstractSequence(TriangleSet* triangleSet, int num) {
      triangles = triangleSet;
      triangleListSize = num;
    };
    virtual void step() = 0;
    inline void writeAll(int red, int green, int blue) {
      for (int x = 0; x < triangleListSize; x++) {
        triangles[x].manualWrite(red, blue, green);
      }
    }
  protected:
    TriangleSet* triangles;
    int triangleListSize;

};

class SolidSequence : public AbstractSequence {
    // super basic 3 color solid, probably thorw this away
  public:
    inline SolidSequence(TriangleSet* triangleSet, int num) : AbstractSequence(triangleSet, num)  {
      i = 1;
    };
    inline void step() {
      switch (i % 3) {
        case 0:
          writeAll(0, 0, 255);
          i = 0;
          break;
        case 1:
          writeAll(255, 0, 0);
          i++;
          break;
        case 2:
          writeAll(0, 255, 0);
          i++;
          break;
      }
    };
  private:
    int i;
};

class FadeSequence : public AbstractSequence {
    // fade all levels between all colors at once
  public:
    inline FadeSequence(TriangleSet* triangleSet, int num) : AbstractSequence(triangleSet, num) {
      red = 255;
      blue = 1;
      green = 1;
      redInc = -1;
      greenInc = 1;
      blueInc = 0;
    };
    inline void step() {
      //      for (int x = 0; x < triangleListSize; x++) {
      //        triangles[x].manualWrite(red, blue, green);
      //      }
      writeAll(red, blue, green);
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
};

