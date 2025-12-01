#include <iostream>

struct p_t{
  int x, y;
};

struct IDraw {
  virtual p_t begin() = 0;
  virtual p_t next(p_t) = 0;
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
}

int main()
{
  using namespace top;
}
 