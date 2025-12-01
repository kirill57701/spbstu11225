#include <iostream>

struct p_t{
  int x, y;
};

struct IDraw {
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

int main()
{
  using namespace top;
}
