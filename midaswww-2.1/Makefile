# Makefile - modern Linux (64-bit, Open Motif / libmotif 2.3) version
#
# Requires: libmotif-dev (Xm, Mrm, uil), libxt-dev, libxmu-dev, libx11-dev
#
            LDLIBS = -lMrm -lXm -lXt -lXmu -lXext -lX11
         LDOPTIONS = 
                CC = gcc
          PORTFLAGS = -std=gnu89 -Wno-endif-labels -Wno-builtin-declaration-mismatch \
                      -Werror=implicit-function-declaration -Werror=int-conversion \
                      -Werror=incompatible-pointer-types -Wno-unused-result
            CFLAGS = -O2 -g $(PORTFLAGS) $(DEFINES) 
                RM = rm -f
               UIL = uil

include CommonMakefile

$(PGM):: $(OBJS) 
	$(RM) $@
	$(CC) -o $@ $(OBJS) $(LDOPTIONS) $(LDLIBS)

install:
	/usr/bin/install -c -s -m 755 midaswww /usr/local/bin
	/usr/bin/install -c -m 644 midas.uid   /usr/local/lib
	/usr/bin/install -c -m 644 midaswww.uid  /usr/local/lib

clean:
	rm -f *.o midaswww *.uid *.uic *.adh

