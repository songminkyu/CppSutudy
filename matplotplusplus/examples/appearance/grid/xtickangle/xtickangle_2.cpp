#include <matplot/matplot.h>

int main() {
    using namespace matplot;

    tiledlayout(2,1);

    auto ax1 = nexttile();
    plot(ax1,rand(6,6,0,1));

    auto ax2 = nexttile();
    plot(ax2,rand(6,6,0,1));
    xtickangle(ax2, 45);

    wait();
    return 0;
}