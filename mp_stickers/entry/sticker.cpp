#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 1);

  sheet.addSticker(i, -42, -225);

  Image render = sheet.render();

  // REQUIRE( render.width() == alma.width() + 42 );
  // REQUIRE( render.height() == alma.height() + 225 );

  //checkStickerPlacement(i, render, 0, 0);
  render.writeToFile("myImage.png");

  
  return 0;
}
