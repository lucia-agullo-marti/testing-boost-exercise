#define BOOST_TEST_DYN_LINK

#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include <filesystem>
#include <string>
#include "matrixIO.hpp"

using namespace Eigen;
namespace fs = std::filesystem;

BOOST_AUTO_TEST_SUITE(MatrixIOTests)

static std::string locate_test_matrix()
{
  const fs::path candidates[] = {fs::path("data/m3.csv"), fs::path("../data/m3.csv"), fs::path("../../data/m3.csv")};

  for (const auto &p : candidates) {
    if (fs::exists(p))
      return p.string();
  }

  BOOST_FAIL("Could not locate data/m3.csv");
  return "";
}

BOOST_AUTO_TEST_CASE(OpenData)
{
  const int n = 3;

  MatrixXd expected(n, n);
  expected << 0.680375, 0.59688, -0.329554, -0.211234, 0.823295, 0.536459, 0.566198, -0.604897, -0.444451;

  const std::string filePath = locate_test_matrix();

  const MatrixXd actual = matrixIO::openData(filePath, n);

  BOOST_REQUIRE_EQUAL(actual.rows(), n);
  BOOST_REQUIRE_EQUAL(actual.cols(), n);

  BOOST_TEST((actual - expected).norm() < 1e-12);
}
BOOST_AUTO_TEST_SUITE_END()
