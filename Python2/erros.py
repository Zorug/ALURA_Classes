from models import *
try:
    arquivo = open('perfis.csv', 'r')
    valores = arquivo.readline().split(':')
    Perfil(*valores)
    print('arquivo foi aberto')
    arquivo.close
except (IOError, TypeError) as erro:
    print('Deu erro %s' % erro)
