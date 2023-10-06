#ifndef RECT_HPP
#define RECT_HPP

#include <iostream>

#include "../Vec2/Vec2.hpp"

using namespace std;

class Rect
{
private:
public:
  float x, y, w, h;
  Rect();
  Rect(float x, float y, float w, float h);
  bool Contains(float x, float y);
  bool Contains(Vec2 b);

  void SetCenter(Vec2 v);
  void SetCenter(float x, float y);
  Vec2 GetCenteredVec2();
};

#endif