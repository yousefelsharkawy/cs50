from cs50 import get_string
text = get_string("Text: ")
text = text.lower()
letters = 0
sentences = 0
words = 1
for i in range(len(text)):
    if text[i] >= 'a' and text[i] <= 'z':
        letters += 1
    if text[i] == ' ':
        words += 1
    if text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1
l = (letters * 100) / words
s = (sentences * 100) / words
index = round(0.0588 * l - 0.296 * s - 15.8)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")