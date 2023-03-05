# -*- coding: UTF-8 -*-
import re


def cadastrar(nomes): #1
    print 'Digite: o nome:'
    nome = raw_input()
    nomes.append(nome)


def listar(nomes): #2
    print 'Listando nomes:'
    for nome in nomes:
        print nome


def remover(nomes): #3
    print 'Qual nome gostaria de remover?'
    nome = raw_input()
    nomes.remove(nome)


def alterar(nomes): #4
    print 'Qual nome vc gostaria de alterar?'
    nome_a_alterar = raw_input()

    if nome_a_alterar in nomes:
        posicao = nomes.index(nome_a_alterar)
        print 'Digite novo nome:'
        nome_novo = raw_input()
        nomes[posicao] = nome_novo


def procurar(nomes): #5
    print 'Digite nome a procurar:'
    nome = raw_input()

    if(nome in nomes):
        print 'Nome %s está cadastrado' % (nome)
    else:
        print "Nome %s não está cadastrado" % (nome)


def procurar_regex(nomes):#6
    print('Digite a expressão regular')
    regex = raw_input()
    nomes_concatenados = ' '.join(nomes)
    resultados = re.findall(regex, nomes_concatenados)
    print(resultados)


def menu():
    nomes = []
    escolha = ''
    while(escolha != '0'):
        print 'Digite 1 para cadastrar, 2 para listar, 3 para remover, 4 para alterar um nome, 5 para verificar nome, 6... ou 0 para terminar'
        escolha = raw_input()

        if(escolha == '1'):
            cadastrar(nomes)

        if(escolha == '2'):
            listar(nomes)

        if(escolha == '3'):
            remover(nomes)

        if(escolha == '4'):
            alterar(nomes)

        if(escolha == '5'):
            procurar(nomes)

        if(escolha == '6'):
            procurar_regex(nomes)

menu()
