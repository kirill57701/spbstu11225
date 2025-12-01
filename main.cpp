#include <iostream>

struct p_t
{
  int x, y;
};

struct IDraw 
{
  virtual p_t begin() const = 0;
  virtual p_t next(p_t) const = 0;
};

size_t count(IDraw& d)
{
  size_t k = 0;
  p_t p = d.begin();

}

namespace top{
  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  struct dot: IDraw{
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t o;
    dot(int x, int y);
  };

  void make_f(IDraw** b, size_t k);
  void get_points(IDraw* b, p_t** ps, size_t &s);
  frame_t build_frame(const p_t ps, size_t s);
  char* build_carvas(frame_t f);
  void build_canvas(char* cnv, frame_t fr, const p_t* ps, size_t k, char f);
  void print_canvas(const char* cnv, frame_t fr);
}

top::dot::dot(int x, int y):
  IDraw(), o{x, y}
{}

p_t top::dot::begin() const {
  return o;
}

p_t top::dot::next(p_t) const {
  return begin();
}

struct frame_t{
  p_t left_bot;
  p_t right_top;
};

int main()
{
  using namespace top;
  IDraw* f[3] = {};
  p_t* p = nullptr;
  size_t s = 0;
  int err = 0;
  try 
  {
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(f[i], &p, s);
    }
    frame_t fr = build_frame(*p, s);
    cnv = build_canvas();
    paint_canvas(cnv, fr, p, s, '#');
    print_canvas(cnv, fr);
  }
  catch(...)
  {
    err = 1;
  }
}
