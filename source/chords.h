#define NOTE_C2  36
#define NOTE_Cs2 37
#define NOTE_D2  38
#define NOTE_DS2 39
#define NOTE_E2  40
#define NOTE_F2  41
#define NOTE_Fs2 42
#define NOTE_G2  43
#define NOTE_Gs2 44
#define NOTE_A2  45
#define NOTE_As2 46
#define NOTE_B2  47

#define NOTE_C3  48
#define NOTE_Cs3 49
#define NOTE_D3  50
#define NOTE_Ds3 51
#define NOTE_E3  52
#define NOTE_F3  53
#define NOTE_Fs3 54
#define NOTE_G3  55
#define NOTE_Gs3 56
#define NOTE_A3  57
#define NOTE_As3 58
#define NOTE_B3  59

#define NOTE_C4  60
#define NOTE_Cs4 61
#define NOTE_D4  62
#define NOTE_Ds4 63
#define NOTE_E4  64
#define NOTE_F4  65
#define NOTE_Fs4 66
#define NOTE_G4  67
#define NOTE_Gs4 68
#define NOTE_A4  69
#define NOTE_As4 70
#define NOTE_B4  71

#define NOTE_C5  72
#define NOTE_Cs5 73
#define NOTE_D5  74
#define NOTE_Ds5 75
#define NOTE_E5  76
#define NOTE_F5  76
#define NOTE_Fs5 77
#define NOTE_G5  78
#define NOTE_Gs5 79
#define NOTE_A5  79
#define NOTE_As5 80
#define NOTE_B5  81


// The equation for note to frequency is:
// float freq = 440.0f * exp2f((float)(note - 69) * 0.0833333f);

// according to http://www.guitar-chords.org.uk/
// and http://www.8notes.com/guitar_chord_chart/c.asp

/// Major
int Cmaj[4]   =  {NOTE_C3, NOTE_E3, NOTE_G3, 0};       //  C  - E  - G
int Csmaj[4]  =  {NOTE_Cs3, NOTE_F3, NOTE_Gs3, 0};     //  C# - F  - G#
int Dmaj[4]   =  {NOTE_D3, NOTE_Fs3, NOTE_A3, 0};      //  D  - F# - A
int Dsmaj[4]  =  {NOTE_Ds3, NOTE_G3, NOTE_As3, 0};     //  D# - G  - A#
int Emaj[4]   =  {NOTE_E3, NOTE_Gs3, NOTE_B3, 0};      //  E  - G# - B
int Fmaj[4]   =  {NOTE_F3, NOTE_A3, NOTE_C4, 0};       //  F  - A  - C
int Fsmaj[4]  =  {NOTE_Fs3, NOTE_As3, NOTE_Cs4, 0};    //  F# - A# - C
int Gmaj[4]   =  {NOTE_G3, NOTE_B3, NOTE_D4, 0};       //  G  - B  - D
int Gsmaj[4]  =  {NOTE_Gs3, NOTE_C4, NOTE_Ds4, 0};     //  G# - C  - D#
int Amaj[4]   =  {NOTE_A3, NOTE_Cs4, NOTE_E4, 0};      //  A  - C# - E
int Asmaj[4]  =  {NOTE_As3, NOTE_D4, NOTE_F4, 0};      //  A# - D  - F
int Bmaj[4]   =  {NOTE_B3, NOTE_G4, NOTE_Fs4, 0};      //  B  - D# - F#

// Major 2
int Cmaj2[4]  =  {NOTE_C4, NOTE_E4, NOTE_G4, 0};       //  C  - E  - G
int Csmaj2[4] =  {NOTE_Cs4, NOTE_F4, NOTE_Gs4, 0};     //  C# - F  - G#
int Dmaj2[4]  =  {NOTE_D4, NOTE_Fs4, NOTE_A4, 0};      //  D  - F# - A
int Dsmaj2[4] =  {NOTE_Ds4, NOTE_G4, NOTE_As4, 0};     //  D# - G  - A#
int Emaj2[4]  =  {NOTE_E4, NOTE_Gs4, NOTE_B4, 0};      //  E  - G# - B
int Fmaj2[4]  =  {NOTE_F4, NOTE_A4, NOTE_C5, 0};       //  F  - A  - C
int Fsmaj2[4] =  {NOTE_Fs4, NOTE_As4, NOTE_Cs5, 0};    //  F# - A# - C
int Gmaj2[4]  =  {NOTE_G4, NOTE_B4, NOTE_D5, 0};       //  G  - B  - D
int Gsmaj2[4] =  {NOTE_Gs4, NOTE_C5, NOTE_Ds5, 0};     //  G# - C  - D#
int Amaj2[4]  =  {NOTE_A4, NOTE_Cs5, NOTE_E5, 0};      //  A  - C# - E
int Asmaj2[4] =  {NOTE_As4, NOTE_D5, NOTE_F5, 0};      //  A# - D  - F
int Bmaj2[4]  =  {NOTE_B4, NOTE_G5, NOTE_Fs5, 0};      //  B  - D# - F#

/// Minor
int Cmin[4]   =  {NOTE_C3, NOTE_Ds3, NOTE_G3, 1};      //  C  - D# - G
int Csmin[4]  =  {NOTE_Cs3, NOTE_E3, NOTE_Gs3, 1};     //  C# - E  - G#
int Dmin[4]   =  {NOTE_D3, NOTE_F3, NOTE_A3, 1};       //  D  - F  - A
int Dsmin[4]  =  {NOTE_Ds3, NOTE_Fs3, NOTE_As3, 1};    //  D# - F# - A#
int Emin[4]   =  {NOTE_E3, NOTE_G3, NOTE_B3, 1};       //  E  - G  - B
int Fmin[4]   =  {NOTE_F3, NOTE_Gs3, NOTE_C4, 1};      //  F  - G# - C
int Fsmin[4]  =  {NOTE_Fs3, NOTE_A3, NOTE_Cs4, 1};     //  F# - A  - C
int Gmin[4]   =  {NOTE_G3, NOTE_As3, NOTE_D4, 1};      //  G  - A# - D
int Gsmin[4]  =  {NOTE_Gs3, NOTE_B3, NOTE_Ds4, 1};     //  G# - B  - D#
int Amin[4]   =  {NOTE_A3, NOTE_C4, NOTE_E4, 1};       //  A  - C  - E
int Asmin[4]  =  {NOTE_As3, NOTE_Cs4, NOTE_F4, 1};     //  A# - C# - F
int Bmin[4]   =  {NOTE_B3, NOTE_D4, NOTE_Fs4, 1};      //  B  - D  - F#

/// Minor 2
int Cmin2[4]   =  {NOTE_C4, NOTE_Ds4, NOTE_G4, 1};      //  C  - D# - G
int Csmin2[4]  =  {NOTE_Cs4, NOTE_E4, NOTE_Gs4, 1};     //  C# - E - G#
int Dmin2[4]   =  {NOTE_D4, NOTE_F4, NOTE_A4, 1};       //  D  - F - A
int Dsmin2[4]  =  {NOTE_Ds4, NOTE_Fs4, NOTE_As4, 1};    //  D# - F# - A#
int Emin2[4]   =  {NOTE_E4, NOTE_G4, NOTE_B4, 1};       //  E  - G - B
int Fmin2[4]   =  {NOTE_F4, NOTE_Gs4, NOTE_C5, 1};      //  F  - G# - C
int Fsmin2[4]  =  {NOTE_Fs4, NOTE_A4, NOTE_Cs5, 1};     //  F# - A - C
int Gmin2[4]   =  {NOTE_G4, NOTE_As4, NOTE_D5, 1};      //  G  - A# - D
int Gsmin2[4]  =  {NOTE_Gs4, NOTE_B4, NOTE_Ds5, 1};     //  G# - B - D#
int Amin2[4]   =  {NOTE_A4, NOTE_C5, NOTE_E5, 1};       //  A  - C - E
int Asmin2[4]  =  {NOTE_As4, NOTE_Cs5, NOTE_F5, 1};     //  A# - C# - F
int Bmin2[4]   =  {NOTE_B4, NOTE_D5, NOTE_Fs5, 1};      //  B  - D - F#

/// Diminished
int Cdim[4]   =  {NOTE_C3, NOTE_Ds3, NOTE_Fs3, 1};     //  C  - D# - F#
int Csdim[4]  =  {NOTE_Cs3, NOTE_E3, NOTE_G3, 1};      //  C# - E  - G
int Ddim[4]   =  {NOTE_D3, NOTE_F3, NOTE_Gs3, 1};      //  D  - F  - G#
int Dsdim[4]  =  {NOTE_Ds3, NOTE_Fs3, NOTE_A3, 1};     //  D# - F# - A
int Edim[4]   =  {NOTE_E3, NOTE_G3, NOTE_As3, 1};      //  E  - G  - A#
int Fdim[4]   =  {NOTE_F3, NOTE_Gs3, NOTE_B3, 1};      //  F  - G# - B
int Fsdim[4]  =  {NOTE_Fs3, NOTE_A3, NOTE_C4, 1};      //  F# - A  - C
int Gdim[4]   =  {NOTE_G3, NOTE_As3, NOTE_Cs4, 1};     //  G  - A# - C#
int Gsdim[4]  =  {NOTE_Gs3, NOTE_B3, NOTE_D4, 1};      //  G# - B  - D
int Adim[4]   =  {NOTE_A3, NOTE_C4, NOTE_Ds4, 1};      //  A  - C  - D#
int Asdim[4]  =  {NOTE_As3, NOTE_Cs4, NOTE_E4, 1};     //  A# - C# - E
int Bdim[4]   =  {NOTE_B3, NOTE_D4, NOTE_F4, 1};       //  B  - D  - F

/// Diminished 2
int Cdim2[4]   =  {NOTE_C4, NOTE_Ds4, NOTE_Fs4, 1};     //  C  - D# - F#
int Csdim2[4]  =  {NOTE_Cs4, NOTE_E4, NOTE_G4, 1};      //  C# - E  - G
int Ddim2[4]   =  {NOTE_D4, NOTE_F4, NOTE_Gs4, 1};      //  D  - F  - G#
int Dsdim2[4]  =  {NOTE_Ds4, NOTE_Fs4, NOTE_A4, 1};     //  D# - F# - A
int Edim2[4]   =  {NOTE_E4, NOTE_G4, NOTE_As4, 1};      //  E  - G  - A#
int Fdim2[4]   =  {NOTE_F4, NOTE_Gs4, NOTE_B4, 1};      //  F  - G# - B
int Fsdim2[4]  =  {NOTE_Fs4, NOTE_A4, NOTE_C5, 1};      //  F# - A  - C
int Gdim2[4]   =  {NOTE_G4, NOTE_As4, NOTE_Cs5, 1};     //  G  - A# - C#
int Gsdim2[4]  =  {NOTE_Gs4, NOTE_B4, NOTE_D5, 1};      //  G# - B  - D
int Adim2[4]   =  {NOTE_A4, NOTE_C5, NOTE_Ds5, 1};      //  A  - C  - D#
int Asdim2[4]  =  {NOTE_As4, NOTE_Cs5, NOTE_E5, 1};     //  A# - C# - E
int Bdim2[4]   =  {NOTE_B4, NOTE_D5, NOTE_F5, 1};       //  B  - D  - F
