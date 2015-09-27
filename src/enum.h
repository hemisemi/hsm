#ifndef SWAPI_ENUM_H
#define SWAPI_ENUM_H

namespace hsm{

enum DefaultColor{
    black,
    white,
    red,
    green,
    blue,
    transparent
};

enum CaseSensitivity{
    CaseInsensitive = 0,
    CaseSensitive = 1
};

enum EventPriority{
    HighEventPriority = 1,
    NormalEventPriority = 0,
    LowEventPriority = -1
};

enum Direction{
    Horizontal,
    Vertical
};

enum Alignment{
    AlignLeft = 0x001,
    AlignRight = 0x002,
    AlignHCenter = 0x003,
    AlignJustify = 0x004,
    AlignHorizontal_Flag = AlignLeft | AlignRight | AlignHCenter | AlignJustify,

    AlignTop = 0x020,
    AlignBottom = 0x040,
    AlignVCenter = 0x080,
    AlignVertical_Flag = AlignTop | AlignBottom | AlignVCenter
};

enum MouseButton{
    NoButton = 0,
    LeftButton = 1,
    RightButton = 2,
    MiddleButton = 4,
    AllButton = LeftButton | RightButton | MiddleButton
};

enum KeyboardModifier{
    NoModifier = 0,
    ShiftModifier = 0x02000000,
    ControlModifier = 0x04000000,
    AltModifier = 0x08000000,
    MetaModifier = 0x10000000,
    KeypadModifier = 0x20000000,
    GroupSwitchModifier = 0x40000000
};

enum Key{
    Key_Unknown = 0,
    //
    Key_Escape = 0x01000000,
    Key_Tab = 0x01000001,
    Key_Backtab = 0x01000002,
    Key_Backspace = 0x01000003,
    Key_Return = 0x01000004,
    Key_Enter = 0x01000005,
    Key_Insert = 0x01000006,
    Key_Delete = 0x01000007,
    Key_Pause = 0x01000008,
    //
    Key_Left = 0x01000012,
    Key_Up = 0x01000013,
    Key_Right = 0x01000014,
    Key_Down = 0x01000015,
    //
    Key_ShiftL = 0x01100000,
    Key_ShiftR = 0x01100001,
    Key_ControlL = 0x01100002,
    Key_ControlR = 0x01100003,
    Key_MetaL = 0x01100004,
    Key_MetaR = 0x01100005,
    Key_CapsLock = 0x01000024,
    Key_ShiftLock = 0x01000025,
    Key_NumLock = 0x01000026,
    //
    Key_Keypad = 0x11000000,
    Key_Keypad0 = 0x11000030,
    Key_Keypad1 = 0x11000031,
    Key_Keypad2 = 0x11000032,
    Key_Keypad3 = 0x11000033,
    Key_Keypad4 = 0x11000034,
    Key_Keypad5 = 0x11000035,
    Key_Keypad6 = 0x11000036,
    Key_Keypad7 = 0x11000037,
    Key_Keypad8 = 0x11000038,
    Key_Keypad9 = 0x11000039,
    //
    Key_F1	= 0x01000030,
    Key_F2	= 0x01000031,
    Key_F3	= 0x01000032,
    Key_F4	= 0x01000033,
    Key_F5	= 0x01000034,
    Key_F6	= 0x01000035,
    Key_F7	= 0x01000036,
    Key_F8	= 0x01000037,
    Key_F9	= 0x01000038,
    Key_F10	= 0x01000039,
    Key_F11	= 0x0100003a,
    Key_F12	= 0x0100003b,
    Key_F13	= 0x0100003c,
    Key_F14	= 0x0100003d,
    Key_F15	= 0x0100003e,
    Key_F16	= 0x0100003f,
    Key_F17	= 0x01000040,
    Key_F18	= 0x01000041,
    Key_F19	= 0x01000042,
    Key_F20	= 0x01000043,
    Key_F21	= 0x01000044,
    Key_F22	= 0x01000045,
    Key_F23	= 0x01000046,
    Key_F24	= 0x01000047,
    Key_F25	= 0x01000048,
    Key_F26	= 0x01000049,
    Key_F27	= 0x0100004a,
    Key_F28	= 0x0100004b,
    Key_F29	= 0x0100004c,
    Key_F30	= 0x0100004d,
    Key_F31	= 0x0100004e,
    Key_F32	= 0x0100004f,
    Key_F33	= 0x01000050,
    Key_F34	= 0x01000051,
    Key_F35	= 0x01000052,
    // control chars
    Key_Space = 0x20,
    Key_Any = Key_Space,
    Key_Exclam = 0x21,
    Key_QuoteDbl = 0x22,
    Key_NumberSign = 0x23,
    Key_Dollar = 0x24,
    Key_Percent = 0x25,
    Key_Ampersand = 0x26,
    Key_Apostrophe = 0x27,
    Key_ParenLeft = 0x28,
    Key_ParenRight = 0x29,
    Key_Asterisk = 0x2a,
    Key_Plus = 0x2b,
    Key_Comma = 0x2c,
    Key_Minus = 0x2d,
    Key_Period = 0x2e,
    Key_Slash = 0x2f,
    Key_0 = 0x30,
    Key_1 = 0x31,
    Key_2 = 0x32,
    Key_3 = 0x33,
    Key_4 = 0x34,
    Key_5 = 0x35,
    Key_6 = 0x36,
    Key_7 = 0x37,
    Key_8 = 0x38,
    Key_9 = 0x39,
    Key_Colon = 0x3a,
    Key_Semicolon = 0x3b,
    Key_Less = 0x3c,
    Key_Equal = 0x3d,
    Key_Greater = 0x3e,
    Key_Question = 0x3f,
    Key_At = 0x40,
    Key_A = 0x41,
    Key_B = 0x42,
    Key_C = 0x43,
    Key_D = 0x44,
    Key_E = 0x45,
    Key_F = 0x46,
    Key_G = 0x47,
    Key_H = 0x48,
    Key_I = 0x49,
    Key_J = 0x4a,
    Key_K = 0x4b,
    Key_L = 0x4c,
    Key_M = 0x4d,
    Key_N = 0x4e,
    Key_O = 0x4f,
    Key_P = 0x50,
    Key_Q = 0x51,
    Key_R = 0x52,
    Key_S = 0x53,
    Key_T = 0x54,
    Key_U = 0x55,
    Key_V = 0x56,
    Key_W = 0x57,
    Key_X = 0x58,
    Key_Y = 0x59,
    Key_Z = 0x5a,
    Key_BracketLeft = 0x5b,
    Key_Backslash = 0x5c,
    Key_BracketRight = 0x5d,
    Key_AsciiCircum = 0x5e,
    Key_Underscore = 0x5f,
    Key_QuoteLeft = 0x60,
    // lower cases
    Key_BraceLeft = 0x7b,
    Key_Bar = 0x7c,
    Key_BraceRight = 0x7d,
    Key_AsciiTilde = 0x7e,
    // control chars
    Key_nobreakspace = 0x0a0,
    Key_exclamdown = 0x0a1,
    Key_cent = 0x0a2,
    Key_sterling = 0x0a3,
    Key_currency = 0x0a4,
    Key_yen = 0x0a5,
    Key_brokenbar = 0x0a6,
    Key_section = 0x0a7,
    Key_diaeresis = 0x0a8,
    Key_copyright = 0x0a9,
    Key_ordfeminine = 0x0aa,
    Key_guillemotleft = 0x0ab,
    Key_notsign = 0x0ac,
    Key_hyphen = 0x0ad,
    Key_registered = 0x0ae,
    Key_macron = 0x0af,
    Key_degree = 0x0b0,
    Key_plusminus = 0x0b1,
    Key_twosuperior = 0x0b2,
    Key_threesuperior = 0x0b3,
    Key_acute = 0x0b4,
    Key_mu = 0x0b5,
    Key_paragraph = 0x0b6,
    Key_periodcentered = 0x0b7,
    Key_cedilla = 0x0b8,
    Key_onesuperior = 0x0b9,
    Key_masculine = 0x0ba,
    Key_guillemotright = 0x0bb,
    Key_onequarter = 0x0bc,
    Key_onehalf = 0x0bd,
    Key_threequarters = 0x0be,
    Key_questiondown = 0x0bf,
    Key_Agrave = 0x0c0,
    Key_Aacute = 0x0c1,
    Key_Acircumflex = 0x0c2,
    Key_Atilde = 0x0c3,
    Key_Adiaeresis = 0x0c4,
    Key_Aring = 0x0c5,
    Key_AE = 0x0c6,
    Key_Ccedilla = 0x0c7,
    Key_Egrave = 0x0c8,
    Key_Eacute = 0x0c9,
    Key_Ecircumflex = 0x0ca,
    Key_Ediaeresis = 0x0cb,
    Key_Igrave = 0x0cc,
    Key_Iacute = 0x0cd,
    Key_Icircumflex = 0x0ce,
    Key_Idiaeresis = 0x0cf,
    Key_ETH = 0x0d0,
    Key_Ntilde = 0x0d1,
    Key_Ograve = 0x0d2,
    Key_Oacute = 0x0d3,
    Key_Ocircumflex = 0x0d4,
    Key_Otilde = 0x0d5,
    Key_Odiaeresis = 0x0d6,
    Key_multiply = 0x0d7,
    Key_Ooblique = 0x0d8,
    Key_Ugrave = 0x0d9,
    Key_Uacute = 0x0da,
    Key_Ucircumflex = 0x0db,
    Key_Udiaeresis = 0x0dc,
    Key_Yacute = 0x0dd,
    Key_THORN = 0x0de,
    Key_ssharp = 0x0df,
    /*Key_agrave  = 0x00e0,
    Key_aacute = 0x00e1,
    Key_acircumflex = 0x00e2,
    Key_atilde = 0x00e3,
    Key_adiaeresis = 0x00e4,
    Key_aring = 0x00e5,
    Key_ae = 0x00e6,
    Key_ccedilla = 0x00e7,
    Key_egrave = 0x00e8,
    Key_eacute = 0x00e9,
    Key_ecircumflex = 0x00ea,
    Key_ediaeresis = 0x00eb,
    Key_igrave = 0x00ec,
    Key_iacute = 0x00ed,
    Key_icircumflex = 0x00ee,
    Key_idiaeresis = 0x00ef,
    Key_eth = 0x00f0,
    Key_ntilde = 0x00f1,
    Key_ograve = 0x00f2,
    Key_oacute = 0x00f3,
    Key_ocircumflex = 0x00f4,
    Key_otilde = 0x00f5,
    Key_odiaeresis = 0x00f6,*/
    Key_division = 0x0f7,
    /*Key_oslash = 0x0f8,
    Key_ooblique = 0x0f9,
    Key_ugrave = 0x0fa,
    Key_uacute = 0x0fb,
    Key_ucircumflex = 0x00fb,
    Key_udiaeresis = 0x00fc,
    Key_yacute = 0x00fd,
    Key_thorn = 0x00fe,*/
    Key_ydiaeresis = 0x0ff
};

}

#endif // SWAPI_ENUM_H