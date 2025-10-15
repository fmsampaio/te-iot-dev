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
    'AMANDA SCHEIDT',
    'ANDRE DE CONTO NETO',
    'ANITA AMABILE DE BONA',
    'ARTHUR ALF VARELA',
    'AUGUSTO MACIEL FERREIRA',
    'DAVI BAZZANELLA KUHN',
    'EMANUELLE AMARAL SEBEN',
    'GABRIEL DE SOUSA DRACZESKI',
    'GUILHERME GAMA DA SILVA',
    'GUSTAVO DE OLIVEIRA TURCHETTO',
    'GUSTAVO ORNAGHI COUSSEAU',
    'HELIO BORSTMANN NETO',
    'JULIA BARCELOS ALMEIDA',
    'KAIO MANFRO DA SILVA',
    'LARA CANALI DE LIMA',
    'LETÍCIA GONÇALVES SKOREK',
    'MATEUS JUNGES DE SOUZA',
    'MAYSSON PICOLI',
    'MIGUEL FREITAS DA ROSA',
    'MIGUEL MOURA TERNES BAEZ',
    'PEDRO AUGUSTO BARTELLE',
    'VINICIUS DE OLIVEIRA REGNER',
    'YASMIM SACOL BITENCOURT',
    'YURI IVAN ALTHAUS',
    'YURI WITT KOVALEVICH',
]

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    # Set Connecting Client ID
    client = mqtt_client.Client(client_id)
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