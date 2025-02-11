# GyroscopeDrawing
예찬이가 부탁한 아두이노 (자이로스코프로 그림 그리기)

# 사용 물품
- 아두이노 프로 마이크로 5V/16MHz(Arduino Promicro Atmega32u4)
- 아두이노 기울기센서(9축 가속도+자이로+지자기) MPU-9250

# 보드 연결
- `Atmega32u4(레오나르도)`와 `MPU-9250`를 [I2C 통신](https://blog.naver.com/dkwltmdgus/220771950093)으로 연결
1. VCC와 GND를 각각 연결
2. SDA를 2번 핀으로 연결
3. SCL을 3번 핀으로 연결
