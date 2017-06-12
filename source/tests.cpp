#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

TEST_CASE("";"[]")

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
