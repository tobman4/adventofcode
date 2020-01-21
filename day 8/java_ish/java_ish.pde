/*

SPAGET
need funcs

*/
/**/
int W = 25;
int H = 6;
int L;
/**/
String file = "./../pic";

color[] color_map = new color[3];

String raw_data = "";
String[] data;

void setup() {
  // set colors to be used
  color_map[0] = color(255,0,0);
  color_map[1] = color(0,255,0);
  color_map[2] = color(0,0,255);
  
  // open file  
  String[] lines = loadStrings(file);
  println("there are " + lines.length + " lines");
  for (int i = 0 ; i < lines.length; i++) {
    raw_data += lines[i];
    println(lines[i]);
  }

  // split data to array
  data = new String[raw_data.length()];
  data = raw_data.split("");
  println("setup done");
}

void draw() {
  println("draw start");
  background(0);
  

  // setup variabels we need for the size
  L = data.length/(W*H);
  int layers[][][] = new int[L][H][W];
  

  // variabels we need to solve part 1;
  int on = 0;
  int best = 999999999;
  int zero_count;
  int one_count,two_count;
  int solve = -1;
  
  // put data onto 3d array

  /*
    a = layer
    i = Y
    j = X
  */
  for(int a = 0; a < layers.length; a++) { // layer loop
    // reset layer "stats"
    zero_count = 0;
    one_count = 0;
    two_count = 0;

    for(int i = 0; i < H; i++) { // heigth loop(Y)
        for(int j = 0; j < W; j++) { // width loop(x)
          // count ints for part 1
          if(int(data[on]) == 0) {
            zero_count++;
          } else if(int(data[on]) == 1) {
            one_count++;
          } else if(int(data[on]) == 2) {
            two_count++;
          }
          layers[a][i][j] = int(data[on]); // write to array
         on++;// inc index counter
       }
    }
    // find the one whit fewest 0`s
    if(zero_count < best) {
       best = zero_count;
       solve = one_count*two_count;
       println(a + " = " + zero_count + " = " + str(one_count) + " " + str(two_count) + " = " + one_count*two_count);
    }
    
  }
  
  int layerd[][] = new int[H][W]; // create output array
  for(int i = 0; i < layerd.length; i++) {
      for(int j = 0; j < layerd[i].length; j++) {
        layerd[i][j] = 2; // fill whit transparent
      }
    }


  for(int a = 0; a < layers.length; a++) {
    for(int i = 0; i < layerd.length; i++) {
      for(int j = 0; j < layerd[i].length; j++) {
        if(layerd[i][j] == 2) { // if transparent set to pixel
          layerd[i][j] = layers[a][i][j];
        }
      }
    }
  }


  // draw to screen
  loadPixels();

  /*
  #############################################################
  # set size(2500,100) if u want to se all and uncoment under #
  # v   vv   vv   vv   vv   vv   vv   vv   vv   vv   vv   vv  #
  #############################################################
  */


  // for(int a = 0; a < layers.length; a++) {
  //   for(int i = 0; i < layers[a].length; i++) {
  //     for(int j = 0; j < layers[a][i].length; j++) {
  //       pixels[(width*i) + (j+W*a)] = color_map[layers[a][i][j]];
  //     }
  //   }
  // }

  for(int i = 0; i < layerd.length; i++) {
      for(int j = 0; j < layerd[i].length; j++) {
        pixels[(width*(i+H)) + j] = color_map[layerd[i][j]];
      }
    }

  updatePixels();
  noLoop();
  println("draw end");
}

public void settings() {
  size(100, 100);
  pixelDensity(1);
}
