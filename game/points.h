
#ifndef POINTS
#define POINTS

#include "../libs/cebus.h"
#include "../libs/raylib/raylib.h"

typedef struct Point {
  Vector2 pos;
  f32 radius;
} Point;


Point* get_inner_track(){
  Point* track = malloc(sizeof(Point) * 200); 
  track[0].pos = (Vector2){2030.000000, 1173.063843};
  track[0].radius = 5.000000;
  track[1].pos = (Vector2){2010.000000, 1138.675293};
  track[1].radius = 5.000000;
  track[2].pos = (Vector2){1970.000000, 1106.594482};
  track[2].radius = 5.000000;
  track[3].pos = (Vector2){1896.000000, 1064.569092};
  track[3].radius = 5.000000;
  track[4].pos = (Vector2){1082.000000, 660.561890};
  track[4].radius = 5.000000;
  track[5].pos = (Vector2){770.000000, 502.561890};
  track[5].radius = 5.000000;
  track[6].pos = (Vector2){638.000000, 482.561890};
  track[6].radius = 5.000000;
  track[7].pos = (Vector2){552.000000, 530.561890};
  track[7].radius = 5.000000;
  track[8].pos = (Vector2){500.000000, 628.561890};
  track[8].radius = 5.000000;
  track[9].pos = (Vector2){490.000000, 770.561890};
  track[9].radius = 5.000000;
  track[10].pos = (Vector2){494.000000, 886.561890};
  track[10].radius = 5.000000;
  track[11].pos = (Vector2){492.000000, 1022.561890};
  track[11].radius = 5.000000;
  track[12].pos = (Vector2){500.000000, 1084.561890};
  track[12].radius = 5.000000;
  track[13].pos = (Vector2){500.000000, 1258.561890};
  track[13].radius = 5.000000;
  track[14].pos = (Vector2){500.000000, 1388.561890};
  track[14].radius = 5.000000;
  track[15].pos = (Vector2){508.000000, 1506.561890};
  track[15].radius = 5.000000;
  track[16].pos = (Vector2){544.000000, 1590.561890};
  track[16].radius = 5.000000;
  track[17].pos = (Vector2){626.000000, 1580.561890};
  track[17].radius = 5.000000;
  track[18].pos = (Vector2){1062.000000, 1362.561890};
  track[18].radius = 5.000000;
  track[19].pos = (Vector2){1168.000000, 1308.561890};
  track[19].radius = 5.000000;
  track[20].pos = (Vector2){1296.000000, 1306.561890};
  track[20].radius = 5.000000;
  track[21].pos = (Vector2){1418.000000, 1368.561890};
  track[21].radius = 5.000000;
  track[22].pos = (Vector2){1480.000000, 1478.561890};
  track[22].radius = 5.000000;
  track[23].pos = (Vector2){1694.000000, 1912.561890};
  track[23].radius = 5.000000;
  track[24].pos = (Vector2){1806.000000, 1976.561890};
  track[24].radius = 5.000000;
  track[25].pos = (Vector2){1910.000000, 1974.561890};
  track[25].radius = 5.000000;
  track[26].pos = (Vector2){2000.000000, 1898.561890};
  track[26].radius = 5.000000;
  track[27].pos = (Vector2){2014.000000, 1322.561890};
  track[27].radius = 5.000000;
  track[28].pos = (Vector2){2018.000000, 1230.561890};
  track[28].radius = 5.000000;
  track[29].pos = (Vector2){2026.000000, 1170.561890};
  track[29].radius = 5.000000;

  
  return track;
}

Point* get_outer_track(){
  Point* track = malloc(sizeof(Point) * 200); 
track[0].pos = (Vector2){2204.000000, 1412.000000};
track[0].radius = 5.000000;
track[1].pos = (Vector2){2208.000000, 1136.000000};
track[1].radius = 5.000000;
track[2].pos = (Vector2){2194.000000, 1050.000000};
track[2].radius = 5.000000;
track[3].pos = (Vector2){2124.000000, 964.000000};
track[3].radius = 5.000000;
track[4].pos = (Vector2){2032.000000, 940.000000};
track[4].radius = 5.000000;
track[5].pos = (Vector2){1950.000000, 890.000000};
track[5].radius = 5.000000;
track[6].pos = (Vector2){1378.000000, 608.000000};
track[6].radius = 5.000000;
track[7].pos = (Vector2){1038.036255, 427.158447};
track[7].radius = 5.000000;
track[8].pos = (Vector2){731.986450, 282.225464};
track[8].radius = 5.000000;
track[9].pos = (Vector2){537.408325, 295.870728};
track[9].radius = 5.000000;
track[10].pos = (Vector2){391.357178, 413.839294};
track[10].radius = 5.000000;
track[11].pos = (Vector2){307.354004, 603.837036};
track[11].radius = 5.000000;
track[12].pos = (Vector2){317.354004, 989.837036};
track[12].radius = 5.000000;
track[13].pos = (Vector2){319.354004, 1225.837036};
track[13].radius = 5.000000;
track[14].pos = (Vector2){330.495117, 1421.217163};
track[14].radius = 5.000000;
track[15].pos = (Vector2){312.495117, 1645.599243};
track[15].radius = 5.000000;
track[16].pos = (Vector2){364.495117, 1805.358643};
track[16].radius = 5.000000;
track[17].pos = (Vector2){478.495117, 1835.320068};
track[17].radius = 5.000000;
track[18].pos = (Vector2){612.495117, 1817.298340};
track[18].radius = 5.000000;
track[19].pos = (Vector2){1196.495117, 1517.293823};
track[19].radius = 5.000000;
track[20].pos = (Vector2){1298.495117, 1555.293823};
track[20].radius = 5.000000;
track[21].pos = (Vector2){1432.495117, 1837.293823};
track[21].radius = 5.000000;
track[22].pos = (Vector2){1508.495117, 1979.293823};
track[22].radius = 5.000000;
track[23].pos = (Vector2){1608.495117, 2111.293945};
track[23].radius = 5.000000;
track[24].pos = (Vector2){1696.495117, 2167.293945};
track[24].radius = 5.000000;
track[25].pos = (Vector2){1830.495117, 2197.293945};
track[25].radius = 5.000000;
track[26].pos = (Vector2){1916.495117, 2195.293945};
track[26].radius = 5.000000;
track[27].pos = (Vector2){2030.495117, 2165.293945};
track[27].radius = 5.000000;
track[28].pos = (Vector2){2144.495117, 2109.293945};
track[28].radius = 5.000000;
track[29].pos = (Vector2){2206.495117, 1997.293823};
track[29].radius = 5.000000;
track[30].pos = (Vector2){2202.495117, 1413.293823};
track[30].radius = 5.000000;
  return track;
}

Point* get_check_marks(){
  Point* track = malloc(sizeof(Point) * 100);
track[0].pos = (Vector2){2021.428467, 1258.857056};
track[0].radius = 5.000000;
track[1].pos = (Vector2){2194.285645, 1263.142822};
track[1].radius = 5.000000;
track[2].pos = (Vector2){2002.857056, 1113.142822};
track[2].radius = 5.000000;
track[3].pos = (Vector2){2135.714355, 987.428467};
track[3].radius = 5.000000;
track[4].pos = (Vector2){1782.737549, 996.305054};
track[4].radius = 5.000000;
track[5].pos = (Vector2){1862.527588, 858.206665};
track[5].radius = 5.000000;
track[6].pos = (Vector2){1361.610107, 792.297119};
track[6].radius = 5.000000;
track[7].pos = (Vector2){1450.148926, 652.290894};
track[7].radius = 5.000000;
track[8].pos = (Vector2){1053.005981, 636.576538};
track[8].radius = 5.000000;
track[9].pos = (Vector2){1145.863159, 492.290894};
track[9].radius = 5.000000;
track[10].pos = (Vector2){782.629272, 501.434875};
track[10].radius = 5.000000;
track[11].pos = (Vector2){861.875366, 351.367584};
track[11].radius = 5.000000;
track[12].pos = (Vector2){633.475586, 295.132507};
track[12].radius = 5.000000;
track[13].pos = (Vector2){636.169128, 470.779175};
track[13].radius = 5.000000;
track[14].pos = (Vector2){401.830322, 417.900208};
track[14].radius = 5.000000;
track[15].pos = (Vector2){536.110596, 543.612366};
track[15].radius = 5.000000;
track[16].pos = (Vector2){314.682068, 710.755249};
track[16].radius = 5.000000;
track[17].pos = (Vector2){483.253479, 727.898071};
track[17].radius = 5.000000;
track[18].pos = (Vector2){319.013306, 920.767700};
track[18].radius = 5.000000;
track[19].pos = (Vector2){482.075684, 926.505066};
track[19].radius = 5.000000;
track[20].pos = (Vector2){325.740784, 1208.425171};
track[20].radius = 5.000000;
track[21].pos = (Vector2){487.093384, 1213.119263};
track[21].radius = 5.000000;
track[22].pos = (Vector2){328.501770, 1533.228638};
track[22].radius = 5.000000;
track[23].pos = (Vector2){492.784790, 1507.527832};
track[23].radius = 5.000000;
track[24].pos = (Vector2){375.369995, 1799.139404};
track[24].radius = 5.000000;
track[25].pos = (Vector2){536.303223, 1595.759521};
track[25].radius = 5.000000;
track[26].pos = (Vector2){626.177917, 1590.997559};
track[26].radius = 5.000000;
track[27].pos = (Vector2){671.871399, 1771.155273};
track[27].radius = 5.000000;
track[28].pos = (Vector2){821.862671, 1489.793945};
track[28].radius = 5.000000;
track[29].pos = (Vector2){876.145386, 1671.244385};
track[29].radius = 5.000000;
track[30].pos = (Vector2){1057.573853, 1371.247803};
track[30].radius = 5.000000;
track[31].pos = (Vector2){1111.859619, 1548.390625};
track[31].radius = 5.000000;
track[32].pos = (Vector2){1320.430908, 1328.390625};
track[32].radius = 5.000000;
track[33].pos = (Vector2){1244.716797, 1528.390625};
track[33].radius = 5.000000;
track[34].pos = (Vector2){1340.872192, 1622.305176};
track[34].radius = 5.000000;
track[35].pos = (Vector2){1495.772583, 1540.327148};
track[35].radius = 5.000000;
track[36].pos = (Vector2){1462.251221, 1874.491211};
track[36].radius = 5.000000;
track[37].pos = (Vector2){1615.265259, 1781.609375};
track[37].radius = 5.000000;
track[38].pos = (Vector2){1776.766113, 1970.169556};
track[38].radius = 5.000000;
track[39].pos = (Vector2){1731.064697, 2165.883789};
track[39].radius = 5.000000;
track[40].pos = (Vector2){1966.778931, 1930.169556};
track[40].radius = 5.000000;
track[41].pos = (Vector2){2065.350342, 2133.026611};
track[41].radius = 5.000000;
track[42].pos = (Vector2){2003.921753, 1777.312378};
track[42].radius = 5.000000;
track[43].pos = (Vector2){2193.921631, 1780.169556};
track[43].radius = 5.000000;
track[44].pos = (Vector2){2012.493286, 1550.169556};
track[44].radius = 5.000000;
track[45].pos = (Vector2){2192.493164, 1545.883789};
track[45].radius = 5.000000;
  return track;
}

// void write_points_to_file(const char *filename, Point *points,
//                               size_t count) {
//   FILE *file = fopen(filename, "wb");
//   if (!file) {
//     perror("Error opening file for writing");
//     return;
//   }
//   fwrite(&count, sizeof(size_t), 1, file);
//   fwrite(points, sizeof(Point), count, file);
//   fclose(file);
// }

// Point *read_points_from_file(const char *filename, i32 *count) {
//   FILE *file = fopen(filename, "rb");
//   if (!file) {
//     perror("Error opening file for reading");
//     return NULL;
//   }
//
//   fread(count, sizeof(size_t), 1, file);
//
//   Point *points = malloc(sizeof(Point) * (*count + 100));
//   if (!points) {
//     perror("Error allocating memory");
//     fclose(file);
//     return NULL;
//   }
//
//   fread(points, sizeof(Point), *count, file);
//   fclose(file);
//   return points;
// }
//

#endif // !j
