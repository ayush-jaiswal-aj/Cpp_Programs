from openai import OpenAI

client = OpenAI(api_key="your_openai_key") # Replace with your actual API key

def ask_chatgpt(question):
    try:
        response = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "user", "content": question}
            ],
            max_tokens=150,
            temperature=0.7
        )
        return response.choices[0].message.content.strip()
    except Exception as e:
        return f"Error: {e}"

def main():
    print("Ask ChatGPT (type 'exit' to quit):\n")
    while True:
        question = input("You: ")
        if question.lower() in ["exit", "quit"]:
            print("Goodbye!")
            break
        answer = ask_chatgpt(question)
        print(f"ChatGPT: {answer}\n")

if __name__ == "__main__":
    main()
