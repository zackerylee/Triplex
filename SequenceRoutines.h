/*****************************************************************
 * 
 * This is the container for all the Triplex! routines. Because 
 * I am lazy I put all the routines in a single header file,
 * and have been putting the functions "inline" in the headers.
 * 
 **/

/**
 * A color object that knows how to increment, decrement, and wait
 *  the most basic color pattern we use involves going from 0 -> 255, then 255 -> 0, then sitting at 0 for a cycle. This
 *  allows us to cycle from Red -> Green -> Blue, with the value 0-255 each being a Color object
 *  does that make sense? no? hmmmm
 **/
class Color {
public:
  inline Color(int start = 0) {
    value = start;
  }
  inline void increment(int incrementBy = 1) {
    value += incrementBy;
    if (value >= (255 * 3)) {
      value = 0;
    }
  }
  inline int write(int offset = 0) {
    int newVal = value + offset;
    if (newVal > (255 * 3)) {
      newVal -= (255 * 3);
    }
    if (newVal <= 255) {
      return newVal;
    }
    else if (newVal <= (255 * 2)) {
      return (255 - (newVal - 255));
    }
    else {
      return 0;
    }
  }
private:
  int value;
};

/**
 * AbstractSequence - the abstract sequence class
 *  any Sequence class that extends this class gets a few things for free
 *  - timed control of when to actually "step" based on the specified rate of change
 *  - some helper functions
 *  - tracking of color state
 **/
class AbstractSequence {
public:
  AbstractSequence(TriangleSet* triangleSet, int num) {
    triangles = triangleSet;
    triangleListSize = num;
  };
  inline void checkedStep() {
    if (rateOfChange == 0 || (millis() - lastChange > rateOfChange)) {
      lastChange = millis();
      step();
    }
  }
  virtual void step() = 0;
  inline void writeAll(int red, int green, int blue) {
    for (int x = 0; x < triangleListSize; x++) {
      triangles[x].manualWrite(red, green, blue);
    }
  }
protected:
  TriangleSet* triangles;
  int triangleListSize;
  int rateOfChange;
  unsigned long lastChange;
  Color redColor;
  Color greenColor;
  Color blueColor;

};

class SolidSequence : 
public AbstractSequence {
  // super basic 3 color solid, probably thorw this away
public:
  inline SolidSequence(TriangleSet* triangleSet, int num, int rateOfChangeMillis) : 
  AbstractSequence(triangleSet, num)  {
    rateOfChange = rateOfChangeMillis;
    redColor = Color(0);
    greenColor = Color(255);
    blueColor = Color(255 * 2); 

  };
  inline void step() {
    writeAll(redColor.write(), greenColor.write(), blueColor.write());
    redColor.increment(255);
    greenColor.increment(255);
    blueColor.increment(255);
  };
private:
};

class FadeSequence : 
public AbstractSequence {
  // fade all levels between all colors at once
public:
  inline FadeSequence(TriangleSet* triangleSet, int num, int rateOfChangeMillis) : 
  AbstractSequence(triangleSet, num) {
    redColor = Color(0);
    greenColor = Color(255);
    blueColor = Color(255 * 2); 
    rateOfChange = rateOfChangeMillis;
  };
  inline void step() {
    writeAll(redColor.write(), greenColor.write(), blueColor.write());
    redColor.increment();
    greenColor.increment();
    blueColor.increment();
  };
private:
};


class MovingFadeSequence : 
public AbstractSequence {
public:
  inline MovingFadeSequence(TriangleSet* triangleSet, int num, int rateOfChangeMillis, int colorDistance) : 
  AbstractSequence(triangleSet, num) {
    rateOfChange = rateOfChangeMillis; 
    redColor = Color(0);
    greenColor = Color(255);
    blueColor = Color(255 * 2); 
    distance = colorDistance;
  }
  inline void step() {
    int offset = 0;
    for (int x = 0; x < triangleListSize; x++) {
      triangles[x].manualWrite(redColor.write(offset), greenColor.write(offset), blueColor.write(offset));
      offset += distance;
    }
    redColor.increment();
    greenColor.increment();
    blueColor.increment();
  }

private: 
  int distance;
};

class SolidRiseSequence : 
public AbstractSequence {
public:
  inline SolidRiseSequence(TriangleSet* triangleSet, int num, int rateOfChangeMillis) : 
  AbstractSequence(triangleSet, num) {
    rateOfChange = rateOfChangeMillis;
    whiteLevel = -1; // start with no string lit
    dir = 1;         // go up
  }
  inline void step() {
    for (int x = 0; x < triangleListSize; x++) {
      if (x > whiteLevel) {
        triangles[x].manualWrite(0, 0, 200);
      }
      else if (x == whiteLevel) {
        triangles[x].manualWrite(66, 66, 66);
      }
      else {
        triangles[x].manualWrite(100, 0, 100);
      }
    }
    whiteLevel = whiteLevel + dir;
    if (whiteLevel >= triangleListSize) {
      dir = -1;
      //whiteLevel = -1;
    }
    else if (whiteLevel == -1) {
      dir = 1;
    }
  }
private:
  int whiteLevel;
  int dir;
};

class CycleRiseSequence : 
public AbstractSequence {
public:
  inline CycleRiseSequence(TriangleSet* triangleSet, int num, int rateOfChangeMillis) : 
  AbstractSequence(triangleSet, num) {
    rateOfChange = rateOfChangeMillis;
    whiteLevel = -1; // start with no string lit
    dir = 1;         // go up
    redColor = Color(0);
    greenColor = Color(255);
    blueColor = Color(255 * 2); 
    secondRedColor = Color(255 * 2);
    secondGreenColor = Color(0);
    secondBlueColor = Color(255); 


  }
  inline void step() {
    for (int x = 0; x < triangleListSize; x++) {
      if (x > whiteLevel) {
        triangles[x].manualWrite(redColor.write(), greenColor.write(), blueColor.write());
      }
      else if (x == whiteLevel) {
        triangles[x].manualWrite(66, 66, 66);
      }
      else {
        triangles[x].manualWrite(secondRedColor.write(), secondGreenColor.write(), secondBlueColor.write(distance));
      }
    }
    whiteLevel = whiteLevel + dir;
    if (whiteLevel >= triangleListSize) {
      dir = -1;
      redColor.increment(255);
      greenColor.increment(255);
      blueColor.increment(255);
    }
    else if (whiteLevel == -1) {
      dir = 1;
      secondRedColor.increment(255);
      secondGreenColor.increment(255);
      secondBlueColor.increment(255);
    }
  }
private:
  int whiteLevel;
  int dir;
  int distance;
  Color secondRedColor;
  Color secondGreenColor;
  Color secondBlueColor;
};







