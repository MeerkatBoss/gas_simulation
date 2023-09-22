#include <cstdio>
#include "app.h"

#include "math/matrix.h"
#include "math/vec.h"

int main()
{
  using namespace math;
  auto m = Matrix({
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 10}
      }) * Matrix({
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 10}
      }).getInverse();

  
  App app;
  app.run();

  return 0;
}
