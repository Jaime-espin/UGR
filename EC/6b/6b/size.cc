#include <benchmark/benchmark.h>
#include <numeric>

const std::size_t MIN = 1 << 10, MAX = 1 << 30;

char bytes[MAX]; // 1 GB

struct init
{
    init() { std::iota(bytes, bytes + MAX, 0); }
} _;

static void test(benchmark::State &state)
{
    std::size_t cache = state.range(0);
    char r = 0;
    for (auto _ : state)
        for (std::size_t i = 0; i < 1'000'000; ++i)
        {
            r ^= bytes[(i * 64) % cache]; // optimízame!!!
            // benchmark::DoNotOptimize(...); // evitar optimizaciones agresivas
            // benchmark::ClobberMemory();    // forzar accesos a memoria
        }
}

BENCHMARK(test)->RangeMultiplier(2)->Range(MIN, MAX);

BENCHMARK_MAIN();
