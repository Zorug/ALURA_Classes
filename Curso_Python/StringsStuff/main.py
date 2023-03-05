# -*- coding: utf-8 -*-

from ExtratorArgumentosUrl import ExtratorArgumentosUrl

url = 'https://www.bytebank.com.br/cambio?moedaorigem=real&moedadestino=dolar'

#url = "moedaorigem=real&moedadestino=dolar"
# argumento = ExtratorArgumentosUrl(url)

# find

argumentosUrl = ExtratorArgumentosUrl(url)

moedaOrigem, moedaDestino = argumentosUrl.ExtraiArgumentos()
print(moedaDestino, moedaOrigem)

#ExtratorArgumentosUrl.urlEhValida("a")

#index = url.find("moedadestino") + len("moedadestino") +1
#substring = url[index:]
#print(substring)