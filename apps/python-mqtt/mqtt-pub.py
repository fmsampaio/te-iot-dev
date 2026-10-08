from paho.mqtt import client as mqtt_client
import random
import time

""" Plano A => Tyckr MQTT IO """
broker = 'mqtt.tyckr.io'
port = 1883

""" Plano B => Bevywise MQTT HQ """
# broker = 'public-mqtt-broker.bevywise.com'
# port = 1883

topicTurma = 'te/turma'
topicTempo = 'te/temperatura'
client_id = f'python-mqtt-{random.randint(0, 1000)}'

delay = 3

baseTemp = 18.0


alunos = [
    'ADRIAN DE LIMA DA ROSA',
    'ALAN BASTOS NADALON',
    'BEATRICE ONZI CAPPELETTI',
    'BRAYAN FERREIRA DA CRUZ',
    'BRUNO CAMPEOL BARTELLE',
    'CAIO MIGUEL CALGAROTTO',
    'CARLOS LEANDRO GOULART DOS SANTOS JUNIOR',
    'DIONATAN PIMENTEL SCHINEIDER',
    'GABRIELLY WAGNER GROTH',
    'GERMANO HENDGES PEREIRA',
    'JOANA ALBERTI DE LIMA',
    'JOAO VITOR FAE MANICA',
    'JOÃO VÍTOR MAIOLI MARMENTINI',
    'KALINDI GOJTEJ RIBEIRO',
    'LUCAS BERTOLETTI PAESE',
    'LUCAS SEHN FRITSCH',
    'LUIZA PERINI CAPRINI',
    'MARCO ANTONIO FERRARI',
    'MARIANA CARBONARI DE PIZZOL',
    'MATHEUS ABREU JABLONSKI',
    'NAIARA FARDO RIBOLDI',
    'RAFAELA PEROTTONI ROSSATO',
    'RAMIRO DE MORAIS SEVERGNINI',
    'RONALDO DA SILVA BISOGNIN FILHO',
    'SADY ANTONIO COSTAMILAN NETO',
    'SUÉLEN CARNEIRO FEIJÓ',
    'VICTOR HUGO KLIPEL',
    'VICTORIA PALAVRO LUNARDI',
    'VINICIUS HENRIQUE SANTOS DA SILVA',
    'VITOR DE CESERO TREVISAN',
    'YURI ALEXANDRE GUELSO SANTOS'
]

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    # Set Connecting Client ID
    client = mqtt_client.Client(
        mqtt_client.CallbackAPIVersion.VERSION1,
        client_id=client_id
    )
    #client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def publishMsg(topic, msg):
    result = client.publish(topic, msg)
    
    # result: [0, 1]
    status = result[0]
    if status == 0:
        print(f"Send `{msg}` to topic `{topic}`")
    else:
        print(f"Failed to send message to topic {topic}")

def publishTurma(client):  
    msg = alunos[random.randint(0, len(alunos)-1)]
    publishMsg(topicTurma, msg)    
    
def publishTemperatura(client):
    msg = f'{(baseTemp + (baseTemp * 0.05 * random.random())):.2f}'
    publishMsg(topicTempo, msg)


if __name__ == "__main__":
    client = connect_mqtt()
    client.loop_start()
    while True:
        time.sleep(delay)
        publishTemperatura(client)
        publishTurma(client)