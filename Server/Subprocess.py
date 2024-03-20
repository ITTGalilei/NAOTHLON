import subprocess

def open_webpage(url):
    try:
        subprocess.run(["start", "", url], check=True, shell=True)
    except subprocess.CalledProcessError as e:
        print(f"Errore durante l'apertura della pagina: {e}")

if __name__ == "__main__":
    # Sostituisci con l'URL che vuoi aprire
    webpage_url = "https://www.example.com"
    
    # Apri la pagina web nel browser
    open_webpage(webpage_url)
