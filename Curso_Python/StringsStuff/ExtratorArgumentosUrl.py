# -*- coding: utf-8 -*-

class ExtratorArgumentosUrl:
    def __init__(self,url):
        if self.urlEhValida(url):
            self.url = url
        else:
            raise LookupError("Url inválida!!!")
        
    @staticmethod #este método é estático, não é mais necessário o self
    def urlEhValida(url):
        if url:
            return True
        else:
            return False
        
    def ExtraiArgumentos(self):
        
        buscaMoedaOrigem    = 'moedaorigem'
        buscaMoedaDestino   = 'moedadestino'
        
        indiceInicialMoedaDestino     = self.url.encontraIndiceInicial(buscaMoedaDestino)
        
        indiceInicialMoedaOrigem    = self.url.encontraIndiceInicial(buscaMoedaOrigem)
        indiceFinalMoedaOrigem      = self.url.find('&')
        
        moedaOrigem = self.url[indiceInicialMoedaOrigem:indiceFinalMoedaOrigem]
        moedaDestino = self.url[indiceInicialMoedaDestino:]
        
        return moedaOrigem, moedaDestino
    
    def encontraIndiceInicial(self,moedaBuscada):
        return self.url.find(moedaBuscada) + len(moedaBuscada) +1