import random

# Generate 256 random 8-bit hex digits
hex_digits = [f"{random.randint(0, 255):02x}" for _ in range(256)]
random_hex_string = ''.join(hex_digits)

print(random_hex_string)