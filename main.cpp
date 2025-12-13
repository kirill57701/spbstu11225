#include <iostream>
namespace topit {
  struct p_t { int x, y; };
  bool operator==(p_t, p_t);
  bool operator!=(p_t, p_t);
  struct f_t { p_t aa, bb; };

  struct IDraw {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  struct Dot: IDraw {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t d;
  };
  size_t points(const IDraw& d, p_t** pts, size_t s);

  f_t frame(const p_t* pts, size_t s);

  char * canvas(f_t fr, char fill);

  void paint(char* cnv, f_t fr, p_t p, char fill);

  void flush(std::ostream& os, const char* cnv, f_t fr);
}

void extend(topit::p_t** pts, size_t s, topit::p_t p)
{
  size_t upd_s = s + 1;
  topit::p_t* res = new topit::p_t[upd_s];
  for (size_t i = 0; i < s; ++i)
  {
    res[i] = (*pts)[i];
  }
  res[s] = p;
  delete[] * pts;
  *pts = res;
}

size_t topit::points(const IDraw& d, topit::p_t** pts, size_t s)
{
  topit::p_t p = d.begin();
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

topit::f_t topit::frame(const p_t* pts, size_t s)
{
  if (!s)
  {
    throw std::logic_error("bad_size");
  }
  int minx = pts[0].x, maxx = minx;
  int miny = pts[0].y, maxy = miny;
  for (size_t i = 1; i < s; ++i)
  {
    minx = std::min(minx, pts[i].x);
    maxx = std::max(maxx, pts[i].x);
    miny = std::min(miny, pts[i].y);
    maxy = std::max(maxy, pts[i].y);
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}

size_t rows(topit::f_t fr)
{
  return (fr.bb.y - fr.aa.y + 1);
}

size_t cols(topit::f_t fr)
{
  return (fr.bb.x - fr.aa.x + 1);
}

char * topit::canvas(f_t fr, char fill)
{
  char* cnv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i)
  {
    cnv[i] = fill;
  }
  return cnv;
}

void topit::paint(char* cns, f_t fr, p_t p, char fill)
{
  int dx = p.x - fr.aa.x;
  int dy = fr.bb.y - p.y;
  cns[dy*cols(fr) + dx] = fill;
}

void topit::flush(std::ostream& os, const char* cnv, f_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i)
  {
    for (size_t j = 0; j < cols(fr); ++j)
    {
      os << cnv[i*cols(fr) + j];
    }
    os << "\n";
  }
}

void mk_line(topit::IDraw** shps, int a, int x1, int x2, int y1, int y2, char direction) {

  if (direction == 'h'){
    int c = x1;
    for (int i = a; i < a + x2 - x1 + 1; ++i) {
      shps[i] = new topit::Dot(c++, y1);
    }
  }
  else if (direction == 'v'){
    int c = y1;
    for (int i = a; i < a + y2 - y1 + 1; ++i) {
      shps[i] = new topit::Dot(x1, c++);
    }
  }
  else {
    int c1 = x1, c2 = y1;
    for (int i = a; i < a + std::min(x2 - x1 + 1, y2 - y1 + 1); ++i) {
      shps[i] = new topit::Dot(c1++, c2++);
    }
  }
}

void mk_square(topit::IDraw** shps, int start_pos, topit::p_t ld, int width) {
  mk_line(shps, start_pos, ld.x, ld.x + width - 1, ld.y, ld.y, 'h');
  mk_line(shps, start_pos + width, ld.x, ld.x, ld.y, ld.y + width - 1, 'v');
  mk_line(shps, start_pos + width*2, ld.x, ld.x + width - 1, ld.y + width - 1, ld.y, 'h');
  mk_line(shps, start_pos + width*3, ld.x + width - 1, ld.x, ld.y, ld.y + width - 1, 'v');
}

int main() {
  using topit::IDraw;
  using topit::Dot;
  using topit::f_t;
  using topit::p_t;
  int err = 0;
  IDraw* shps[19] = {};
  p_t * pts = nullptr;
  size_t s = 0;
  try {
    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    topit::p_t q{2, 3};
    mk_square(shps, 3, q, 4);
    for (size_t i = 0; i < 19; ++i) {
      s += points(*(shps[i]), &pts, s);
    }
    f_t fr = frame(pts, s);
    char * cnv = canvas(fr, ' .');
    for (size_t i = 0; i < s; ++i) {
      paint(cnv, fr, pts[i], '#');
    }
    flush(std::cout, cnv, fr);
    delete [] cnv;
  } catch (...) {
    err = 2;
    std::cerr << "Bad drawing\n";
  }
  delete [] pts;
  delete shps[0];
  delete shps[1];
  delete shps[2];
  return err;
}
topit::Dot::Dot(p_t dd):
 IDraw(),
 d{dd}
{}
topit::Dot::Dot(int x, int y):
 IDraw(),
 d{x, y}
{}
topit::p_t topit::Dot::begin() const {
  return d;
}
topit::p_t topit::Dot::next(p_t prev) const {
  if (prev != begin()) {
    throw std::logic_error("bad impl");
  }
  return d;
}
bool topit::operator==(p_t a, p_t b) {
  return a.x == b.x && a.y == b.y;
}
bool topit::operator!=(p_t a, p_t b) {
  return !(a == b);
}
