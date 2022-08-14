// Reference:
// https://github.com/ixty/mandibule/blob/master/code/elfload.h
// https://elixir.bootlin.com/linux/latest/source/include/linux/align.h

#define PAGE_SIZE           0x1000

#define __ALIGN_KERNEL(x, a)        __ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_KERNEL_MASK(x, mask)    (((x) + (mask)) & ~(mask))

#define ALIGN(x, a)     __ALIGN_KERNEL((x), (a))
#define ALIGN_DOWN(x, a)	__ALIGN_KERNEL((x) - ((a) - 1), (a))

#define ALIGN_PAGE(x) ALIGN((x), PAGE_SIZE)
