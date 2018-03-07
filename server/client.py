#!/usr/bin/env python

import asyncio
import websockets


async def hello(name):
    async with websockets.connect('ws://localhost:8765') as websocket:
        await websocket.send(name)
        print("> {}".format(name))

        greeting = await websocket.recv()
        print("< {}".format(greeting))

asyncio.get_event_loop().run_until_complete(hello('message'))
