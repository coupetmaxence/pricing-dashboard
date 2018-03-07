#!/usr/bin/env python

import asyncio
import websockets
import subprocess


async def hello(websocket, path):
    message = await websocket.recv()
    print("< {}".format(message))

    data = json.load(message)
    # TODO : check data, etc

    result = subprocess.run(['../pricer/main', message], stdout=subprocess.PIPE)
    result_message = result.stdout.decode('utf-8')

    await websocket.send(result_message)
    print("> {}".format(result_message))

start_server = websockets.serve(hello, 'localhost', 8765)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
