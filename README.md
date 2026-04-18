# doseguardian-intelligent-pill-assistant
Embedded system for medication reminders using LPC2148, featuring RTC, LCD display, keypad input, and alert system.

# 💊 DoseGuardian: Intelligent Pill-Taking Assistant (LPC2148)

---

## 📌 Project Description

**DoseGuardian** is an embedded system project developed using the **LPC2148 ARM7 microcontroller**.
It helps users take medicines on time by providing **RTC-based alerts**, using a **16×2 LCD**, **keypad**, **buzzer**, and **LED indicators**.

This system ensures better medication adherence by notifying users and tracking whether medicine is taken or missed.

---

## 🧠 Key Features

* ⏰ Real-Time Clock (RTC) based timing
* 📟 16×2 LCD display interface
* 🔢 4×4 Matrix Keypad input
* 🔔 Buzzer alert for medicine time
* 💡 LED indication for missed dose
* ✅ Medicine taken confirmation
* ❌ Medicine missed detection
* 🧭 Menu-driven user interface

---

## 🛠️ Hardware Components

* LPC2148 ARM7 Microcontroller
* RTC (Internal RTC Module)
* 16×2 LCD Display
* 4×4 Matrix Keypad
* Buzzer
* LED
* Push Buttons / Switches
* Power Supply

---

## 🧪 Software Tools Used

* 🖥️ Keil µVision (Embedded C Programming)
* 🔌 Proteus (Simulation) *(optional)*
* 🌐 GitHub (Version Control)

---

## 🖼️ LCD Output Screens & Explanation

### 🔹 1️⃣ RTC Time Display

```
12:30:45
18/04/2026
```

* Displays real-time clock
* Continuously updates every second ⏱️

---

### 🔹 2️⃣ Main Menu Screen

```
1.RTC  2.MED
3.EXIT
```
<img width="1203" height="820" alt="RTC" src="https://github.com/user-attachments/assets/27a38763-08c8-4a92-95df-08d03846f2fb" />


* User navigates using keypad
* Used to configure system

---

### 🔹 3️⃣ Medicine Alert

```
TAKE MED NOW
```

* Triggered when RTC time matches medicine time
* 🔔 Buzzer ON
* System waits for user response

---

### 🔹 4️⃣ Medicine Taken Confirmation

```
MED TAKEN
```

* User presses switch
* 🔕 Buzzer OFF
* 💡 LED OFF
* Indicates successful intake ✅

---

### 🔹 5️⃣ Medicine Missed Alert

```
MED MISSED
```

* Triggered if user does not respond
* 🔕 Buzzer OFF
* 🚨 LED ON
* Indicates missed dose ❌

---

## ⚙️ Working Principle

1. System initializes LCD, RTC, keypad, and I/O
2. RTC continuously tracks current time
3. LCD displays time and date
4. User sets:

   * RTC time
   * Medicine schedule
5. System compares current time with set medicine time
6. When matched:

   * LCD shows **"TAKE MED NOW"**
   * Buzzer turns ON
7. User action:

   * Press switch → **MED TAKEN**
   * No response → **MED MISSED**

---

## 🔁 System Flow

1. Power ON 🔌
2. Initialize system
3. Display time & date
4. Wait for user input
5. Check medicine schedule
6. Trigger alert
7. Wait for response
8. Repeat continuously 🔄

---

## 📊 Applications

* 👴 Elderly patient care
* 🏥 Hospitals and clinics
* 🏠 Home medication systems
* 💊 Chronic disease management

---

## 🔮 Future Enhancements

* 📲 IoT-based remote monitoring
* 📩 SMS alerts using GSM
* 📱 Mobile app integration
* 💾 Multiple medicine scheduling

---

## ⚠️ Limitations

* Supports only one medicine schedule
* No remote monitoring
* Manual configuration required

---

## 👨‍💻 Author

**Lingamdinne Anila**

---

## ⭐ Support

If you like this project:

* ⭐ Star the repository
* 🍴 Fork it
* 🛠️ Improve and contribute

---

## 📎 Conclusion

DoseGuardian is a reliable embedded solution for medication reminders.
It ensures timely alerts and helps users maintain proper medication routines using simple and effective hardware.
