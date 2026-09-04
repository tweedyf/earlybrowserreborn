# MidasWWW 2.1 on 64-bit Linux with Open Motif

MidasWWW was written in 1992 for 32-bit Unix workstations (SunOS, HP-UX,
AIX, IRIX, VMS) and Motif 1.1/1.2.  This tree builds and runs on a
modern LP64 Linux with Motif 2.3 (`libmotif-dev`).

## Building

Packages (Debian/Ubuntu names):

    sudo apt-get install build-essential libmotif-dev libx11-dev libxt-dev \
                         libxmu-dev libxext-dev xfonts-75dpi xfonts-100dpi

Then:

    make            # builds uid2c, the .uid/.uic files, the .adh headers and midaswww
    ./midaswww http://example.com/          # or a file:// URL, or set $WWW_HOME
    make clean

The `uil` compiler and the Motif resource manager library come from
`libmotif-dev`.  The UIL files and app-defaults are compiled into the
binary, so nothing needs installing to run it.

The browser uses the classic X11 bitmap fonts (`-adobe-helvetica-*`,
`-adobe-times-*`, `-adobe-courier-*`).  If the X server was started before
`xfonts-75dpi`/`xfonts-100dpi` were installed (typical for XWayland) add
them to the font path for the running server:

    xset +fp /usr/share/fonts/X11/75dpi,/usr/share/fonts/X11/100dpi
    xset fp rehash

Otherwise you get `Cannot convert string "-*-helvetica-..." to type FontStruct`.

## What changed for the port

64-bit (LP64) correctness:

- `midasproto.h` (new) declares every external function with its real return
  type.  The K&R sources relied on implicit `int` declarations, which on
  LP64 truncate every returned pointer, `Pixmap`, `XmString` and
  `XtIntervalId` to 32 bits.  It is pulled in through `midasoperand.h` and
  `SGMLText.h`.  Declarations use empty parameter lists on purpose because
  the definitions are old-style and take `char`/`short`/`float` arguments.
- The interpreter's operand union (`midasoperand.h`) stores its integer
  member as `long` so that integer and pointer views of an operand are the
  same size.  `midasconvert.c` and `midasevaluate.c` were adjusted to match,
  and the `XtConvertAndStore` result buffer is now pointer sized and copied
  out according to the size Xt actually wrote.
- Several places passed an `int` length through a `char **` and read or
  wrote it as a pointer (`dump_text` in `SGMLHyper.c`, the selection dumpers
  in `SGMLFormattedText.c`/`SGMLPlainText.c`).  The storage is now `long`.
  On LP64 the old code overwrote neighbouring stack variables, under-sized
  the source dump buffer, and corrupted the heap ("Document Source" crashed).
- `SGMLNtagList` was declared with `sizeof(SGMLTagList)` (a 24 byte struct)
  while the field and every reader are pointers (`SGMLCompositeText.c`).
- The gethostbyname cache in `TCPIPConnect` allocated
  `h_length + sizeof(int)` bytes for a struct whose data member sits at a
  padded offset.
- The SGMLText object record aliases `num_popups` at the same offset as
  `core.num_popups` to work around an old Xt destroy bug.  `SGMLTextP.h`
  now uses the "DEC alpha" field ordering on any LP64 machine so the offsets
  still match (the program aborts at startup if they do not).
- Widget pointer hashing uses `unsigned long` so the index cannot go negative.
- `NULL` assigned to `XrmQuark`, `Pixmap` and `XtIntervalId` values became 0.
- `cuserid()` (gone from glibc) became `getpwuid(getuid())`, `sys_errlist`
  became `strerror`, the local BSD `getenv.c`/`setenv.c` (which shadowed
  libc) were dropped from the build, and the missing standard headers were
  added.

Motif 2.x differences:

- Motif 2 renamed the type of `XmNiconPixmap` to `DynamicPixmap` and made
  `XmNset` an `XmToggleButtonState` (`Set`) instead of a `Boolean`.  The
  Midas converter table (`midasconvert.c`) gained converters for both.
- Since Motif 2.0 an `XmMainWindow` only recognises its command and message
  windows through the `scrolledWindowChildType` constraint; otherwise it
  swallows them into the scrolling clip window.  `Midaswww_common_part.ad`
  sets the constraint on `WWWHeader` and `WWWKey`.

Modern toolchain/runtime:

- `MidasScanWidgetTree` patched `'\0'` characters into its path argument
  while walking it; most callers pass string literals, which are read-only
  on Linux.  It now works on a private copy.
- `if (cond) XtSetArg(...); n++;` in `custom.c` incremented the argument
  count even when the argument was not set, passing an uninitialised `Arg`
  to `XtCreateWidget`.  This was masked by `XmNrowColumnType` being read
  into a `char *` instead of an `unsigned char`.
- The URL parser's trailing-whitespace trim read one byte before an empty
  string.
- `file:///path` and `file://localhost/path` are treated as local files.
  In the original, `file://host/path` always meant anonymous FTP to `host`
  (that form still does for any other host); plain paths and `file:/path`
  were already local.

The Makefile builds with `-std=gnu89` and turns implicit function
declarations and int/pointer conversions into errors so that this class of
64-bit bug cannot silently return.

## Known limitations

- Only the protocols of 1993: `http` (HTTP/0.9 and 1.0), `gopher`, `ftp`,
  `file`.  No HTTPS, no HTTP/1.1 chunked encoding or virtual hosting.
- Postscript viewing needs an old-style `gs` with the Ghostview X11
  extension; the menu is greyed out without it.
- The hard-wired home page and help URLs point at hosts that no longer
  exist.  Pass a URL on the command line or set `WWW_HOME`.
- `tmpnam` is still used for temporary files (linker warning).
