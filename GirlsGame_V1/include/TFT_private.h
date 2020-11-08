#ifndef TFT_PRIVATE_H
#define TFT_PRIVATE_H



typedef enum {
    // 1x high & 1x wide size
    X1 = 0x11,
    // 2x high & 1x wide size
    X2 = 0x21,
    // 2x high & 2x wider size
    // 0x0A is set because need to offset 5 position to right
    //      when draw the characters of string
    X3 = 0x22
  } ESizes;

  // number of cols for chars
#define CHARS_COLS_LEN 5
  // number of rows for chars
 #define CHARS_ROWS_LEN 8

 extern const u8 CHARACTERS[][CHARS_COLS_LEN];

static void voidWriteCommand(u8 copy_u8Command);
static void voidWriteData(u8 copy_u8Data);


#endif
