import requests
import argparse

url = "http://localhost:8080/ksiazki"

def get_ksiazki():
    response=requests.get(url)
    ksiazki=response.json()
    for ksiazka in ksiazki:
        print(f"{ksiazka['id']}: {ksiazka['tytul']} - {ksiazka['autor']} ({ksiazka['rok']})")

def get_ksiazka(ksiazka_id):
    response=requests.get(f"{url}/{ksiazka_id}")
    ksiazka=response.json()
    print(f"{ksiazka['id']}: {ksiazka['tytul']} - {ksiazka['autor']} ({ksiazka['rok']})")

def add_ksiazka(tytul,autor,rok):
    data={"tytul": tytul, "autor": autor, "rok": rok}
    response=requests.post(url,json=data)
    print(response.json()["message"])

def update_ksiazka(ksiazka_id,tytul,autor,rok):
    data = {"tytul": tytul, "autor": autor, "rok": rok}
    response=requests.put(f"{url}/{ksiazka_id}",json=data)
    print(response.json()["message"])

def delete_ksiazka(ksiazka_id):
    response=requests.delete(f"{url}/{ksiazka_id}")
    print(response.json()["message"])

def main():
    parser=argparse.ArgumentParser(description='Zarządzanie książkami')
    subparsers = parser.add_subparsers(dest='command',help='Dostępne polecenia')
    parser_get = subparsers.add_parser('get',help='Pobierz listę książek lub szczegóły książki')
    parser_get.add_argument('--id',type=int, help='ID książki')
    parser_add = subparsers.add_parser('add',help='Dodaj nową książkę')
    parser_add.add_argument('--tytul',required=True, help='Tytuł książki')
    parser_add.add_argument('--autor',required=True, help='Autor książki')
    parser_add.add_argument('--rok',required=True, type=int, help='Rok wydania książki')
    parser_update = subparsers.add_parser('update',help='Zaktualizuj książkę')
    parser_update.add_argument('--id',required=True,type=int,help='ID książki')
    parser_update.add_argument('--tytul',help='Nowy tytuł książki')
    parser_update.add_argument('--autor',help='Nowy autor książki')
    parser_update.add_argument('--rok',help='Nowy rok wydania')
    parser_delete = subparsers.add_parser('delete',help='Usuń książkę')
    parser_delete.add_argument('--id',required=True,type=int,help='ID książki')
    args=parser.parse_args()
    if args.command=='get':
        if args.id:
            get_ksiazka(args.id)
        else:
            get_ksiazki()
    elif args.command=='add':
        add_ksiazka(args.tytul,args.autor,args.rok)
    elif args.command=='update':
        update_ksiazka(args.id,args.tytul,args.autor,args.rok)
    elif args.command=='delete':
        delete_ksiazka(args.id)

if __name__ == '__main__':
    main()