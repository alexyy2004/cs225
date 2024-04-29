/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource, vector<TileImage>& theTiles) {
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    MosaicCanvas* mosaic = new MosaicCanvas(rows, columns);
    vector<Point<3>> points;
    // Populate pointToTile map with average colors of TileImages
    std::map<Point<3>, TileImage*> pointToTile;
    for (size_t i = 0; i < theTiles.size(); ++i) {
        LUVAPixel pixel = theTiles[i].getAverageColor();
        Point<3> point = convertToXYZ(pixel);
        pointToTile[point] = &theTiles[i];
        points.push_back(point);
    }
    KDTree<3>* tree = new KDTree<3>(points);
    // Iterate through the rows and columns of the mosaic
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            // Get the average color of the region in the source image
            LUVAPixel region_color = theSource.getRegionColor(row, col);
            Point<3> region_point = convertToXYZ(region_color);
            Point<3> nearest_point = tree->findNearestNeighbor(region_point);

            // Find the closest TileImage based on the region color
            TileImage* closestTile = pointToTile[nearest_point];

            // Set the TileImage in the MosaicCanvas at the corresponding position
            mosaic->setTile(row, col, closestTile);
        }
    }

    return mosaic;
}

// MosaicCanvas* mapTiles(SourceImage const& theSource,
//                        vector<TileImage>& theTiles)
// {
//     /**
//      * @todo Implement this function!
//      */
//     MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

//     map<Point<3>, size_t> tiles_map; //points and index of image in theTiles
//     vector<Point<3>> points;
//     for(size_t i = 0; i < theTiles.size(); i++){
//       LUVAPixel pixel = theTiles[i].getAverageColor();
//       Point<3> point = convertToXYZ(pixel);
//       points.push_back(point);
//       tiles_map.insert(pair<Point<3>, size_t>(point,i));
//     }
//     //build a kdTree
//     KDTree<3>* tree = new KDTree<3>(points);
//     for(int i = 0; i < theSource.getRows(); i++){
//       for(int j = 0; j < theSource.getColumns(); j++){
//         LUVAPixel region_color = theSource.getRegionColor(i, j);
//         Point<3> region_point = convertToXYZ(region_color);
//         Point<3> nearest_point = tree->findNearestNeighbor(region_point);
//         size_t index = tiles_map[nearest_point];
//         canvas->setTile(i, j, &theTiles[index]);
//       }
//     }
//     //delete tree;  //for memory leak check
//     return canvas;
// }

