
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "ImageTraversal.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

PNG getTestPNG() {
  PNG png(4, 4);
  HSLAPixel blackPixel(180, 1, 0);
  for (unsigned i = 0; i < 4; i++) {
    png.getPixel(i, 0) = blackPixel;
    png.getPixel(0, i) = blackPixel;
    png.getPixel(i, 3) = blackPixel;
    png.getPixel(3, i) = blackPixel;
  }
    
  return png;
}

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;       png.readFromFile("../data/i.png");
  PNG expected;  expected.readFromFile("../data/i-rainbow-dfs.png");
  PNG expected2; expected2.readFromFile("../data/i-rainbow-dfs-2.png");
  
  FloodFilledImage image(png);
  Traversals::ImageTraversal dfs(png, Point(40, 40), 0.05, {
    Traversals::dfs_add, Traversals::dfs_pop, Traversals::dfs_peek
  });

  RainbowColorPicker rainbow(0.05);
  image.addFloodFill( dfs, rainbow );
  std::cout << "before animate" << std::endl;
  Animation animation = image.animate(1000);
  std::cout << "after animate" << std::endl;
  
  //REQUIRE( animation.frameCount() > 2 );
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  secondFrame.writeToFile("i-rainbow-dfs-2.png");
  lastFrame.writeToFile("i-rainbow-dfs.png");
  animation.write("i-rainbow-dfs.gif");
  // INFO("Files written to i-rainbow-dfs-* for debugging.");
  
  // REQUIRE( secondFrame == expected2 );
  // REQUIRE( lastFrame == expected );

  return 0;
}
