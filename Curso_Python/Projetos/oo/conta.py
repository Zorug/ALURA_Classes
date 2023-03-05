# -*- coding: utf-8 -*-
"""
Created on Fri Mar  8 18:58:46 2019

@author: Sorug
"""

class Conta:
    
    def __init__(self, numero, titular, saldo, limite):
        print("construindo objeto ... {}".format(self))
        self.__numero = numero #underscore apenas a partir da classe pode ser modificado
        self.__titular = titular #isso se chama encapsulamento
        self.__saldo = saldo
        self.__limite = limite
        
    def extrato(self):
        print("Saldo de {} do titular {}".format(self.__saldo, self.__titular))
        
    def deposita(self, valor):
        self.__saldo += valor
        
    def saca(self, valor):
        if(valor <= (self.__saldo + self.__limite)):
            self.__saldo -= valor
        else:
            print("O valor {} passou o limite".format(valor))
        
    def transfere(self, valor, destino):
        self.saca(valor)
        destino.deposita(valor)
        
    def get_saldo(self):
        return self.__saldo
    
    def get_titular(self):
        return self.__titular
    
    @property
    def limite(self):
        return self.__limite
    
    @limite.setter
    def limite(self, limite):
        self.__limite = limite