
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10  // Slave select pin
#define RST_PIN 9   // Reset pin
MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance




#define RELAY_PIN 7 // Pin for the relay module
#define BUTTON_PIN 2 // Pin for the push button

// I2C LCD setup (change address if necessary)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the address if your LCD is different

// Card structure
struct Card {
    long uid;      // Card UID in decimal
    float balance; // Card balance
};

// Authorized cards with their balances
Card authorizedCards[] = {
    {478310163, 50.0}, // Replace with your card's UID and balance
    {410699816, 500.0}   // Another card example
};

const int numCards = sizeof(authorizedCards) / sizeof(authorizedCards[0]);

float currentBalance = 0.0; // Current balance of the scanned card
bool loadState = false; // Track if the load is on or off
unsigned long previousMillis = 0; // Store last deduction time
const long deductionInterval = 60000; // 1 minute
unsigned long chargingStartTime = 0; // Time when charging started
unsigned long chargingDuration = 0; // Total duration of charging in seconds
long lastCardUID = -1; // Track the last scanned card UID
long cardUID = 0;

void setup() {
    Serial.begin(9600);
    SPI.begin(); // Initialize SPI bus
    rfid.PCD_Init(); // Initialize MFRC522
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with pull-up resistor
    digitalWrite(RELAY_PIN, LOW); // Ensure relay is off

    lcd.begin(); // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    lcd.setCursor(0, 0);
    lcd.print("PARK YOUR CAR IN");
    lcd.setCursor(0, 1);
    lcd.print("CHARGING SLOT");

    Serial.println("Scan your card...");
}

void loop() {
    // Check for button press to turn off load
    if (digitalRead(BUTTON_PIN) == LOW) { // Button pressed
        if (loadState) {
            Serial.println("Turning off load...");
            digitalWrite(RELAY_PIN, LOW); // Turn relay OFF
            loadState = false; // Update load state
            displaySummary(); // Show total amount and time on LCD
        }
        delay(200); // Simple debounce delay
    }

    // Check for new cards
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        // Reset cardUID for each new card
        cardUID = 0;

        // Read UID
        for (byte i = 0; i < rfid.uid.size; i++) {
            cardUID = cardUID * 128 + rfid.uid.uidByte[i]; // Convert to decimal
        }

        // Print scanned UID in decimal
        Serial.print("Scanned UID (Decimal): ");
        Serial.println(cardUID);

        // Update LCD display with the card UID
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Balance: ");
        lcd.print(currentBalance);
        

        // Find the card in authorized cards
        for (int i = 0; i < numCards; i++) {
            if (authorizedCards[i].uid == cardUID) {
                // If the same card is scanned again, continue from the current balance
                if (loadState && cardUID == lastCardUID) {
                    Serial.println("Resuming previous session.");
                } else {
                    // Initialize or reset balance if a new card is scanned
                    currentBalance = authorizedCards[i].balance;
                    Serial.print("Card Found! Starting Balance: ");
                    Serial.println(currentBalance);

                    // Turn on the load
                    if (!loadState) {
                        Serial.println("Turning on load...");
                        digitalWrite(RELAY_PIN, HIGH); // Turn relay ON
                        loadState = true;
                        chargingStartTime = millis(); // Record start time
                        previousMillis = millis(); // Set initial deduction time
                    }
                }

                // Update the last scanned card UID
                lastCardUID = cardUID;
                break; // Exit loop once card is found
            }
        }

        rfid.PICC_HaltA(); // Halt PICC
        rfid.PCD_StopCrypto1(); // Stop encryption on PCD
    }

    // Deduct balance in real-time while load is on
    if (loadState) {
        unsigned long currentMillis = millis();

        // Update charging duration every second
        chargingDuration = (currentMillis - chargingStartTime) / 1000; // Convert to seconds

        // Check if one minute has passed for balance deduction
        if (currentMillis - previousMillis >= deductionInterval) {
            previousMillis = currentMillis; // Update previousMillis for next interval

            // Deduct 1 from the current balance
            if (currentBalance > 0) {
                currentBalance -= 1; // Deduct from balance
                Serial.print("Balance deducted. New Balance: ");
                Serial.println(currentBalance);

                // Update authorized card balance
                for (int i = 0; i < numCards; i++) {
                    if (authorizedCards[i].uid == lastCardUID) {
                        authorizedCards[i].balance = currentBalance; // Update balance
                        break;
                    }
                }
            } else {
                Serial.println("Balance is zero. Turning off load...");
                digitalWrite(RELAY_PIN, LOW); // Turn relay OFF
                loadState = false; // Update load state

                // Update LCD display
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Balance: 0");
                lcd.setCursor(0, 1);
                lcd.print("Load OFF");
                return; // Exit loop
            }
        }

        // Calculate hours, minutes, and seconds
        unsigned long hours = chargingDuration / 3600;
        unsigned long minutes = (chargingDuration % 3600) / 60;
        unsigned long seconds = chargingDuration % 60;

        // Update LCD with current balance and charging time
        lcd.setCursor(9, 0); // Move cursor to update balance
        lcd.print(currentBalance);
        lcd.print("   "); // Extra spaces to clear previous digits

        lcd.setCursor(0, 1); // Move cursor to update time
        lcd.print("Time: ");
        lcd.print(hours);
        lcd.print("h ");
        lcd.print(minutes);
        lcd.print("m ");
        lcd.print(seconds);
        lcd.print("s "); // Show charging duration
    }
}

void displaySummary() {
    // Display the total amount and time on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total Amount: ");
    lcd.print(currentBalance);
    lcd.setCursor(0, 1);
    
    unsigned long hours = chargingDuration / 3600;
    unsigned long minutes = (chargingDuration % 3600) / 60;
    unsigned long seconds = chargingDuration % 60;

    lcd.print("Time: ");
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("m ");
    lcd.print(seconds);
    lcd.print("s"); // Show charging duration
    delay(5000);

    // Reset display to initial message
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PARK YOUR CAR IN ");
    lcd.setCursor(0, 1);
    lcd.print("CHARGING SLOT ");
} 
