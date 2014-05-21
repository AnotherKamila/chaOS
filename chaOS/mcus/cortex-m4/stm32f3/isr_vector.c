/* specifies the layout of the ISR vector table */

#include "core.h"
#include "kernel/panic.h"
#include "kernel/isr.h"

extern void _estack(void); // linker-supplied address; this type because of the vector table's type
// TODO no, the above isn't nice -- the conversion should be more explicit

extern void _start(void) __attribute__((noreturn)); // defined in main.c

// create default implementations for all system interrupt handlers -- will cause a panic if the
// exception occurs unless they are overriden
ISR_UNEXPECTED( INT_NMI        )
ISR_UNEXPECTED( INT_HARDFAULT  )
ISR_UNEXPECTED( INT_MEMMANAGE  )
ISR_UNEXPECTED( INT_BUSFAULT   )
ISR_UNEXPECTED( INT_USAGEFAULT )
ISR_UNEXPECTED( INT_SVCALL     )
ISR_UNEXPECTED( INT_PENDSV     )
ISR_UNEXPECTED( INT_SYSTICK    )

// declare hardware interrupt handlers (note: the CPU will hardfault when an interrupt without an
// implementation occurs)
// TODO either remove the need to do this explicitly, or generate with a preprocessor for loop
ISR_NULL( 16)
ISR_NULL( 17)
ISR_NULL( 18)
ISR_NULL( 19)
ISR_NULL( 20)
ISR_NULL( 21)
ISR_NULL( 22)
ISR_NULL( 23)
ISR_NULL( 24)
ISR_NULL( 25)
ISR_NULL( 26)
ISR_NULL( 27)
ISR_NULL( 28)
ISR_NULL( 29)
ISR_NULL( 30)
ISR_NULL( 31)
ISR_NULL( 32)
ISR_NULL( 33)
ISR_NULL( 34)
ISR_NULL( 35)
ISR_NULL( 36)
ISR_NULL( 37)
ISR_NULL( 38)
ISR_NULL( 39)
ISR_NULL( 40)
ISR_NULL( 41)
ISR_NULL( 42)
ISR_NULL( 43)
ISR_NULL( 44)
ISR_NULL( 45)
ISR_NULL( 46)
ISR_NULL( 47)
ISR_NULL( 48)
ISR_NULL( 49)
ISR_NULL( 50)
ISR_NULL( 51)
ISR_NULL( 52)
ISR_NULL( 53)
ISR_NULL( 54)
ISR_NULL( 55)
ISR_NULL( 56)
ISR_NULL( 57)
ISR_NULL( 58)
ISR_NULL( 59)
ISR_NULL( 60)
ISR_NULL( 61)
ISR_NULL( 62)
ISR_NULL( 63)
ISR_NULL( 64)
ISR_NULL( 65)
ISR_NULL( 66)
ISR_NULL( 67)
ISR_NULL( 68)
ISR_NULL( 69)
ISR_NULL( 70)
ISR_NULL( 71)
ISR_NULL( 72)
ISR_NULL( 73)
ISR_NULL( 74)
ISR_NULL( 75)
ISR_NULL( 76)
ISR_NULL( 77)
ISR_NULL( 78)
ISR_NULL( 79)
ISR_NULL( 80)
ISR_NULL( 81)
ISR_NULL( 82)
ISR_NULL( 83)
ISR_NULL( 84)
ISR_NULL( 85)
ISR_NULL( 86)
ISR_NULL( 87)
ISR_NULL( 88)
ISR_NULL( 89)
ISR_NULL( 90)
ISR_NULL( 91)
ISR_NULL( 92)
ISR_NULL( 93)
ISR_NULL( 94)
ISR_NULL( 95)
ISR_NULL( 96)
ISR_NULL( 97)
ISR_NULL( 98)
ISR_NULL( 99)
ISR_NULL(100)
ISR_NULL(101)
ISR_NULL(102)
ISR_NULL(103)
ISR_NULL(104)
ISR_NULL(105)
ISR_NULL(106)
ISR_NULL(107)
ISR_NULL(108)
ISR_NULL(109)
ISR_NULL(110)
ISR_NULL(111)
ISR_NULL(112)
ISR_NULL(113)
ISR_NULL(114)
ISR_NULL(115)
ISR_NULL(116)
ISR_NULL(117)
ISR_NULL(118)
ISR_NULL(119)
ISR_NULL(120)
ISR_NULL(121)
ISR_NULL(122)
ISR_NULL(123)
ISR_NULL(124)
ISR_NULL(125)
ISR_NULL(126)
ISR_NULL(127)
ISR_NULL(128)
ISR_NULL(129)
ISR_NULL(130)
ISR_NULL(131)
ISR_NULL(132)
ISR_NULL(133)
ISR_NULL(134)
ISR_NULL(135)
ISR_NULL(136)
ISR_NULL(137)
ISR_NULL(138)
ISR_NULL(139)
ISR_NULL(140)
ISR_NULL(141)
ISR_NULL(142)
ISR_NULL(143)
ISR_NULL(144)
ISR_NULL(145)
ISR_NULL(146)
ISR_NULL(147)
ISR_NULL(148)
ISR_NULL(149)
ISR_NULL(150)
ISR_NULL(151)
ISR_NULL(152)
ISR_NULL(153)
ISR_NULL(154)
ISR_NULL(155)
ISR_NULL(156)
ISR_NULL(157)
ISR_NULL(158)
ISR_NULL(159)
ISR_NULL(160)
ISR_NULL(161)
ISR_NULL(162)
ISR_NULL(163)
ISR_NULL(164)
ISR_NULL(165)
ISR_NULL(166)
ISR_NULL(167)
ISR_NULL(168)
ISR_NULL(169)
ISR_NULL(170)
ISR_NULL(171)
ISR_NULL(172)
ISR_NULL(173)
ISR_NULL(174)
ISR_NULL(175)
ISR_NULL(176)
ISR_NULL(177)
ISR_NULL(178)
ISR_NULL(179)
ISR_NULL(180)
ISR_NULL(181)
ISR_NULL(182)
ISR_NULL(183)
ISR_NULL(184)
ISR_NULL(185)
ISR_NULL(186)
ISR_NULL(187)
ISR_NULL(188)
ISR_NULL(189)
ISR_NULL(190)
ISR_NULL(191)
ISR_NULL(192)
ISR_NULL(193)
ISR_NULL(194)
ISR_NULL(195)
ISR_NULL(196)
ISR_NULL(197)
ISR_NULL(198)
ISR_NULL(199)
ISR_NULL(200)
ISR_NULL(201)
ISR_NULL(202)
ISR_NULL(203)
ISR_NULL(204)
ISR_NULL(205)
ISR_NULL(206)
ISR_NULL(207)
ISR_NULL(208)
ISR_NULL(209)
ISR_NULL(210)
ISR_NULL(211)
ISR_NULL(212)
ISR_NULL(213)
ISR_NULL(214)
ISR_NULL(215)
ISR_NULL(216)
ISR_NULL(217)
ISR_NULL(218)
ISR_NULL(219)
ISR_NULL(220)
ISR_NULL(221)
ISR_NULL(222)
ISR_NULL(223)
ISR_NULL(224)
ISR_NULL(225)
ISR_NULL(226)
ISR_NULL(227)
ISR_NULL(228)
ISR_NULL(229)
ISR_NULL(230)
ISR_NULL(231)
ISR_NULL(232)
ISR_NULL(233)
ISR_NULL(234)
ISR_NULL(235)
ISR_NULL(236)
ISR_NULL(237)
ISR_NULL(238)
ISR_NULL(239)
ISR_NULL(240)
ISR_NULL(241)
ISR_NULL(242)
ISR_NULL(243)
ISR_NULL(244)
ISR_NULL(245)
ISR_NULL(246)
ISR_NULL(247)
ISR_NULL(248)
ISR_NULL(249)
ISR_NULL(250)
ISR_NULL(251)
ISR_NULL(252)
ISR_NULL(253)
ISR_NULL(254)
ISR_NULL(255)

// the linker script puts .isr_vector at 0x0
void (*isr_vector[])(void) __attribute__((section(".isr_vector"))) = {
    _estack ,// stack top
    _start  ,// entry point
    // system interrupts
    INTFN(INT_NMI),
    INTFN(INT_HARDFAULT),
    INTFN(INT_MEMMANAGE),
    INTFN(INT_BUSFAULT),
    INTFN(INT_USAGEFAULT),
    NULL,
    NULL,
    NULL,
    NULL,
    INTFN(INT_SVCALL),
    NULL,
    NULL,
    INTFN(INT_PENDSV),
    INTFN(INT_SYSTICK),
    // hardware interrupts
    // TODO maybe the following should be generated by a preprocessor for loop if I find the courage
    INTFN( 16),
    INTFN( 17),
    INTFN( 18),
    INTFN( 19),
    INTFN( 20),
    INTFN( 21),
    INTFN( 22),
    INTFN( 23),
    INTFN( 24),
    INTFN( 25),
    INTFN( 26),
    INTFN( 27),
    INTFN( 28),
    INTFN( 29),
    INTFN( 30),
    INTFN( 31),
    INTFN( 32),
    INTFN( 33),
    INTFN( 34),
    INTFN( 35),
    INTFN( 36),
    INTFN( 37),
    INTFN( 38),
    INTFN( 39),
    INTFN( 40),
    INTFN( 41),
    INTFN( 42),
    INTFN( 43),
    INTFN( 44),
    INTFN( 45),
    INTFN( 46),
    INTFN( 47),
    INTFN( 48),
    INTFN( 49),
    INTFN( 50),
    INTFN( 51),
    INTFN( 52),
    INTFN( 53),
    INTFN( 54),
    INTFN( 55),
    INTFN( 56),
    INTFN( 57),
    INTFN( 58),
    INTFN( 59),
    INTFN( 60),
    INTFN( 61),
    INTFN( 62),
    INTFN( 63),
    INTFN( 64),
    INTFN( 65),
    INTFN( 66),
    INTFN( 67),
    INTFN( 68),
    INTFN( 69),
    INTFN( 70),
    INTFN( 71),
    INTFN( 72),
    INTFN( 73),
    INTFN( 74),
    INTFN( 75),
    INTFN( 76),
    INTFN( 77),
    INTFN( 78),
    INTFN( 79),
    INTFN( 80),
    INTFN( 81),
    INTFN( 82),
    INTFN( 83),
    INTFN( 84),
    INTFN( 85),
    INTFN( 86),
    INTFN( 87),
    INTFN( 88),
    INTFN( 89),
    INTFN( 90),
    INTFN( 91),
    INTFN( 92),
    INTFN( 93),
    INTFN( 94),
    INTFN( 95),
    INTFN( 96),
    INTFN( 97),
    INTFN( 98),
    INTFN( 99),
    INTFN(100),
    INTFN(101),
    INTFN(102),
    INTFN(103),
    INTFN(104),
    INTFN(105),
    INTFN(106),
    INTFN(107),
    INTFN(108),
    INTFN(109),
    INTFN(110),
    INTFN(111),
    INTFN(112),
    INTFN(113),
    INTFN(114),
    INTFN(115),
    INTFN(116),
    INTFN(117),
    INTFN(118),
    INTFN(119),
    INTFN(120),
    INTFN(121),
    INTFN(122),
    INTFN(123),
    INTFN(124),
    INTFN(125),
    INTFN(126),
    INTFN(127),
    INTFN(128),
    INTFN(129),
    INTFN(130),
    INTFN(131),
    INTFN(132),
    INTFN(133),
    INTFN(134),
    INTFN(135),
    INTFN(136),
    INTFN(137),
    INTFN(138),
    INTFN(139),
    INTFN(140),
    INTFN(141),
    INTFN(142),
    INTFN(143),
    INTFN(144),
    INTFN(145),
    INTFN(146),
    INTFN(147),
    INTFN(148),
    INTFN(149),
    INTFN(150),
    INTFN(151),
    INTFN(152),
    INTFN(153),
    INTFN(154),
    INTFN(155),
    INTFN(156),
    INTFN(157),
    INTFN(158),
    INTFN(159),
    INTFN(160),
    INTFN(161),
    INTFN(162),
    INTFN(163),
    INTFN(164),
    INTFN(165),
    INTFN(166),
    INTFN(167),
    INTFN(168),
    INTFN(169),
    INTFN(170),
    INTFN(171),
    INTFN(172),
    INTFN(173),
    INTFN(174),
    INTFN(175),
    INTFN(176),
    INTFN(177),
    INTFN(178),
    INTFN(179),
    INTFN(180),
    INTFN(181),
    INTFN(182),
    INTFN(183),
    INTFN(184),
    INTFN(185),
    INTFN(186),
    INTFN(187),
    INTFN(188),
    INTFN(189),
    INTFN(190),
    INTFN(191),
    INTFN(192),
    INTFN(193),
    INTFN(194),
    INTFN(195),
    INTFN(196),
    INTFN(197),
    INTFN(198),
    INTFN(199),
    INTFN(200),
    INTFN(201),
    INTFN(202),
    INTFN(203),
    INTFN(204),
    INTFN(205),
    INTFN(206),
    INTFN(207),
    INTFN(208),
    INTFN(209),
    INTFN(210),
    INTFN(211),
    INTFN(212),
    INTFN(213),
    INTFN(214),
    INTFN(215),
    INTFN(216),
    INTFN(217),
    INTFN(218),
    INTFN(219),
    INTFN(220),
    INTFN(221),
    INTFN(222),
    INTFN(223),
    INTFN(224),
    INTFN(225),
    INTFN(226),
    INTFN(227),
    INTFN(228),
    INTFN(229),
    INTFN(230),
    INTFN(231),
    INTFN(232),
    INTFN(233),
    INTFN(234),
    INTFN(235),
    INTFN(236),
    INTFN(237),
    INTFN(238),
    INTFN(239),
    INTFN(240),
    INTFN(241),
    INTFN(242),
    INTFN(243),
    INTFN(244),
    INTFN(245),
    INTFN(246),
    INTFN(247),
    INTFN(248),
    INTFN(249),
    INTFN(250),
    INTFN(251),
    INTFN(252),
    INTFN(253),
    INTFN(254),
    INTFN(255),
};
