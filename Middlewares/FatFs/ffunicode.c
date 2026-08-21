#include "ff.h"

WCHAR ff_oem2uni(WCHAR oem, WORD cp) { return (oem <= 0x7F) ? oem : '?'; }

WCHAR ff_uni2oem(DWORD uni, WORD cp) {
  return (uni <= 0x7F) ? (WCHAR)uni : '?';
}

DWORD ff_wtoupper(DWORD chr) {
  return (chr >= 'a' && chr <= 'z') ? chr - 32 : chr;
}
