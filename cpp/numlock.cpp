#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
 
bool keyState(int iKey,Display *pDisplay)
{
  int          iKeyMask = 0;
  Window       wDummy1, wDummy2;
  int          iDummy3, iDummy4, iDummy5, iDummy6;
  unsigned int iMask;
  XModifierKeymap* map = XGetModifierMapping(pDisplay);
  KeyCode keyCode = XKeysymToKeycode(pDisplay,iKey);
  if(keyCode == NoSymbol) return false;
  for(int i = 0; i < 8; ++i) {
    if( map->modifiermap[map->max_keypermod * i] == keyCode) {
      iKeyMask = 1 << i;
    }
  }
  XQueryPointer(pDisplay, DefaultRootWindow(pDisplay), &wDummy1, &wDummy2,
                &iDummy3, &iDummy4, &iDummy5, &iDummy6, &iMask );
  XFreeModifiermap(map);
  return (iMask & iKeyMask) != 0;
} 
 
int main(void)
{
  Display* pDisplay = XOpenDisplay( NULL );
  if( pDisplay == NULL ) return 1;
  printf("Scroll: %d\n",keyState(XK_Scroll_Lock,pDisplay));
  printf("Caps  : %d\n",keyState(XK_Caps_Lock,pDisplay));
  printf("Num   : %d\n",keyState(XK_Num_Lock,pDisplay));
  XCloseDisplay(pDisplay);
  return 0;
}