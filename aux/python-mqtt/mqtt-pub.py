from paho.mqtt import client as mqtt_client
import random
import time

broker = 'm14.cloudmqtt.com'
port = 12891
topicTurma = 'te/turma'
topicTempo = 'te/temperatura'
client_id = f'python-mqtt-{random.randint(0, 1000)}'
username = 'vqlvmcfj'
password = 'Vzw6NIX4voxY'

delay = 3

baseTemp = 18.0

alunos = [
    'ANA LAURA BARBIERI JUM',
    'ANGELA REGINATTO BENVENUTI',
    'ARTHUR FARIAS ZANETI',
    'AUGUSTO CARRER HERPICH',
    'BRYAN RIBEIRO MELO',
    'CAMILE FERREIRA PEDROLO',
    'CAMILE WEBER',
    'CASSIANO JOSÉ SOBIERAI',
    'ERICA MARTINS',
    'ÉRICK SANTOS MATOS',
    'GUILHERME THOMAS DA COSTA',
    'JADINA BRUMMELHAUS CABRERA',
    'LUCAS DE CESERO CHEROBIN',
    'LUCAS ZANELLA',
    'MARCELLA SOUZA LOPES',
    'MATEUS ZUCCO',
    'NATÁLIA MULLER ABICH',
    'NÍCOLAS LANFREDI BOTTIN',
    'PAMELA MARIA DA SILVA',
    'PEDRO HENRIQUE DAVID ZAZYKI',
    'RAFAEL BORGES GRAUNKE',
    'RAFAELA MIRAILH ZANIN',
    'VITORIA HAMMES MEDEIROS',
    'WILLIAM GABRIEL FILIPPI',
]

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    # Set Connecting Client ID
    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
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