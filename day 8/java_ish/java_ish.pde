int W = 26;
int H = 6;


String file = "./../pic_test";

color[] color_map = new color[3];

String raw_data = "";
String[] data;

void setup() {
  size(600,600);
  displayDensity(1);
  
  // open file  
  String[] lines = loadStrings(file);
  println("there are " + lines.length + " lines");
  for (int i = 0 ; i < lines.length; i++) {
    raw_data += lines[i];
    println(lines[i]);
  }
  data = new String[raw_data.length()];
  data = raw_data.split("");
  println("setup done");
}

void draw() {
  background(0);
  scale(10);
  loadPixels();
  for(int i = 0; i < W; i++) {
    for(int j = 0; j > H; j++) {
      pixels[i] = color(255,0,255);
    }
  }
  updatePixels();
  noLoop();
}
