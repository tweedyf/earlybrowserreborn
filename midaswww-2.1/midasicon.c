/*
 * midasicon.c -- publish the shell's icon as _NET_WM_ICON.
 *
 * Midas sets the shell's XmNiconPixmap (a 1-bit bitmap compiled from the UIL
 * file), which is all a 1993 window manager needed.  Modern desktops (GNOME
 * Shell, KDE, XFCE, ...) ignore the ICCCM WM_HINTS bitmap and take the window
 * icon from the EWMH _NET_WM_ICON property instead: a list of ARGB images.
 * This converts the existing bitmap into that form, at several pixel-doubled
 * sizes on a light rounded tile so the line art stays visible on dark docks.
 * It is an X11 property, so it works the same under XWayland.
 */
#include "midasproto.h"
#include <X11/Xatom.h>
#include <X11/Shell.h>

#define ICON_BG   0xffe6e6e6UL   /* opaque light grey tile */
#define ICON_FG   0xff000000UL   /* opaque black line art  */

void MidasSetNetWmIcon(shell)
Widget shell;
{
    Display *dpy = XtDisplay(shell);
    Pixmap pixmap = None;
    Arg args[1];
    Window root;
    int x, y;
    unsigned int w, h, bw, depth;
    XImage *img;
    static const int scales[] = { 1, 2, 3, 4 };
    unsigned long total = 0, *data, *p;
    unsigned long bgpixel = 0;
    int i, j, s;

    if (!XtIsRealized(shell) || !XtIsShell(shell)) return;

    XtSetArg(args[0], XtNiconPixmap, &pixmap);
    XtGetValues(shell, args, 1);
    if (pixmap == None || pixmap == XtUnspecifiedPixmap) return;

    if (!XGetGeometry(dpy, pixmap, &root, &x, &y, &w, &h, &bw, &depth)) return;
    if (w == 0 || h == 0 || w > 256 || h > 256) return;

    img = XGetImage(dpy, pixmap, 0, 0, w, h, AllPlanes, ZPixmap);
    if (img == NULL) return;

    /* Whatever the depth, the blank area of a line-art icon is by far the
       most common pixel value.  Take that as the background and paint every
       other value as foreground. */
    {
        unsigned long v[8]; unsigned long c[8]; int nv = 0, best = 0;
        for (j = 0; j < h; j++)
          for (i = 0; i < w; i++)
            {
              unsigned long pix = XGetPixel(img, i, j);
              int k;
              for (k = 0; k < nv; k++) if (v[k] == pix) break;
              if (k == nv) { if (nv == 8) continue; v[nv] = pix; c[nv] = 0; nv++; }
              c[k]++;
            }
        for (i = 1; i < nv; i++) if (c[i] > c[best]) best = i;
        bgpixel = nv ? v[best] : 0;
        if (getenv("MIDAS_TRACE"))
          fprintf(stderr, "midas icon: %ux%u depth %u, %d pixel values, background %lu\n", w, h, depth, nv, bgpixel);
    }

    for (s = 0; s < XtNumber(scales); s++)
        total += 2 + (unsigned long) w * scales[s] * (unsigned long) h * scales[s];

    data = (unsigned long *) XtMalloc(total * sizeof(unsigned long));
    p = data;

    for (s = 0; s < XtNumber(scales); s++)
      {
        int k = scales[s];
        unsigned long W = w * k, H = h * k;
        unsigned long r = (W < H ? W : H) / 8;      /* corner radius */

        *p++ = W;
        *p++ = H;
        for (j = 0; j < H; j++)
          for (i = 0; i < W; i++)
            {
              unsigned long pix = XGetPixel(img, i / k, j / k);
              Boolean drawn = (pix != bgpixel);
              unsigned long argb = drawn ? ICON_FG : ICON_BG;

              /* transparent outside a rounded rectangle */
              if (r > 1)
                {
                  long cx = (i < (long) r) ? (long) r - i - 1 : (i >= (long)(W - r)) ? i - (long)(W - r) : -1;
                  long cy = (j < (long) r) ? (long) r - j - 1 : (j >= (long)(H - r)) ? j - (long)(H - r) : -1;
                  if (cx >= 0 && cy >= 0 && cx * cx + cy * cy > (long)(r * r)) argb = 0;
                }
              *p++ = argb;
            }
      }

    XChangeProperty(dpy, XtWindow(shell),
                    XInternAtom(dpy, "_NET_WM_ICON", False), XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char *) data, (int) total);
    XtFree((char *) data);
    XDestroyImage(img);
}
