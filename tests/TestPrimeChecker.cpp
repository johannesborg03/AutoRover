#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this once per test-runner!

#include "../catch.hpp"
#include "../src/PrimeChecker.hpp"

TEST_CASE("Test PrimeChecker 1.") {
    PrimeChecker pc;
    REQUIRE(pc.isPrime(5));
}

// Added to test cases more to try out the pipeline more thoroughly
TEST_CASE("Test PrimeChecker 2.") {
    PrimeChecker pc;
    REQUIRE(pc.isPrime(6));
}

TEST_CASE("Test PrimeChecker 3.") {
    PrimeChecker pc;
    REQUIRE(pc.isPrime(7));
}