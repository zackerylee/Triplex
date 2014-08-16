/*****************************************************************
 * 
 * This is the container for all the Triplex! routines. Because 
 * I am lazy I put all the routines in a single header file,
 * and have been putting the functions "inline" in the headers.
 * 
 **/

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
  int rateOfChange;

};

class SolidSequence : 
public AbstractSequence {
  // super basic 3 color solid, probably thorw this away
public:
  inline SolidSequence(TriangleSet* triangleSet, int num, int rateOfChangeMillis) : 
  AbstractSequence(triangleSet, num)  {
    i = 1;
    rateOfChange = rateOfChangeMillis;
  };
  inline void step() {
    switch (i % 3) {
    case 0:
      writeAll(0, 0, 255);
      i = 1;
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
    // temporarily put a delay in here before i have a seziure and die
    //  i want to write in the idea of a delay into the abstract class
    delay(rateOfChange);
  };
private:
  int i;
};

class FadeSequence : 
public AbstractSequence {
  // fade all levels between all colors at once
public:
  inline FadeSequence(TriangleSet* triangleSet, int num, int rateOfChangeMillis) : 
  AbstractSequence(triangleSet, num) {
    red = 255;
    blue = 1;
    green = 1;
    redInc = -1;
    greenInc = 1;
    blueInc = 0;
    rateOfChange = rateOfChangeMillis;
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
    delay(rateOfChange);
  };
private:
  int red;
  int blue;
  int green;
  int redInc;
  int blueInc;
  int greenInc;
};


