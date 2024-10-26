const SALT_SIZE = 16;
const MAX_INPUT_SIZE = 512;
const OUTPUT_SIZE = 32;

alert("don't work, may crash");

const crypt4re5 = {
    getSalt: function (salt) {
        let a = salt.length;
        for (let i = 0; i < a; i++) {
            let b = salt.charCodeAt(i);
            a += (b % 2 === 0) ? b : -b;
        }
        return (a < 0) ? -a : a % 10;
    },

    crypt: function (output, _text, _salt) {
        let salt = "";
        let text = "";

        let outputHash = "";

        // Check for input arguments
        if (_text.length >= MAX_INPUT_SIZE) {
            console.log(`Input text length is too large: expected between 1 to ${MAX_INPUT_SIZE - 1} chars`);
            return;
        }
        text = _text;
        if (text.length === 0) {
            console.log("Please enter a valid text to crypt");
            return;
        }
        
        // If the salt argument is provided but empty, or if it's not provided, use `text` as the salt
        let saltInt;
        if (_salt && _salt.length > 0) {
            if (_salt.length >= SALT_SIZE) {
                return;
            }
            salt = _salt; // Copy provided salt
            saltInt = this.getSalt(salt);
        } else {
            saltInt = this.getSalt(text); // Use text as salt if salt is empty or not provided
        }
        
        let running = true;
        while (running) {
            for (let i = 0; i < text.length - 1; i += 2) {
                let char1 = text[i];
                let char2 = (i + 1 < text.length) ? text[i + 1] : "";

                let transformedChar = (i + outputHash.length + char1.charCodeAt(0) + (char2 ? char2.charCodeAt(0) : 0)) + saltInt;
                
                // Ensure the transformed character is within ASCII 20 to 126
                while (transformedChar > 126 || transformedChar <= 32) {
                    transformedChar -= 106;
                }
                let newChar = String.fromCharCode(transformedChar);
                
                if (outputHash.length < OUTPUT_SIZE - 1) {
                    outputHash += newChar;
                } else {
                    running = false;
                    break;
                }
            }
        }

        // Output the result
        output = outputHash;
        console.log(output); // Log the result to the console
    }
};

// Usage example
let result = "";
crypt4re5.crypt(result, "exampleText", "exampleSalt");
