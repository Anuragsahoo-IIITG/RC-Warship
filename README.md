## Why I Built It  

Building this RC warship was the perfect project to merge my passions for **naval history, model building, and electronics**.  

I’ve always been fascinated by detailed ships in games like *Assassin’s Creed IV: Black Flag* and movies like *Pirates of the Caribbean*, where naval battles and futuristic mechanisms spark the imagination. That inspiration, combined with my engineering curiosity, pushed me to go beyond making a static replica—I wanted a **fully operational, remote-controlled warship**.  

My goal was to turn that curiosity into a **hands-on learning experience** and an **entry point into microcontrollers and wireless communication**. Along the way, I explored and learned:  

- **Electronics & Programming** – Controlling motors and servos with an Arduino, and setting up wireless communication with nRF modules.  
- **Propulsion Systems** – Using dual motors for both thrust and steering, while managing speed and direction precisely.  
- **Waterproofing** – A critical challenge. My first attempt with cheap motors failed after only 15 minutes, even with hot-glue sealing. That failure taught me the importance of proper component selection and protection.  
- **RC Transmitter Design** – Building a custom transmitter with joysticks and potentiometers for responsive, intuitive control.  

The most rewarding moment was watching everything—mechanical build, wiring, and code—come together into a **dynamic, functional RC warship**. This project not only gave me a working model but also marked the beginning of my journey into **embedded systems and practical electronics**.  


## 📡 How I Made the Remote  

Designing the **remote control** was as exciting as building the warship itself, because it meant creating an interface that felt **intuitive and reliable**—just like a real ship’s control system. Instead of buying an RC transmitter, I challenged myself to **build one from scratch**, which gave me complete freedom over the layout and functionality.  

---

### 🔹 Why I Started with the Remote  
The documentation begins with the **remote** because that’s how this entire project started.  
My first success was getting **two nRF24L01 modules** (one on the remote, one on the boat) to send and receive basic joystick data (0–1023 values).  

- At first, these values were just **proof of communication**.  
- Later, they became **critical control signals**:  
  - **Motor Speed** → mapped from joystick forward/back values.  
  - **Gun Angle** → mapped from joystick side/up-down values.  
  - **Gun Fire Command** → triggered by pressing the joystick button (yes, this fired the Orbeez cannon 😆).  

That very first “**Fire!**” moment really felt like being a pirate captain giving the order.  

---

### 🔹 Electronics & Structure of the Remote  

At the core of the remote is an **Arduino Nano**, paired with an **nRF24L01 wireless module** (mounted on an adapter with capacitors for stable power). This enabled **low-latency real-time communication** at 2.4 GHz.  

**Main Input System**:  
- **Dual Joysticks**  
  - Left joystick → forward/reverse thrust + differential turning (controls left/right motors).  
  - Right joystick → controls the Orbeez gun (left/right aim, up/down tilt).  
  - Right joystick button → Fire command.  
- **Power Supply** → A 9V battery in a holder.  
- **Custom Enclosure** → Instead of 3D printing, I recycled a Flipkart box:  
  - Openings cut out for joysticks.  
  - A small window for the Arduino Nano’s LED.  
  - Space left for the nRF antenna to stick out.  

**Structural Reinforcement**:  
- Small breadboard in the center for wiring.  
- Thermocol blocks placed under joysticks (to prevent collapsing while pressing).  
- Double-sided tape for mounting.  
- Entire box sealed into a **sturdy DIY controller**.  

---

### 🔹 Software & Communication  

The transmitter software continuously:  
1. Reads joystick + button values.  
2. Converts them into digital signals.  
3. Sends packets wirelessly via the **nRF24L01**.  

On the **boat side**:  
- Another Arduino Nano receives these packets.  
- Values are converted into **motor speeds** and **servo angles** in real-time.  

👉 Full code is available here:  
- **[Transmitter Code]()**  
- **[Receiver Code]()**  

*(Links can be added once you upload your code files to the repo.)*  

---

### 🔹 Challenges & Fixes  

One of the toughest parts was ensuring **stable wireless communication**.  

- **Problem:** Frequent signal drops and interference in the 2.4 GHz band.  
- **Fixes:**  
  - Used an **nRF adapter with capacitors** to prevent power brownouts.  
  - Selected a **stable RF channel** to avoid cross-interference.  

After these fixes, the remote became **reliable enough for smooth outdoor operation**.  

---
