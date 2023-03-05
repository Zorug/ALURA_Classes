# -*- coding: utf-8 -*-
import csv

def carregar_acessos():
    
    X = [] # dados, valores que temos
    Y = [] # marcacoes, valores que queremos calcular
    
    arquivo = open('acesso.csv', 'rt')
    leitor = csv.reader(arquivo)
    
    next(leitor) # faz jogar fora a primeira linha
    
    for home, como_funciona, contato, comprou in leitor:
        
        X.append([int(home), int(como_funciona), int(contato)])
        Y.append(int(comprou))
        
    return X, Y

def carregar_buscas():
    
    X = []
    Y = []
    arquivo = open('busca.csv', 'rt')
    leitor = csv.reader(arquivo)
    next(leitor)
    for home,busca,logado,comprou in leitor:
        dado = [int(home), busca, int(logado)]
        X.append(dado)
        Y.append(int(comprou))
        
    return X,Y