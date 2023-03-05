# -*- coding: utf-8 -*-
"""
Created on Fri Mar  1 18:26:36 2019

@author: Sorug
"""
import forca
import adivinhacao

print('********************************')
print('******Escolhe o seu jogo!*******')
print('********************************')

print('(1) Forca (2) Adivinhação')

jogo = int(input('Qual jogo?'))

if(jogo == 1):
    print('jogando forca')
    forca.jogar()
elif(jogo == 2):
    print('jogando adivinhação')
    adivinhacao.jogar()