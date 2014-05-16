MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 40K
}

/* TODO: Also use 8K of CCM RAM! */

INCLUDE "chaos.ld"
