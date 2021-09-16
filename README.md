
## 目前器材(每組)

---

- arduino uno*1
- sensor sheild V5.0
- L9110(馬達驅動模組)
- HC-SR04P(超音波測距模組)
- TCRT5000(紅外線反射模組)*2
- ADXL345(加速度感測模組)

---

## 目前接線

---

#### `sensor sheild` ➡ `arduino uno`

- `L9110` A1, B1, A2, B2➡`sheild` D9, D10, D5, D6
- `1HC-SR04P` Trig, Echo➡`sheild` D2, D3
- `TCRT5000` A0➡`sheild` A5
- `TCRT5000` A0➡`sheild` A4


![接線](https://imgur.com/aXOJ8iG.png)

---

## 疑問

---

ADXL345欲使用IIC連接至sensor sheild(SDA➡SDA, SCL➡SCL)，在uno上是幾號針腳?

---

## 需求 

---

將adxl345送到Serial(序列阜)的資料透過無線(wifi或藍芽)傳出，或是利用sd卡儲存資料
    
1. 在snesor sheild上的bluetooth區接上藍芽模組是否能將資料傳出?(請推薦模組)
2. 透過wifi傳輸資料(請推薦方案)。

