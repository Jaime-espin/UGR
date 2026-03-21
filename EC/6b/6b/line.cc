#include <benchmark/benchmark.h>
#include <numeric>

const std::size_t SIZE = 1 << 25; // 32 M

char bytes[SIZE]; // 32 MB

struct init
{
    init() { std::iota(bytes, bytes + SIZE, 0); }
} _;

static void test(benchmark::State &state)
{
    char r = 0;
    for (auto _ : state)
        for (std::size_t i = 0, line = state.range(0); i < SIZE; i += line)
        {
            leer bytes[i]; // optimízame!!!
            // benchmark::DoNotOptimize(...); // evitar optimizaciones agresivas
            // benchmark::ClobberMemory();    // forzar accesos a memoria
        }
}

BENCHMARK(test)->RangeMultiplier(2)->Range(1, 1024); // 1, 2, 4,... 1024

BENCHMARK_MAIN();
