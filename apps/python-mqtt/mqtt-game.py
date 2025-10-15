from paho.mqtt import client as mqtt_client
import random
import time

""" Plano A => Tyckr MQTT IO """
broker = 'mqtt.tyckr.io'
port = 1883

""" Plano B => Bevywise MQTT HQ """
# broker = 'public-mqtt-broker.bevywise.com'
# port = 1883

topic = 'te/game'
client_id = f'python-mqtt-{random.randint(0, 2000)}'

targetNumber = random.randint(0, 1000)

def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            #print("Connected to MQTT Broker!")
            print("JOGO INICIADO!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    #client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        #print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        counter = 0
        try:
            guess = int(msg.payload.decode())
            if(guess < targetNumber):
                print(f"[DICA] O valor alvo é MAIOR que {guess}")
            elif(guess > targetNumber):
                print(f"[DICA] O valor alvo é MENOR que {guess}")
            else:
                print(f"Valor CORRETO! --> {guess}!")
                print("JOGO TERMINADO!")
                exit()
        
        except ValueError:
            counter += 1

            #print('[ERRO] Valor não é um número inteiro.')    

    client.subscribe(topic)
    client.on_message = on_message

def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    
    run()