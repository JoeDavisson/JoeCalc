# data file for the Fltk User Interface Designer (fluid)
version 1.0302 
header_name {.h} 
code_name {.cxx}
Function {make_window()} {open
} {
  Fl_Window {} {
    label JoeCalc open
    xywh {453 305 492 372} type Double align 80 visible
  } {
    Fl_Box {} {
      xywh {8 102 176 172} box ENGRAVED_FRAME align 6
    }
    Fl_Box {} {
      xywh {192 102 64 172} box ENGRAVED_FRAME align 6
    }
    Fl_Box {} {
      xywh {264 102 120 172} box ENGRAVED_FRAME align 6
    }
    Fl_Box {} {
      xywh {8 280 176 88} box ENGRAVED_FRAME align 6
    }
    Fl_Box {} {
      xywh {392 102 96 172} box ENGRAVED_FRAME align 6
    }
    Fl_Box {} {
      xywh {192 280 296 88} box ENGRAVED_FRAME align 6
    }
    Fl_Button {} {
      label 7
      xywh {16 112 48 32}
    }
    Fl_Button {} {
      label 8
      xywh {72 112 48 32}
    }
    Fl_Button {} {
      label 9
      xywh {128 112 48 32}
    }
    Fl_Button {} {
      label 4
      xywh {16 152 48 32}
    }
    Fl_Button {} {
      label 5
      xywh {72 152 48 32}
    }
    Fl_Button {} {
      label 6
      xywh {128 152 48 32}
    }
    Fl_Button {} {
      label 1
      xywh {16 192 48 32}
    }
    Fl_Button {} {
      label 2
      xywh {72 192 48 32}
    }
    Fl_Button {} {
      label 3
      xywh {128 192 48 32}
    }
    Fl_Button {} {
      label 0
      xywh {16 232 48 32}
    }
    Fl_Output {} {
      xywh {8 32 376 32} textsize 18
    }
    Fl_Button {} {
      label {%}
      xywh {328 192 48 32}
    }
    Fl_Button {} {
      label {^}
      xywh {272 192 48 32}
    }
    Fl_Button {} {
      label {&}
      xywh {272 152 48 32}
    }
    Fl_Button {} {
      label {|}
      xywh {328 152 48 32}
    }
    Fl_Button {} {
      label {>>}
      xywh {328 232 48 32}
    }
    Fl_Button {} {
      label {<<}
      xywh {272 232 48 32}
    }
    Fl_Button {} {
      label {.}
      xywh {72 232 48 32}
    }
    Fl_Button {} {
      label {+}
      xywh {200 112 48 32}
    }
    Fl_Button {} {
      label {-}
      xywh {200 152 48 32}
    }
    Fl_Button {} {
      label {*}
      xywh {200 192 48 32}
    }
    Fl_Button {} {
      label {/}
      xywh {200 232 48 32}
    }
    Fl_Button {} {
      label {+/-}
      xywh {272 112 48 32}
    }
    Fl_Button {} {
      label {~}
      xywh {328 112 48 32}
    }
    Fl_Button {} {
      label A
      xywh {16 288 48 32}
    }
    Fl_Button {} {
      label B
      xywh {72 288 48 32}
    }
    Fl_Button {} {
      label C
      xywh {128 288 48 32}
    }
    Fl_Button {} {
      label E
      xywh {72 328 48 32}
    }
    Fl_Button {} {
      label F
      xywh {128 328 48 32}
    }
    Fl_Button {} {
      label D
      xywh {16 328 48 32}
    }
    Fl_Button {} {
      label Dec
      xywh {400 112 80 32}
    }
    Fl_Button {} {
      label Hex
      xywh {400 152 80 32}
    }
    Fl_Button {} {
      label Oct
      xywh {400 192 80 32}
    }
    Fl_Button {} {
      label Bin
      xywh {400 232 80 32}
    }
    Fl_Button {} {
      label {√}
      xywh {200 288 64 32}
    }
    Fl_Button {} {
      label {xⁿ}
      xywh {200 328 64 32}
    }
    Fl_Output {} {
      xywh {8 69 480 12} box NO_BOX textsize 10
    }
    Fl_Button {} {
      label {=}
      xywh {128 232 48 32}
    }
    Fl_Button {} {
      label Int
      xywh {344 288 64 32}
    }
    Fl_Button {} {
      label Sin
      xywh {416 288 64 32}
    }
    Fl_Button {} {
      label Frac
      xywh {344 328 64 32}
    }
    Fl_Button {} {
      label Cos
      xywh {416 328 64 32}
    }
    Fl_Button {} {
      label {1/x}
      xywh {272 288 64 32}
    }
    Fl_Button {} {
      label {π}
      xywh {272 328 64 32}
    }
    Fl_Menu_Bar {} {open
      xywh {0 0 496 24}
    } {}
    Fl_Button {} {
      label Clear
      xywh {400 32 80 32}
    }
    Fl_Output {} {selected
      xywh {8 84 480 12} box NO_BOX textsize 10
    }
  }
  Fl_Window {} {
    label About open
    xywh {502 121 344 112} type Double visible
  } {
    Fl_Box {} {
      label JoeCalc
      xywh {80 8 256 32} labelfont 1 labelsize 24 align 21
    }
    Fl_Box {} {
      label {Copyright (c) 2015 Joe Davisson}
      xywh {80 40 256 32} labelfont 2 align 21
    }
    Fl_Box {} {
      xywh {8 8 64 64} box DOWN_BOX labelfont 1 labelsize 24 align 21
    }
    Fl_Return_Button {} {
      label button
      xywh {124 72 96 32}
    }
  }
} 
