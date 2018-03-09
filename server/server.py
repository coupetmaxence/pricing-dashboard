#!/usr/bin/env python

import asyncio
import websockets
import subprocess
import json
import requests

async def hello(websocket, path):
    message = await websocket.recv()
    print("< {}".format(message))

    # TODO : check data, etc
    json_file = json.loads(message)
    
    json_data = requests.request('GET', 'https://www.alphavantage.co'+
                        '/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol='+json_file['data']['underlying'][0]+
                        '&apikey=KNZX').json()
    json_string = json.dumps(json_data)

    result = subprocess.run(['../pricer/main', message], stdout=subprocess.PIPE)
    result_message = result.stdout.decode('utf-8')

    await websocket.send(json_string)
    print("> {}".format(json_string))

start_server = websockets.serve(hello, '89.234.182.19', 8765)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
