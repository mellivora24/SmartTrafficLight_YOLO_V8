// Định nghĩa các chân cho đèn giao thông ở 4 hướng
#define RED_1 2
#define GREEN_1 3
#define YELLOW_1 4
#define RED_2 5
#define GREEN_2 6
#define YELLOW_2 7
#define RED_3 8
#define GREEN_3 9
#define YELLOW_3 10
#define RED_4 11
#define GREEN_4 12
#define YELLOW_4 13

// Hằng số thời gian (đơn vị: mili giây)
const int YELLOW_TIME = 3000;    // Thời gian đèn vàng: 3 giây
const int MIN_GREEN_TIME = 5000; // Thời gian đèn xanh tối thiểu: 5 giây
const int MAX_GREEN_TIME = 30000; // Thời gian đèn xanh tối đa: 30 giây

void setup() {
  Serial.begin(9600);
  // Cấu hình các chân là đầu ra
  pinMode(RED_1, OUTPUT); pinMode(GREEN_1, OUTPUT); pinMode(YELLOW_1, OUTPUT);
  pinMode(RED_2, OUTPUT); pinMode(GREEN_2, OUTPUT); pinMode(YELLOW_2, OUTPUT);
  pinMode(RED_3, OUTPUT); pinMode(GREEN_3, OUTPUT); pinMode(YELLOW_3, OUTPUT);
  pinMode(RED_4, OUTPUT); pinMode(GREEN_4, OUTPUT); pinMode(YELLOW_4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int vehicles[4] = {0, 0, 0, 0};
    parseData(data, vehicles);
    led_control(vehicles[0], vehicles[1], vehicles[2], vehicles[3]);
  }
}

// Hàm phân tích dữ liệu
void parseData(String data, int vehicles[]) {
  int index = 0;
  while (data.length() > 0 && index < 4) {
    int commaIndex = data.indexOf(',');
    String part = (commaIndex != -1) ? data.substring(0, commaIndex) : data;
    data = (commaIndex != -1) ? data.substring(commaIndex + 1) : "";
    int colonIndex = part.indexOf(':');
    if (colonIndex != -1) {
      int direction = part.substring(0, colonIndex).toInt();
      int count = part.substring(colonIndex + 1).toInt();
      if (direction >= 1 && direction <= 4) {
        vehicles[direction - 1] = count;
      }
    }
    index++;
  }
}

// Hàm điều khiển đèn giao thông
void led_control(int vehicles1, int vehicles2, int vehicles3, int vehicles4) {
  int total_vehicles = vehicles1 + vehicles2 + vehicles3 + vehicles4;
  if (total_vehicles == 0) return;

  // Tính thời gian đèn xanh
  int green_time1 = constrain((vehicles1 * MAX_GREEN_TIME) / total_vehicles, MIN_GREEN_TIME, MAX_GREEN_TIME);
  int green_time2 = constrain((vehicles2 * MAX_GREEN_TIME) / total_vehicles, MIN_GREEN_TIME, MAX_GREEN_TIME);
  int green_time3 = constrain((vehicles3 * MAX_GREEN_TIME) / total_vehicles, MIN_GREEN_TIME, MAX_GREEN_TIME);
  int green_time4 = constrain((vehicles4 * MAX_GREEN_TIME) / total_vehicles, MIN_GREEN_TIME, MAX_GREEN_TIME);

  // Tính tổng thời gian chu kỳ
  int total_cycle_time = (green_time1 + YELLOW_TIME) + (green_time2 + YELLOW_TIME) + 
                        (green_time3 + YELLOW_TIME) + (green_time4 + YELLOW_TIME);

  // Tính thời gian đèn đỏ
  int red_time1 = total_cycle_time - (green_time1 + YELLOW_TIME);
  int red_time2 = total_cycle_time - (green_time2 + YELLOW_TIME);
  int red_time3 = total_cycle_time - (green_time3 + YELLOW_TIME);
  int red_time4 = total_cycle_time - (green_time4 + YELLOW_TIME);

  // Hiển thị thời gian
  Serial.println("Thoi gian cho tung huong:");
  Serial.print("Huong 1: Den xanh "); Serial.print(green_time1 / 1000); 
  Serial.print(" giay, Den vang "); Serial.print(YELLOW_TIME / 1000); 
  Serial.print(" giay, Den do "); Serial.print(red_time1 / 1000); Serial.println(" giay");

  Serial.print("Huong 2: Den xanh "); Serial.print(green_time2 / 1000); 
  Serial.print(" giay, Den vang "); Serial.print(YELLOW_TIME / 1000); 
  Serial.print(" giay, Den do "); Serial.print(red_time2 / 1000); Serial.println(" giay");

  Serial.print("Huong 3: Den xanh "); Serial.print(green_time3 / 1000); 
  Serial.print(" giay, Den vang "); Serial.print(YELLOW_TIME / 1000); 
  Serial.print(" giay, Den do "); Serial.print(red_time3 / 1000); Serial.println(" giay");

  Serial.print("Huong 4: Den xanh "); Serial.print(green_time4 / 1000); 
  Serial.print(" giay, Den vang "); Serial.print(YELLOW_TIME / 1000); 
  Serial.print(" giay, Den do "); Serial.print(red_time4 / 1000); Serial.println(" giay");

  // Điều khiển đèn
  set_lights(1, green_time1); set_yellow(1);
  set_lights(2, green_time2); set_yellow(2);
  set_lights(3, green_time3); set_yellow(3);
  set_lights(4, green_time4); set_yellow(4);
}

// Hàm bật đèn xanh
void set_lights(int quarter, int green_time) {
  digitalWrite(GREEN_1, LOW); digitalWrite(YELLOW_1, LOW); digitalWrite(RED_1, HIGH);
  digitalWrite(GREEN_2, LOW); digitalWrite(YELLOW_2, LOW); digitalWrite(RED_2, HIGH);
  digitalWrite(GREEN_3, LOW); digitalWrite(YELLOW_3, LOW); digitalWrite(RED_3, HIGH);
  digitalWrite(GREEN_4, LOW); digitalWrite(YELLOW_4, LOW); digitalWrite(RED_4, HIGH);

  switch (quarter) {
    case 1: digitalWrite(RED_1, LOW); digitalWrite(GREEN_1, HIGH); break;
    case 2: digitalWrite(RED_2, LOW); digitalWrite(GREEN_2, HIGH); break;
    case 3: digitalWrite(RED_3, LOW); digitalWrite(GREEN_3, HIGH); break;
    case 4: digitalWrite(RED_4, LOW); digitalWrite(GREEN_4, HIGH); break;
  }
  delay(green_time);
}

// Hàm bật đèn vàng
void set_yellow(int quarter) {
  switch (quarter) {
    case 1: digitalWrite(GREEN_1, LOW); digitalWrite(YELLOW_1, HIGH); break;
    case 2: digitalWrite(GREEN_2, LOW); digitalWrite(YELLOW_2, HIGH); break;
    case 3: digitalWrite(GREEN_3, LOW); digitalWrite(YELLOW_3, HIGH); break;
    case 4: digitalWrite(GREEN_4, LOW); digitalWrite(YELLOW_4, HIGH); break;
  }
  delay(YELLOW_TIME);
  switch (quarter) {
    case 1: digitalWrite(YELLOW_1, LOW); digitalWrite(RED_1, HIGH); break;
    case 2: digitalWrite(YELLOW_2, LOW); digitalWrite(RED_2, HIGH); break;
    case 3: digitalWrite(YELLOW_3, LOW); digitalWrite(RED_3, HIGH); break;
    case 4: digitalWrite(YELLOW_4, LOW); digitalWrite(RED_4, HIGH); break;
  }
}