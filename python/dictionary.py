# need to install requests module
# open terminal on vs code and run:
# pip install requests

import requests

def get_definition(word):
    url = f"https://api.dictionaryapi.dev/api/v2/entries/en/{word}"  #free dictionary api
    try:
        response = requests.get(url, timeout=5)
        if response.status_code == 200:
            data = response.json()
            definition = data[0]["meanings"][0]["definitions"][0]["definition"]
            return definition
        else:
            return "Definition not found."
    except:
        return "Error connecting to dictionary API."

if __name__ == "__main__":
    word = input("Enter a word: ").strip()
    meaning = get_definition(word)
    print(f"\nDefinition of '{word}': {meaning}")
