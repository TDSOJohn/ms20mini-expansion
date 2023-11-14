#define pin_s1 2
#define pin_s2 3
#define pin_s3 4
#define pin_s4 5
#define pin_p0 6
#define pin_p1 7
#define pin_p2 8
#define pin_p3 9

const int keyboard_size = 40;
int keyboard_data[keyboard_size];

const int period_ms = 1;

int data[10][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 1, 0, 0},
  {0, 1, 0, 1},
  {0, 1, 1, 0},
  {0, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 1}
};

void print_all() {
  for(int i = 0; i < keyboard_size; i++) {
    if(i%4==0)
      Serial.print(" ");
    Serial.print(keyboard_data[i]);
  }
  Serial.println();
}

// output a 4-bit word on all 4 output pins (p1..4)
void word_out(int word_in[]) {
  digitalWrite(pin_p0, word_in[0]);
  digitalWrite(pin_p1, word_in[1]);
  digitalWrite(pin_p2, word_in[2]);
  digitalWrite(pin_p3, word_in[3]);
}

// read all 4 input pins (s1..4)
void read_all(int data_word[]) {
  data_word[0] = digitalRead(pin_s1);
  data_word[1] = digitalRead(pin_s2);
  data_word[2] = digitalRead(pin_s3);
  data_word[3] = digitalRead(pin_s4);
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

// set the input (p1..4) and output (s1..4) pins
void setup() {
  pinMode(pin_s1, INPUT);
  pinMode(pin_s2, INPUT);
  pinMode(pin_s3, INPUT);
  pinMode(pin_s4, INPUT);
  pinMode(pin_p0, OUTPUT);
  pinMode(pin_p1, OUTPUT);
  pinMode(pin_p2, OUTPUT);
  pinMode(pin_p3, OUTPUT);

  for(int i = 0; i < keyboard_size; i++)
    keyboard_data[i] = 0;

  Serial.begin(31250);
}

int data_in[4] = {0, 0, 0, 0};

int index_temp = 0;

void loop() {
  for(int i = 0; i < 6; i++) {
    word_out(data[i]);
    delay(period_ms);
    read_all(data_in);
    for(int j = 0; j < 4; j++) {
      index_temp = i * 4 + j;
      if(keyboard_data[index_temp] != data_in[j]) {
        keyboard_data[index_temp] = data_in[j];
      }
    }
    delay(period_ms);
  }
  word_out(data[6]);
  delay(period_ms);
  read_all(data_in);
  index_temp = 6 * 4;
  if(keyboard_data[index_temp] != data_in[0]) {
    keyboard_data[index_temp] = data_in[0];
  }
  delay(period_ms);
  for(int i = 7; i < 10; i++) {
    word_out(data[i]);
    delay(period_ms);
    read_all(data_in);
    for(int j = 0; j < 4; j++) {
      index_temp = i * 4 + j - 3;
      if(keyboard_data[index_temp] != data_in[j]) {
        keyboard_data[index_temp] = data_in[j];
      }
    }
    delay(period_ms);
  }
  print_all();
}
