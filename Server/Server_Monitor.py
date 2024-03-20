import socket
import threading
import datetime
import subprocess

def handle_client(client_socket):
    # Ottieni l'indirizzo IP del client
    client_address = client_socket.getpeername()[0]

    try:
        # Ottieni il nome host associato all'indirizzo IP
        client_hostname, _, _ = socket.gethostbyaddr(client_address)
    except socket.herror:
        # Se non è possibile ottenere il nome host, assegna un valore di default
        client_hostname = "Unknown"

    # Registra le informazioni su un file
    with open('connections.txt', 'a') as file:
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        file.write(f"{timestamp} - Host: {client_hostname}, IP: {client_address}\n")

    # Visualizza le informazioni su console
    print(f"Connection from {client_hostname} ({client_address})")

    # Chiudi la connessione
    client_socket.close()

def switchcase(temp):
    cases={
        "black":"https://www.decathlon.it/p/t-shirt-uomo-fitness-adidas-regular-100-cotone-nera/_/R-p-X8809000?mc=8809000",
        "white":"https://www.decathlon.it/p/t-shirt-uomo-fitness-adidas-regular-cotone-bianca/_/R-p-X8808981?mc=8808981",
        "fitness":"Image/fitness.png",
        "sneaker":"https://www.decathlon.it/search?Ntt=sneaker",
        "running":"Image/running.png",
        "red":"https://www.decathlon.it/p/mp/puma/sneaker-basse-rebound-v6-puma-black-pink-lilac-white/_/R-p-3025c13e-d906-43a8-aab2-c3278f42192d?mc=3025c13e-d906-43a8-aab2-c3278f42192d_c4.c1.c14",
        "pink":"https://www.decathlon.it/p/mp/puma/sneaker-rebound-v6-lo-da-ragazzi-puma-black-shadow-gray/_/R-p-1cb3f02a-20b3-4328-aa7f-9f16f642e509?mc=1cb3f02a-20b3-4328-aa7f-9f16f642e509_c4.c24",
        "shirt":"https://www.decathlon.it/search?Ntt=shirt"
    }
    return cases.get(temp,"default")


def start_server():
    # Configura il server
    host = '192.168.1.45'
    port = 8080

    # Crea un socket TCP/IP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
    # Collega il socket all'indirizzo e alla porta specificati
    server_socket.bind((host, port))

    # Accetta al massimo 5 connessioni in coda
    server_socket.listen(5)

    print(f"Server in ascolto su {host}:{port}")

    # Loop principale del server
    while True:
        # Accetta la connessione dal client
        client_socket, addr = server_socket.accept()
        data = client_socket.recv(1024)
        if not data:
        	break
        print(f"Ricevuto da {addr}: {data.decode('utf-8')}")
       
       #richiama la funzione switchcase
        temp=data.decode('utf-8')
        url=switchcase(temp)
        
        subprocess.run(["start", "", url], check=True, shell=True)
        # Gestisci il client in un thread separato
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    # Avvia il server
    start_server()
