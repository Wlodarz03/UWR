from sqlalchemy import create_engine, Column,Integer,String,ForeignKey
from sqlalchemy.orm import declarative_base,relationship,sessionmaker
import argparse
import sys

Base = declarative_base()

class Ksiazka(Base):
    __tablename__ = 'ksiazki'

    id = Column(Integer, primary_key=True)
    tytul = Column(String,primary_key=False)
    autor = Column(String,primary_key=False)
    rok = Column(Integer, primary_key=False)
    znajomy_id = Column(Integer, ForeignKey('znajomi.id'))
    znajomy = relationship('Znajomi', back_populates='ksiazki')

class Znajomi(Base):
    __tablename__ = 'znajomi'

    id = Column(Integer, primary_key=True)
    imie = Column(String, primary_key=False)
    email = Column(String,primary_key=False)
    books = relationship('Ksiazka', back_populates='znajomi')


engine = create_engine('sqlite:///library.db', echo=True)
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
session = Session()

def add_book(tytul,autor,rok):
    new_book = Ksiazka(tytul=tytul, autor=autor, rok=rok)
    session.add(new_book)
    session.commit()
    session.flush()
    print(f"Książka dodana: {tytul} - {autor} ({rok})")

def borrow_book(book_id, imie, email):
    borrower = session.query(Znajomi).filter_by(email=email).first()

    if not borrower:
        borrower = Znajomi(imie=imie,email=email)
        session.add(borrower)

    book = session.query(Ksiazka).filter_by(id=book_id, znajomy_id=None).first()
    if book:
        book.znajomy = borrower
        session.commit()
    else:
        print(f"Książka wypożyczona: {book.tytul} - {book.autor} ({book.rok}) przez {borrower.imie}")

def return_book(book_id):
    book = session.query(Ksiazka).filter_by(id=book_id).first()

    if book and book.znajomy:
        imie = book.znajomy.imie
        book.znajomy = None
        session.commit()
        print(f"Książka zwrócona: {book.tytul} - {book.autor} ({book.rok}) przez {imie}")
    else:
        print("Książka nie jest wypożyczona lub nie istnieje.")

def main():
    parser = argparse.ArgumentParser(description='Zarządzaj biblioteką.')

    parser.add_argument('command', choices=['add', 'borrow', 'return'], help='Dostępne komendy: add, borrow, return')

    args = parser.parse_args(sys.argv[1:2])

    if args.command == 'add':
        parser_add = argparse.ArgumentParser(description='Dodaj nową książkę.')
        parser_add.add_argument('--tytul', required=True, help='Tytuł książki.')
        parser_add.add_argument('--autor', required=True, help='Autor książki.')
        parser_add.add_argument('--rok', required=True, type=int, help='Rok wydania książki.')
        args_add = parser_add.parse_args(sys.argv[2:])
        add_book(args_add.tytul, args_add.autor, args_add.rok)

    elif args.command == 'borrow':
        parser_borrow = argparse.ArgumentParser(description='Wypożycz książkę.')
        parser_borrow.add_argument('--book_id', required=True, type=int, help='ID książki do wypożyczenia.')
        parser_borrow.add_argument('--imie', required=True, help='Imię wypożyczającego.')
        parser_borrow.add_argument('--email', required=True, help='Email wypożyczającego.')
        args_borrow = parser_borrow.parse_args(sys.argv[2:])
        borrow_book(args_borrow.book_id, args_borrow.imie, args_borrow.email)

    elif args.command == 'return':
        parser_return = argparse.ArgumentParser(description='Oddaj książkę.')
        parser_return.add_argument('--book_id', required=True, type=int, help='ID książki do oddania.')
        args_return = parser_return.parse_args(sys.argv[2:])
        return_book(args_return.book_id)


if __name__ == "__main__":
    main()