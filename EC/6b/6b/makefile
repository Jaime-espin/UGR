###############################################################################
# makefile
###############################################################################

SHELL := bash
.ONESHELL:

###############################################################################

ATT = $(EXE:=.att)
SRC = $(wildcard *.cc)
EXE = $(basename $(SRC))
DAT = $(EXE:=.dat)
PNG = $(EXE:=.png) $(EXE:=-log.png)
SVG = $(EXE:=.svg) $(EXE:=-log.svg)

###############################################################################

CXXFLAGS = -fanalyzer -O3 -std=c++23 -Wall -Werror
LDLIBS = -lbenchmark

PLT = set grid; \
	  set key autotitle columnhead; \
      set xlabel 'size (B)'; \
	  set logscale x 2; \
	  set output '$@'; \
	  set terminal svg enhanced background rgb 'white'; \
	  set xtics rotate (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1K' 1024, '2K' 2048, '4K' 4096, '8K' 8192, '16K' 16384, '32K' 32768, '64K' 65526, '128K' 131072, '256K' 262144, '512K' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864, '128M' 134217728, '256M' 268435455, '512M' 536870912, '1G' 1073741823); \
      set ylabel 'time ($(shell tail -1 $< | tr -s ' ' | cut -d' ' -f3))'; \
	  unset key; \
      plot '<(sed \"s/.*\///\" $<)' u 1:(\$$4) w lp lc 1 pt 7

###############################################################################

all: svg

att: $(ATT)

clean:
	-rm -fv $(ATT) $(DAT) $(EXE) $(PNG) $(SVG) core* *~

dat: $(DAT)

exe: $(EXE)

info: /sys/devices/system/cpu/cpu0/cache
	@printf "%51s\n" | tr ' ' '-'
	printf "%5s %12s %8s %8s %9s %4s\n" level type line size instance ways
	printf "%51s\n" | tr ' ' '-'
	for ((i=0; i<$$(ls $< | grep "index[[:digit:]]\+" | wc -l); ++i)); do
		j=$$((i + 1))
		printf "%5s %12s %8s %8s %9s %4s\n" $$(cat $</index$$i/{level,type,coherency_line_size,size}) $$(lscpu | grep -o ". \(instancia\|instance\)" | cut -d' ' -f 1 | sed -n $$((i + 1))p) $$(cat $</index$$i/ways_of_associativity)
	done

png : $(PNG)

svg: $(SVG)

tools:
	@os=$$(sed -n 's/^ID=\(.*\)$$/\1/p' /etc/os-release)
	echo "tu distribución de linux es $$os"
	case $$os in
		fedora) echo sudo dnf -y install gcc-c++ gnuplot google-benchmark-devel;;
		ubuntu) echo sudo apt -y install g++ gnuplot libbenchmark-dev;;
		*) echo "debes instalar g++, gnuplot y perf en $$os!";;
	esac

###############################################################################

%.att: %
	objdump -CdS $< > $@

%.dat: %
	./$< --benchmark_counters_tabular=true | tee $@

%.png: %.dat makefile
	gnuplot <<< "$(PLT:svg=pngcairo)"

%-log.png: %.dat makefile
	gnuplot <<< "set logscale y 10; $(PLT:svg=pngcairo)"

%.svg: %.dat makefile
	gnuplot <<< "$(PLT)"

%-log.svg: %.dat makefile
	gnuplot <<< "set logscale y 10; $(PLT)"

###############################################################################

.PHONY: all att clean exe info png svg tools
.PRECIOUS: $(DAT)
.NOEXPORT:

###############################################################################
