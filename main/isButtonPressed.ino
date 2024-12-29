bool isButtonPressed(int buttonPin) {
    static unsigned long lastPressTime = 0;
    unsigned long currentTime = millis();
    
    if (digitalRead(buttonPin) == LOW && (currentTime - lastPressTime) > 200) {
        lastPressTime = currentTime;
        return true;
    }
    return false;
}
