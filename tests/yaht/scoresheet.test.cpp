#include <string>

#include <bandit/bandit.h>
#include "../../src/dice.h"
#include "../../src/yaht/constants.h"
#include "../../src/yaht/scoresheet.h"

using namespace bandit;
using namespace coda;
using namespace coda::yaht;
using namespace snowhouse;

go_bandit([]() {

    describe("a yaht(zee) scoresheet", []() {
        scoresheet *score;

        before_each([&]() { score = new scoresheet(); });

        after_each([&]() { delete score; });

        it("can score ones", [&]() {
            score->upper_score(1, Constants::NUM_DICE);

            Assert::That(score->upper_score(1), Equals(5));
        });

        it("has an upper score", [&]() {

            for (unsigned int i = 1; i <= die::DEFAULT_SIDES; i++) {
                auto value = 2 * i;

                score->upper_score(2, value);

                Assert::That(score->upper_score(2), Equals(value));
            }
        });

        it("gracefully handles range errors", [&]() {
            score->upper_score(1, 11111);

            score->upper_score(1234, 1234);

            Assert::That(score->upper_score(1234), Equals(0));
        });

        it("has a lower score", [&]() {
            for (int i = scoresheet::FIRST_TYPE; i < scoresheet::MAX_TYPE; i++) {
                auto value = 2 * i;

                score->lower_score(scoresheet::CHANCE, (scoresheet::value_type)value);

                Assert::That(score->lower_score(scoresheet::CHANCE), Equals(value));
            }
        });

        it("can reset", [&]() {
            score->upper_score(2, 10);

            Assert::That(score->upper_score(2), Equals(10));

            score->reset();

            Assert::That(score->upper_score(2), !Equals(10));
        });
    });


});
