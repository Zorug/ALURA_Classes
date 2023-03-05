#rb para leitura binaria e wb para escrita binaria
logo = open('python-logo.png', 'rb')
data = logo.read()
logo.close()

logo2 = open('ptyhon-logo2.png', 'wb')
logo2.write(data)
logo2.close()
