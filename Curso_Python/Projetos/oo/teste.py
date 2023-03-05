# -*- coding: utf-8 -*-
"""
Created on Fri Mar  8 10:15:39 2019

@author: Sorug
"""

def cria_conta(numero, titular, saldo, limite):
    conta = {"numero": numero, "titular": titular, "saldo": saldo, "limite": limite}
    return conta

def deposita(conta, valor):
    conta["saldo"] += valor
    
def saca(conta, valor):
    conta["saldo"] -= valor
    
def extrato(conta):
    print("Saldo é {}".format(conta["saldo"]))