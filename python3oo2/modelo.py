# -*- coding: utf-8 -*-
"""
Spyder Editor

Este é um arquivo de script temporário.
"""
class Programa: #classe mãe ou superclasse
    def __init__(self, nome, ano):
        self._nome = nome.title() #deixa todas as iniciais maiúsculas
        self.ano = ano
        self._likes = 0
        
    @property
    def likes(self): #torna likes privado
        return self._likes
    
    def dar_like(self):
        self._likes += 1 #pega os likes privados
        
    @property
    def nome(self):
        return self._nome

    @nome.setter
    def nome(self, novo_nome):
        self._nome = novo_nome.title()


    def __str__(self): #retorna uma string
        return f'{self._nome} - {self.ano} - {self._likes} Likes'


class Filme(Programa): #classe filha
    def __init__(self, nome, ano, duracao):
        super().__init__(nome, ano) #chama a classe mãe
        self.duracao = duracao
        
    def __str__(self):
        return f'{self._nome} - {self.ano} - {self.duracao} min - {self._likes} Likes'

class Serie(Programa):
    def __init__(self, nome, ano, temporadas):
        super().__init__(nome, ano)
        self.temporadas = temporadas
        
    def __str__(self):
        return f'{self._nome} - {self.ano} - {self.temporadas} temporadas - {self._likes} Likes'

        
        
class Playlist:
    def __init__(self, nome, programas):
        self.nome = nome
        self._programas = programas
        
    def __getitem__(self, item):
        return self._programas[item]
        
    @property
    def listagem(self):
        return self._programas
    
    def __len__(self):
        return len(self._programas)
    

vingadores = Filme('vingadores - guerra infinita', 2018, 160)
atlanta = Serie('atlanta', 2018, 2)
tmep = Filme('Todo mundo em pânico', 1999, 100)
demolidor = Serie('Demolidor', 2016, 2)

vingadores.dar_like()
tmep.dar_like()
tmep.dar_like()
tmep.dar_like()
tmep.dar_like()
demolidor.dar_like()
demolidor.dar_like()
atlanta.dar_like()
atlanta.dar_like()
atlanta.dar_like()


filmes_e_series = [vingadores, atlanta, demolidor, tmep] #playlist tem uma ordem
playlist_fim_de_semana = Playlist('fim de semana', filmes_e_series)

print(f'Tamanho do playlist: {len(playlist_fim_de_semana)}')



for programa in playlist_fim_de_semana:
    print(programa)
    
#print(f'Tá ou não tá? {demolidor in playlist_fim_de_semana.listagem}')