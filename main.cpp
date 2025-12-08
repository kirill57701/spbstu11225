#include <iostream>

struct p_t
{
  int x, y;
};

struct frame_t{
  p_t left_bot;
  p_t right_top;
};

struct IDraw
{
  virtual p_t begin() const = 0;
  virtual p_t next(p_t) const = 0;
};

struct vertical_segment
{
  p_t u, d;
};

struct horizontal_segment
{
  p_t l, r;
};

struct diagonal
{
  p_t ld, ru;
};

struct trapeze
{
  p_t lu, ld, ru, rd;
};

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

void top::make_f(IDraw** b, size_t k)
{
  b[0] = new dot(0, 0);
  b[1] = new dot(9, 11);
  b[2] = new dot(-11, -7);
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

/**/
void extend(top::p_t** pts, size_t s, p_t p)
{
  size_t upd_s = s + 1;
  top::p_t* res = new p_t[upd_s];
  for (size_t i = 0; i < s; ++i)
  {
    res[i] = (*pts)[i];
  }
  p_t p = d.begin();
  res[s] = p;
  delete[] * pts;
  *pts = res;
}

size_t top::points(const IDraw& d, p_t** pts, size_t s)
{
  p_t = d.begin();
  extend(pts, s, p);
  size_t delta = 1;
  while (d.next(p) != d.begin())
  {
    p = d.next(p);
    extend(pts, s + delta, p);
    ++delta;
  }
  return delta;
}

int main()
{
  using namespace top;
  IDraw* f[3] = {};
  p_t* p = nullptr;
  size_t s = 0;
  int err = 0;
  char* cnv = nullptr;
  try
  {
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(f[i], &p, s);
    }
    frame_t fr = build_frame(*p, s);
  }
  catch(...)
  {
    err = 1;
  }
  delete f[0];
  delete f[1];
  delete f[2];
  delete [] p;
  delete [] cnv;
  return err;
}
