# -*- coding: utf-8 -*-
"""
Created on Wed Mar 13 15:58:52 2019

@author: zorug
"""

class Data:
    
    def __init__(self, dia, mes, ano):
        self.dia = dia
        self.mes = mes
        self.ano = ano
        
    def formatada(self):
        print("{}/{}/{}".format(self.dia, self.mes, self.ano))